#include "GameEngine_Vertex.h"
GameEngine_Vertex::GameEngine_Vertex(GameEngine_SceneManager* pScene) {
	m_pSceneManager = pScene;
	m_pVertexBuffer = NULL;
}
bool GameEngine_Vertex::CreateVertexBuffer(
	DWORD dwNumVertices,//��������
	DWORD dwFVF) //�����ʽ
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
	DWORD dwStartIndex, //��������ʼλ��
	DWORD dwLockSize) {
	int hr=m_pVertexBuffer->Lock(dwStartIndex,//������ʼλ��
		dwLockSize,//�������ֽڴ�С						     
	    &m_pData,//������ʼλ�õ��ڴ�ָ���ַ
		0//��������
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
	DWORD dwVertexType,//��Ⱦ����
	DWORD dwStartIndex,//��ʼ���������
	DWORD dwNumTriangle)//������ͼԪ�ĸ���
{
	int hr=m_pSceneManager->GetDevice()->SetStreamSource(0,//�ܵ���ˮ�߱��
		m_pVertexBuffer,//������ָ��
		0,//��ʼλ��	     
		m_dwVertexSize);
	if (FAILED(hr))
		return false;
	//�����С
	m_pSceneManager->GetDevice()->SetFVF(m_dwFVF);
	if (FAILED(hr))
		return false;
	m_pSceneManager->GetDevice()->DrawPrimitive((D3DPRIMITIVETYPE)dwVertexType,
		//��������
		dwStartIndex,//��ʼ����λ������
		dwNumTriangle);//���Ƶ�ͼԪ��
	if (FAILED(hr))
		return false;
	return true;
}

