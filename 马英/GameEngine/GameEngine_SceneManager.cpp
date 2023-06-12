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
	ZeroMemory(&param, sizeof(param));//�ṹ������
	param.BackBufferWidth = 800;//��̨���������
	param.BackBufferHeight = 600;//��̨���������
	param.BackBufferFormat = mode.Format;//��̨��������ʾ��ʽ
	param.BackBufferCount = 1;//��̨��������ʽ
	param.hDeviceWindow = hWnd;//���ھ��
	param.Windowed = isWindow;//�Ƿ񴰿���ʾ��true������ʾ��falseȫ����ʾ
	param.SwapEffect = D3DSWAPEFFECT_FLIP;//��̨������
	param.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	//ǰ����̨����������Ƶ��
	m_pDirect3D9->CreateDevice(D3DADAPTER_DEFAULT,//�Կ��� 
		D3DDEVTYPE_HAL, //�豸����
		hWnd, //�豸��������
		vp, //�豸���㴦��ʽ
		&param,  //�豸���Բ���        
		&m_pDirect3DDevice9//�豸�ӿ�ָ��
	);
	if (m_pDirect3DDevice9== NULL)
		return false;
	return true;
}
bool GameEngine_SceneManager::ClearColor(D3DCOLOR color) {
	int hr=m_pDirect3DDevice9->Clear(0,//�����������������ĸ�����0��ʾ���������̨������
		NULL,//ָ��Ҫ����ľ�������ָ�룬NULL��ʾ���о�������
		D3DCLEAR_TARGET,//Ҫ��������������ͣ�Ŀǰ����Ϊ��̨������
		D3DCOLOR_ARGB(1, 0, 0, 0),//����������ɫ��Ŀǰ����Ϊ��ɫ
		1.0,//Z����������ֵ
		0//stencil����������ֵ
	);
	if (FAILED(hr))
		return false;
	else
		return true;
}
bool GameEngine_SceneManager::BeginScene() {
	int hr=m_pDirect3DDevice9->BeginScene(); //��ʼ����
	if (FAILED(hr))
		return false;
	else
		return true;
}
bool GameEngine_SceneManager::EndScene() {
	int hr=m_pDirect3DDevice9->EndScene(); //��������
	if (FAILED(hr))
		return false;

	//�ύ��̨���������
	hr=m_pDirect3DDevice9->Present(NULL,//��̨������Ҫ���Ƶľ���ָ�룬NULL��ʾ����������̨������
		NULL,//��ʾ��Ŀ���������ָ�룬NULL��ʾ���ڿͻ���
		NULL,//Ҫ��ʾ�Ĵ��ھ����NULL��ʾʹ��D3D�豸���ھ��
		NULL//ˢ������NULL��ʾ������Ļ
	);
	if (FAILED(hr))
		return false;
	else
		return true;
}
void GameEngine_SceneManager::SetWorldMatrix(float fPosX, float fPosy, float fPosz, //ƽ�Ʋ���
	float fRotatex, float fRotatey, float fRotaetz,//��ת���� 
	float fScalex, float fScaley, float fScalez//���Ų���
	)
{
	D3DXMATRIX world, translate, rotate, rotatex,rotatey,rotatez,scale; //world����任����translateƽ�Ʊ任����rotate��ת�任����scale���ű任����
	D3DXMatrixIdentity(&world);//��world��Ϊ��λ��
	D3DXMatrixIdentity(&rotate);
	D3DXMatrixIdentity(&scale);
	D3DXMatrixIdentity(&rotatex);
	D3DXMatrixIdentity(&rotatey);
	D3DXMatrixIdentity(&rotatez);
	D3DXMatrixTranslation(&translate, fPosX, fPosy, fPosz);
	//����X,Y,Z��ƽ��x,y,z
	D3DXMatrixRotationX(&rotatex, fRotatex);
	D3DXMatrixRotationY(&rotatey, fRotatey);
	D3DXMatrixRotationZ(&rotatez, fRotaetz);
	rotate = rotate * rotatey;
	rotate *= rotatex;
	rotate *= rotatez;
	//���� ��X,Y,Z���ᣬ��תangle
	D3DXMatrixScaling(&scale, fScalex, fScaley, fScalez);
	//����X,Y,Z��Ŵ�sx,sy,sz��
	//���밴����--����ת--��ƽ�ƴ���任
	world = world * scale;
	world = world * rotate;
	world = world * translate;
	m_pDirect3DDevice9->SetTransform(D3DTS_WORLD, &world);
}
void GameEngine_SceneManager::SetCameraMatrix(D3DXVECTOR3 eye, D3DXVECTOR3 up, D3DXVECTOR3 at) {
	D3DXMATRIX view; //ȡ���任����
	
	D3DXMatrixLookAtLH(&view, &eye, &at, &up);
	//������Ⱦ��ˮ����Ӱ�任�����õľ����Լ��㶥�����Ӱ����
	m_pDirect3DDevice9->SetTransform(D3DTS_VIEW, &view);
}
void GameEngine_SceneManager::SetProjectionMatrix(float fFOV, float fAspect) {
	D3DXMATRIX projection; //ͶӰ�任����
	D3DXMatrixPerspectiveFovLH(&projection,
		fFOV,//��ֱ�ӽ�
		fAspect,//��߱�
		1.0f,//��ƽ�棬һ����Ϊ1.0f
		100.0f//Զƽ��
	);
	//������Ⱦ��ˮ��ͶӰ�任�����õľ���
	m_pDirect3DDevice9->SetTransform(D3DTS_PROJECTION, &projection);
}
void GameEngine_SceneManager::SetViewPort(float fWidth, float fHeight, float fPosX, float fPosY) {
	D3DVIEWPORT9 winport;
	winport.Width = fWidth;//�ӿڵĿ�
	winport.Height = fHeight;//�ӿڵĸ�
	winport.MinZ = 0;//�ӿ�����z����Сֵ��һ��Ϊ0
	winport.MaxZ = 1; ;//�ӿ�����z�����ֵ��һ��Ϊ1
	winport.X = fPosX;//�ӿ����ϽǵĴ�������X
	winport.Y = fPosY; //�ӿ����ϽǵĴ�������Y
	//�����ӿ�
	m_pDirect3DDevice9->SetViewport(&winport);
}
void GameEngine_SceneManager::SetRenderState(bool isLight) {
	m_pDirect3DDevice9->SetRenderState(D3DRS_LIGHTING, isLight);
}
void GameEngine_SceneManager::SetLight(
	int iIndex,//��Դ������
	GameEngine_Light* pLight,//��Դ��ָ��
	bool bIsEnable//�Ƿ����ã�True���ã�false������
) {
	m_pDirect3DDevice9->SetLight(iIndex, pLight->GetLight());
	m_pDirect3DDevice9->LightEnable(iIndex, bIsEnable);
}
void GameEngine_SceneManager::SetMaterial(
	GameEngine_Material* pMaterial
) {
	m_pDirect3DDevice9->SetMaterial(pMaterial->GetMaterial());
}
void GameEngine_SceneManager::SetTexture(GameEngine_Texture* pTexture,//������ָ��
	int i//�����
)
	{
	m_pDirect3DDevice9->SetTexture(i, pTexture->GetTexture());
	}
void GameEngine_SceneManager::SetSelfCameraMatrix(GameEngine_Camera* pCamera) {
	D3DXMATRIX view;
	pCamera->GetMatrixView(view);
	m_pDirect3DDevice9->SetTransform(D3DTS_VIEW, &view);

}
