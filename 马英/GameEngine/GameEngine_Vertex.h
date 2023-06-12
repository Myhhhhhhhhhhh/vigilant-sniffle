#pragma once
#include"GameEngine_SceneManager.h"
class GameEngine_Vertex
{
private:
	GameEngine_SceneManager* m_pSceneManager;//�����������ָ��
	IDirect3DVertexBuffer9* m_pVertexBuffer;//���㻺��ָ��
	void* m_pData;//���ʶ��㻺���ָ��
	DWORD m_dwFVF;//����ĸ�ʽ
	DWORD m_dwNumVertices;//�������
	DWORD m_dwVertexSize;//����Ĵ�С
public:
	GameEngine_Vertex(GameEngine_SceneManager* pScene);
	bool CreateVertexBuffer(
		DWORD dwNumVertices,//��������
		DWORD dwFVF); //�����ʽ
	bool Lock(
		DWORD dwStartIndex, //��������ʼλ��
		DWORD dwLockSize);//���������С
	bool UnLock();
	bool RenderVertex(
		DWORD dwVertexType,//��Ⱦ����
		DWORD dwStartIndex,//��ʼ���������
		DWORD dwNumTriangle);//������ͼԪ�ĸ���
	void* GetData() { return m_pData; }
};

