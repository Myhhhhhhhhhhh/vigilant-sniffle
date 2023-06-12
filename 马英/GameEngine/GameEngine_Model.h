#pragma once
#include"GameEngine_SceneManager.h" 
class GameEngine_Model
{
private:
	ID3DXBuffer* m_pAdjacency;//邻接信息缓冲区
	DWORD* m_pAdjacencyOptimize;//优化后的邻接信息数组
	GameEngine_SceneManager* m_pSceneManager;//场景指针
	ID3DXBuffer* m_pMaterial;//材质缓冲区
	DWORD m_dwMatNum;//材质数量
	D3DMATERIAL9* m_pMat;//材质数组
	IDirect3DTexture9** m_ppTexture;//纹理数组
	ID3DXMesh* m_pMesh;//网格指针
	ID3DXMesh* m_pCloneMesh;//克隆网格指针
public:
	bool LoadMeshFromFileX(LPCTSTR pszFileName);
	// 渲染网格
	 void DrswMesh();
	GameEngine_Model(GameEngine_SceneManager* pScene);
	~GameEngine_Model();
    

};

