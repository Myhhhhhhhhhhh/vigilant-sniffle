#include "GameEngine_Vertex.h"
GameEngine_Vertex::GameEngine_Vertex(GameEngine_SceneManager* pScene) {
	m_pSceneManager = pScene;
	m_pVertexBuffer = NULL;
}
bool GameEngine_Vertex::CreateVertexBuffer(
	DWORD dwNumVertices,//顶点数量
	DWORD dwFVF) //顶点格式
{
	m_dwFVF = dwFVF;
	m_dwNumVertices = dwNumVertices;
	m_dwVertexSize = D3DXGetFVFVertexSize(m_dwFVF);
	int hr=m_pSceneManager->GetDevice()->CreateVertexBuffer(
		m_dwNumVertices *m_dwVertexSize,
		0,
		m_dwFVF,
		D3DPOOL_DEFAULT,
		&m_pVertexBuffer,
		NULL);
	if (FAILED(hr))
		return false;
	else
		return true;
}
bool GameEngine_Vertex::Lock(
	DWORD dwStartIndex, //锁定的起始位置
	DWORD dwLockSize) {
	int hr=m_pVertexBuffer->Lock(dwStartIndex,//锁定起始位置
		dwLockSize,//锁定的字节大小						     
	    &m_pData,//锁定起始位置的内存指针地址
		0//锁定属性
	);
	if (FAILED(hr))
		return false;
	else
		return true;
}
bool GameEngine_Vertex::UnLock() {
	int hr=m_pVertexBuffer->Unlock();
	if (FAILED(hr))
		return false;
	else
		return true;
}
bool GameEngine_Vertex::RenderVertex(
	DWORD dwVertexType,//渲染类型
	DWORD dwStartIndex,//起始顶点的索引
	DWORD dwNumTriangle)//三角形图元的个数
{
	int hr=m_pSceneManager->GetDevice()->SetStreamSource(0,//管道流水线编号
		m_pVertexBuffer,//缓冲区指针
		0,//起始位置	     
		m_dwVertexSize);
	if (FAILED(hr))
		return false;
	//顶点大小
	m_pSceneManager->GetDevice()->SetFVF(m_dwFVF);
	if (FAILED(hr))
		return false;
	m_pSceneManager->GetDevice()->DrawPrimitive((D3DPRIMITIVETYPE)dwVertexType,
		//绘制类型
		dwStartIndex,//起始顶点位置索引
		dwNumTriangle);//绘制的图元数
	if (FAILED(hr))
		return false;
	return true;
}

