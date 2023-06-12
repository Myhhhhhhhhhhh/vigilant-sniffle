#include"GameEngine_SceneManager.h"
#include"GameEngine_Vertex.h"
#include"GameEngine_Light.h"
#include"GameEngine_Material.h"
#include"GameEngine_Texture.h"
#include"GameEngine_Model.h"
#include"GameEngine_Input.h"
#include"GameEngine_Camera.h"
GameEngine_SceneManager* pScene=NULL;
GameEngine_Vertex* pVertex = NULL;
GameEngine_Light light;
GameEngine_Material m;
GameEngine_Texture* pTex;
GameEngine_Model* pModel = NULL;
GameEngine_Input* pInput = NULL;
GameEngine_Camera *pCamera = 0;

float rot = 0;
float x = 0;
bool isRotation = false;
struct CustomVertex {
	float x, y, z;
	float nx, ny, nz;
	float u, v;
	CustomVertex(float ix, float iy, float iz,float fu,float fv) {
		x = ix; y = iy; z = iz; u = fu;v = fv;
	}
	static DWORD CustomFVF;
};
DWORD CustomVertex::CustomFVF = D3DFVF_XYZ | D3DFVF_NORMAL|D3DFVF_TEX1;


void ComputerNormal(CustomVertex& p0, CustomVertex&p1, CustomVertex&p2) {
	D3DXVECTOR3 p00 = D3DXVECTOR3(p0.x, p0.y, p0.z);
	D3DXVECTOR3 p11 = D3DXVECTOR3(p1.x, p1.y, p1.z);
	D3DXVECTOR3 p22 = D3DXVECTOR3(p2.x, p2.y, p2.z);
	D3DXVECTOR3 u = p11 - p00;
	D3DXVECTOR3 v = p22 - p00;
	D3DXVECTOR3 n;
	D3DXVec3Cross(&n, &u, &v);
	D3DXVec3Normalize(&n, &n);
	p0.nx = p1.nx = p2.nx = n.x;
	p0.ny = p1.ny = p2.ny = n.y;
	p0.nz = p1.nz = p2.nz = n.z;
}
bool GameInitialize() {

	return true;
}
bool GameStart(HWND hWnd) {
	
	CustomVertex vertex[] = {
	CustomVertex(-10,0,10,0,0),
	CustomVertex(10,0,10,1,0),
	CustomVertex(-10,0,-10,0,1),
	CustomVertex(10,0,10,1,0),
	CustomVertex(10,0,-10,1,1),
	CustomVertex(-10,0,-10,0,1),
	
	};

	for (int i = 0;i<6;i+=3){
		ComputerNormal(vertex[i], vertex[i + 1], vertex[i + 2]);
		
	}
	light.SetDirection(D3DXVECTOR3(1, 1, 1), D3DXCOLOR(1, 1, 1, 1), D3DXCOLOR(1, 1, 1, 1), D3DXCOLOR(1, 1, 1, 1));
	m.SetMaterial(D3DXCOLOR(1, 1, 1, 1), D3DXCOLOR(1, 1, 1, 1), D3DXCOLOR(1, 1, 1, 1), D3DXCOLOR(0, 0, 0, 1), 3.0f);

	pScene = new GameEngine_SceneManager(L"first");
	if (pScene == NULL)
		return false;
	if (!pScene->IniD3DDevice(hWnd, true))
		return false;
	pVertex = new GameEngine_Vertex(pScene);
	if (!pVertex->CreateVertexBuffer(12, CustomVertex::CustomFVF))
		return false;
	if (!pVertex->Lock(0, 0))
		return false;
	memcpy(pVertex->GetData(), vertex, sizeof(vertex));
	if (!pVertex->UnLock())
		return false;
	pModel = new GameEngine_Model(pScene);
	if (!pModel->LoadMeshFromFileX(TEXT("TIGER.X")))
		return false;
	pTex = new GameEngine_Texture(pScene);
	if(!pTex->LoadTextureFromFile(TEXT("tex4.jpg")))
		return false;
	pInput = new GameEngine_Input();
	pInput->CreateDirectInput(GameEngineApplication::getpGameEngine()->GetInstance());
	pInput->CreateKeyDevice(GameEngineApplication::getpGameEngine()->gethWnd());
	pInput->CreateMouseDevice(GameEngineApplication::getpGameEngine()->gethWnd());
	pScene->SetProjectionMatrix(D3DX_PI / 3, 800.0 / 600.0);
	pScene->SetViewPort(800, 600, 100, 100);
	pScene->SetRenderState(true);
	//pScene->SetCameraMatrix(D3DXVECTOR3(0, 1, -10), D3DXVECTOR3(0, 1, 0), D3DXVECTOR3(0, 0, 0));
	pCamera = new GameEngine_Camera(D3DXVECTOR3(0, 1, -10), D3DXVECTOR3(1, 0, 0), D3DXVECTOR3(0, 1, 0), D3DXVECTOR3(0, 0, 5));
	pScene->SetLight(0, &light, true);
	return true;
}
void GameUpdate(){
	pInput->ReadKeyboard();
	pInput->ReadMouse();
	if (pInput->isKeyPress(DIK_LEFT))
	{
		pCamera->CameraMove_LR(-0.1f);
	}
	if (pInput->isKeyPress(DIK_RIGHT))
	{
		pCamera->CameraMove_LR(-0.1f);
	}
	if (pInput->isKeyPress(DIK_UP))
	{
		pCamera->CameraMove_FN(0.1f);
	}
	if (pInput->isKeyPress(DIK_DOWN))
	{
		pCamera->CameraMove_FN(-0.1f);
	}
	pScene->SetSelfCameraMatrix(pCamera);

	if(!pScene->ClearColor(D3DCOLOR_ARGB(255,0,0,0)))
		return;
	if (!pScene->BeginScene())
		return;
	pScene->SetWorldMatrix(0, 0, 0, 0, rot, 0, 1, 1, 1);
	pScene->SetMaterial(&m);
	pScene->SetTexture(pTex, 0);
	if (!pVertex->RenderVertex(D3DPT_TRIANGLELIST, 0, 2))
		return;
	pScene->SetWorldMatrix(x, 0, 0, 0, 0, 0, 1, 1, 1);
	
	pModel->DrswMesh();

	//pScene->SetWorldMatrix(-3, 0, 0, 0, rot, 0, 1, 1, 1);
	//if (!pVertex->RenderVertex(D3DPT_TRIANGLELIST, 0, 4))
	//	return;
	pScene->SetMaterial(&m);

	if (!pScene->EndScene())
		return;
	
	
		rot += 0.1f;

}
void GameEnd(){
	
}