#include "GameEngine_Model.h"
GameEngine_Model::GameEngine_Model(GameEngine_SceneManager* pScene) {
	m_pAdjacency=NULL;
     m_pAdjacencyOptimize = NULL;
	 m_pSceneManager=pScene;
	 m_pMaterial = NULL;
	m_dwMatNum=0;
	 m_pMat = NULL;
	 m_ppTexture = NULL;
	 m_pMesh = NULL;
	 m_pCloneMesh = NULL;

}
GameEngine_Model::~GameEngine_Model() {
	m_pMesh->Release();
	delete m_ppTexture;

}
void GameEngine_Model::DrswMesh() {
	for (int i = 0;i < m_dwMatNum;i++) {
		m_pSceneManager->GetDevice()->SetMaterial(&m_pMat[i]);
		m_pSceneManager->GetDevice()->SetTexture(0, m_ppTexture[i]);
		m_pMesh->DrawSubset(i);
	}
}
bool GameEngine_Model::LoadMeshFromFileX(LPCTSTR pszFileName){
	int hr = D3DXLoadMeshFromX(pszFileName, D3DXMESH_MANAGED, m_pSceneManager->GetDevice(), &m_pAdjacency, &m_pMaterial, NULL, &m_dwMatNum, &m_pMesh);
	if (FAILED(hr))
		return false;
	if (m_pMaterial != NULL && m_dwMatNum != 0) {
		m_pMat = new D3DMATERIAL9[m_dwMatNum];
		m_ppTexture = new IDirect3DTexture9 * [m_dwMatNum];
		D3DXMATERIAL* temp = (D3DXMATERIAL*)m_pMaterial->GetBufferPointer();
		for (int i = 0;i < m_dwMatNum;i++) {
			m_pMat[i] = temp[i].MatD3D;
			m_pMat[i].Ambient = m_pMat[i].Diffuse;
			if (temp[i].pTextureFilename != NULL) {
				hr = D3DXCreateTextureFromFileA(m_pSceneManager->GetDevice(), temp[i].pTextureFilename, &m_ppTexture[i]);
				if (FAILED(hr))
					m_ppTexture[i] = NULL;
			}
		}
	}
	m_pAdjacencyOptimize = new DWORD[m_pMesh->GetNumFaces() * 3];

	m_pMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE, 0, 0, 0, NULL);
	D3DXComputeNormals(m_pMesh,m_pAdjacencyOptimize);
	return true;
}

