#pragma once
#include"GameEngine_SceneManager.h"
class GameEngine_Vertex
{
private:
	GameEngine_SceneManager* m_pSceneManager;//场景管理对象指针
	IDirect3DVertexBuffer9* m_pVertexBuffer;//顶点缓存指针
	void* m_pData;//访问顶点缓存的指针
	DWORD m_dwFVF;//顶点的格式
	DWORD m_dwNumVertices;//顶点个数
	DWORD m_dwVertexSize;//顶点的大小
public:
	GameEngine_Vertex(GameEngine_SceneManager* pScene);
	bool CreateVertexBuffer(
		DWORD dwNumVertices,//顶点数量
		DWORD dwFVF); //顶点格式
	bool Lock(
		DWORD dwStartIndex, //锁定的起始位置
		DWORD dwLockSize);//锁定区域大小
	bool UnLock();
	bool RenderVertex(
		DWORD dwVertexType,//渲染类型
		DWORD dwStartIndex,//起始顶点的索引
		DWORD dwNumTriangle);//三角形图元的个数
	void* GetData() { return m_pData; }
};

