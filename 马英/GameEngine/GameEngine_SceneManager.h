#pragma once
#include"GameEngineApplication.h"
#include"GameEngine_Light.h"
#include"GameEngine_Material.h"
#include<d3dx9.h>
class GameEngine_Texture;
class GameEngine_Camera;
class GameEngine_SceneManager
{
private:
	TCHAR m_szSceneName[50];//��������
	IDirect3D9* m_pDirect3D9;//IDirect3D9�ӿ�ָ��
	IDirect3DDevice9* m_pDirect3DDevice9;
	//IDirectDDevice�ӿ�ָ��
public:
	GameEngine_SceneManager(LPCTSTR szSceneName);
	//��ʼ��D3D�豸
	bool IniD3DDevice(HWND hWnd, bool isWindow);
	//�����ɫ������
	bool ClearColor(D3DCOLOR color);
	//��ʼ���Ƴ���
	bool BeginScene();
	//�������ƣ�����ʾ
	bool EndScene();
	IDirect3DDevice9* GetDevice() { return m_pDirect3DDevice9; }
	void SetWorldMatrix(float fPosX, float fPosy, float fPosz, //ƽ�Ʋ���
		float fRotatex, float fRotatey, float fRotaetz,//��ת���� 
		float fScalex, float fScaley, float fScalez//���Ų���
	);
	void SetCameraMatrix(D3DXVECTOR3 eye, D3DXVECTOR3 up, D3DXVECTOR3 at);
	void SetProjectionMatrix(float fFOV, float fAspect);
	void SetViewPort(float fWidth, float fHeight, float fPosX, float fPosY);
	void SetRenderState(bool isLight);
	void SetLight(
		int iIndex,//��Դ������
		GameEngine_Light* pLight,//��Դ��ָ��
		bool bIsEnable//�Ƿ����ã�True���ã�false������
	);
	void SetMaterial(
		GameEngine_Material* pMaterial
	);
	void SetTexture(
		GameEngine_Texture* pTexture,//������ָ��
		int i//�����
	);
	void SetSelfCameraMatrix(GameEngine_Camera* pCamera);

};

