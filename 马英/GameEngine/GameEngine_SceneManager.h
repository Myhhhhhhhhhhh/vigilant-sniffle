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
	TCHAR m_szSceneName[50];//场景名称
	IDirect3D9* m_pDirect3D9;//IDirect3D9接口指针
	IDirect3DDevice9* m_pDirect3DDevice9;
	//IDirectDDevice接口指针
public:
	GameEngine_SceneManager(LPCTSTR szSceneName);
	//初始化D3D设备
	bool IniD3DDevice(HWND hWnd, bool isWindow);
	//清空颜色缓冲区
	bool ClearColor(D3DCOLOR color);
	//开始绘制场景
	bool BeginScene();
	//结束绘制，并显示
	bool EndScene();
	IDirect3DDevice9* GetDevice() { return m_pDirect3DDevice9; }
	void SetWorldMatrix(float fPosX, float fPosy, float fPosz, //平移参数
		float fRotatex, float fRotatey, float fRotaetz,//旋转参数 
		float fScalex, float fScaley, float fScalez//缩放参数
	);
	void SetCameraMatrix(D3DXVECTOR3 eye, D3DXVECTOR3 up, D3DXVECTOR3 at);
	void SetProjectionMatrix(float fFOV, float fAspect);
	void SetViewPort(float fWidth, float fHeight, float fPosX, float fPosY);
	void SetRenderState(bool isLight);
	void SetLight(
		int iIndex,//光源索引号
		GameEngine_Light* pLight,//光源类指针
		bool bIsEnable//是否启用，True启用，false不启用
	);
	void SetMaterial(
		GameEngine_Material* pMaterial
	);
	void SetTexture(
		GameEngine_Texture* pTexture,//纹理类指针
		int i//纹理号
	);
	void SetSelfCameraMatrix(GameEngine_Camera* pCamera);

};

