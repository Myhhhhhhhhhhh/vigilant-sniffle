#pragma once
#include"GameEngine_SceneManager.h" 
class GameEngine_Model
{
private:
	ID3DXBuffer* m_pAdjacency;//�ڽ���Ϣ������
	DWORD* m_pAdjacencyOptimize;//�Ż�����ڽ���Ϣ����
	GameEngine_SceneManager* m_pSceneManager;//����ָ��
	ID3DXBuffer* m_pMaterial;//���ʻ�����
	DWORD m_dwMatNum;//��������
	D3DMATERIAL9* m_pMat;//��������
	IDirect3DTexture9** m_ppTexture;//��������
	ID3DXMesh* m_pMesh;//����ָ��
	ID3DXMesh* m_pCloneMesh;//��¡����ָ��
public:
	bool LoadMeshFromFileX(LPCTSTR pszFileName);
	// ��Ⱦ����
	 void DrswMesh();
	GameEngine_Model(GameEngine_SceneManager* pScene);
	~GameEngine_Model();
    

};

