#include "GameEngine_SceneManager.h"
#include"GameEngine_Texture.h"
#include"GameEngine_Camera.h"
GameEngine_SceneManager::GameEngine_SceneManager(LPCTSTR szSceneName) {
	lstrcpy(m_szSceneName, szSceneName);
	m_pDirect3D9 = NULL;
	m_pDirect3DDevice9 = NULL;
}
bool GameEngine_SceneManager::IniD3DDevice(HWND hWnd, bool isWindow) {
	m_pDirect3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	D3DCAPS9 caps;
	m_pDirect3D9->GetDeviceCaps(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		&caps);
	int  vp = 0;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	D3DDISPLAYMODE mode;
	m_pDirect3D9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &mode);
	D3DPRESENT_PARAMETERS param;
	ZeroMemory(&param, sizeof(param));//结构体清零
	param.BackBufferWidth = 800;//后台缓冲区宽度
	param.BackBufferHeight = 600;//后台缓冲区宽度
	param.BackBufferFormat = mode.Format;//后台缓冲区显示格式
	param.BackBufferCount = 1;//后台缓冲区格式
	param.hDeviceWindow = hWnd;//窗口句柄
	param.Windowed = isWindow;//是否窗口显示，true窗口显示；false全屏显示
	param.SwapEffect = D3DSWAPEFFECT_FLIP;//后台缓冲链
	param.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	//前、后台缓冲区交换频率
	m_pDirect3D9->CreateDevice(D3DADAPTER_DEFAULT,//显卡号 
		D3DDEVTYPE_HAL, //设备类型
		hWnd, //设备所属窗口
		vp, //设备顶点处理方式
		&param,  //设备属性参数        
		&m_pDirect3DDevice9//设备接口指针
	);
	if (m_pDirect3DDevice9== NULL)
		return false;
	return true;
}
bool GameEngine_SceneManager::ClearColor(D3DCOLOR color) {
	int hr=m_pDirect3DDevice9->Clear(0,//清除缓冲区矩形区域的个数，0表示清除整个后台缓冲区
		NULL,//指向要清除的矩形区域指针，NULL表示所有矩形区域
		D3DCLEAR_TARGET,//要清除缓冲区的类型，目前参数为后台缓冲区
		D3DCOLOR_ARGB(1, 0, 0, 0),//清除后的新颜色，目前参数为黑色
		1.0,//Z缓冲区的新值
		0//stencil缓冲区的新值
	);
	if (FAILED(hr))
		return false;
	else
		return true;
}
bool GameEngine_SceneManager::BeginScene() {
	int hr=m_pDirect3DDevice9->BeginScene(); //开始绘制
	if (FAILED(hr))
		return false;
	else
		return true;
}
bool GameEngine_SceneManager::EndScene() {
	int hr=m_pDirect3DDevice9->EndScene(); //结束绘制
	if (FAILED(hr))
		return false;

	//提交后台缓存的内容
	hr=m_pDirect3DDevice9->Present(NULL,//后台缓冲区要绘制的矩形指针，NULL表示绘制整个后台缓冲区
		NULL,//显示的目标区域矩形指针，NULL表示窗口客户区
		NULL,//要显示的窗口句柄，NULL表示使用D3D设备窗口句柄
		NULL//刷新区域，NULL表示整个屏幕
	);
	if (FAILED(hr))
		return false;
	else
		return true;
}
void GameEngine_SceneManager::SetWorldMatrix(float fPosX, float fPosy, float fPosz, //平移参数
	float fRotatex, float fRotatey, float fRotaetz,//旋转参数 
	float fScalex, float fScaley, float fScalez//缩放参数
	)
{
	D3DXMATRIX world, translate, rotate, rotatex,rotatey,rotatez,scale; //world世界变换矩阵，translate平移变换矩阵，rotate旋转变换矩阵，scale缩放变换矩阵
	D3DXMatrixIdentity(&world);//将world设为单位阵
	D3DXMatrixIdentity(&rotate);
	D3DXMatrixIdentity(&scale);
	D3DXMatrixIdentity(&rotatex);
	D3DXMatrixIdentity(&rotatey);
	D3DXMatrixIdentity(&rotatez);
	D3DXMatrixTranslation(&translate, fPosX, fPosy, fPosz);
	//沿着X,Y,Z轴平移x,y,z
	D3DXMatrixRotationX(&rotatex, fRotatex);
	D3DXMatrixRotationY(&rotatey, fRotatey);
	D3DXMatrixRotationZ(&rotatez, fRotaetz);
	rotate = rotate * rotatey;
	rotate *= rotatex;
	rotate *= rotatez;
	//绕着 （X,Y,Z）轴，旋转angle
	D3DXMatrixScaling(&scale, fScalex, fScaley, fScalez);
	//沿着X,Y,Z轴放大sx,sy,sz倍
	//必须按缩放--》旋转--》平移次序变换
	world = world * scale;
	world = world * rotate;
	world = world * translate;
	m_pDirect3DDevice9->SetTransform(D3DTS_WORLD, &world);
}
void GameEngine_SceneManager::SetCameraMatrix(D3DXVECTOR3 eye, D3DXVECTOR3 up, D3DXVECTOR3 at) {
	D3DXMATRIX view; //取景变换矩阵
	
	D3DXMatrixLookAtLH(&view, &eye, &at, &up);
	//设置渲染流水线摄影变换所采用的矩阵，以计算顶点的摄影坐标
	m_pDirect3DDevice9->SetTransform(D3DTS_VIEW, &view);
}
void GameEngine_SceneManager::SetProjectionMatrix(float fFOV, float fAspect) {
	D3DXMATRIX projection; //投影变换矩阵
	D3DXMatrixPerspectiveFovLH(&projection,
		fFOV,//垂直视角
		fAspect,//宽高比
		1.0f,//近平面，一般设为1.0f
		100.0f//远平面
	);
	//设置渲染流水线投影变换所采用的矩阵
	m_pDirect3DDevice9->SetTransform(D3DTS_PROJECTION, &projection);
}
void GameEngine_SceneManager::SetViewPort(float fWidth, float fHeight, float fPosX, float fPosY) {
	D3DVIEWPORT9 winport;
	winport.Width = fWidth;//视口的宽
	winport.Height = fHeight;//视口的高
	winport.MinZ = 0;//视口像素z的最小值，一般为0
	winport.MaxZ = 1; ;//视口像素z的最大值，一般为1
	winport.X = fPosX;//视口左上角的窗口坐标X
	winport.Y = fPosY; //视口左上角的窗口坐标Y
	//设置视口
	m_pDirect3DDevice9->SetViewport(&winport);
}
void GameEngine_SceneManager::SetRenderState(bool isLight) {
	m_pDirect3DDevice9->SetRenderState(D3DRS_LIGHTING, isLight);
}
void GameEngine_SceneManager::SetLight(
	int iIndex,//光源索引号
	GameEngine_Light* pLight,//光源类指针
	bool bIsEnable//是否启用，True启用，false不启用
) {
	m_pDirect3DDevice9->SetLight(iIndex, pLight->GetLight());
	m_pDirect3DDevice9->LightEnable(iIndex, bIsEnable);
}
void GameEngine_SceneManager::SetMaterial(
	GameEngine_Material* pMaterial
) {
	m_pDirect3DDevice9->SetMaterial(pMaterial->GetMaterial());
}
void GameEngine_SceneManager::SetTexture(GameEngine_Texture* pTexture,//纹理类指针
	int i//纹理号
)
	{
	m_pDirect3DDevice9->SetTexture(i, pTexture->GetTexture());
	}
void GameEngine_SceneManager::SetSelfCameraMatrix(GameEngine_Camera* pCamera) {
	D3DXMATRIX view;
	pCamera->GetMatrixView(view);
	m_pDirect3DDevice9->SetTransform(D3DTS_VIEW, &view);

}
