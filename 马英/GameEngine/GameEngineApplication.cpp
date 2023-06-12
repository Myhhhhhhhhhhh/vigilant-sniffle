#include "GameEngineApplication.h"
GameEngineApplication* GameEngineApplication::m_pGameEngine = NULL;
long CALLBACK WindowFun(HWND hwnd, UINT m, WPARAM w, LPARAM l);
GameEngineApplication::GameEngineApplication(HINSTANCE hInstance, LPCTSTR szWndClassName, LPCTSTR szWndName, int iWidth, int iHeight, int iFrameDelay) {
	m_hInstance = hInstance;
	lstrcpy(m_szWndClassNmae, szWndClassName);
	lstrcpy(m_szWndNmae, szWndName);
	m_iWidth = iWidth;
	m_iHeight = iHeight;
	m_iFrameDelay = iFrameDelay;
	m_hWnd = NULL;
}
bool GameEngineApplication::initialize(HINSTANCE hInstance, LPCTSTR szWndClassName, LPCTSTR szWndName, int iWidth, int iHeight, int iFrameDelay) {
	if (m_pGameEngine == NULL)
		m_pGameEngine = new GameEngineApplication(hInstance,szWndClassName,szWndName,iWidth,iHeight,iFrameDelay);
	if (m_pGameEngine == NULL)
		return false;
	else
		return true;
}
bool GameEngineApplication::CreateWnd(int mode) {
	WNDCLASS mywndclass;
	ZeroMemory(&mywndclass, sizeof(mywndclass));
	mywndclass.hInstance = m_hInstance;
	mywndclass.lpszClassName = m_szWndClassNmae;
	mywndclass.style = CS_HREDRAW | CS_VREDRAW;
	mywndclass.lpfnWndProc = WindowFun;
	mywndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	if (!RegisterClass(&mywndclass))
		return false;
	m_hWnd = CreateWindow(m_szWndClassNmae, m_szWndNmae, WS_OVERLAPPEDWINDOW, 0, 0, m_iWidth, m_iHeight, NULL, NULL, m_hInstance, NULL);
	if (m_hWnd == NULL)
		return false;
	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	UpdateWindow(m_hWnd);
	return true;
}
long GameEngineApplication::EventHandle(HWND hWnd, UINT m, WPARAM w, LPARAM l) {
	TCHAR C[2];
	TCHAR str[30];
	int x, y;
	switch (m) {
	case WM_DESTROY:
		GameEnd();
		PostQuitMessage(0);
		break;
	}
	return ::DefWindowProc(hWnd, m, w, l);
}
int WINAPI WinMain(HINSTANCE curh, HINSTANCE preh, LPSTR cmd, int mode) {
	static int amounttime = 0;
	int curtime;
	if (!GameEngineApplication::initialize(curh, TEXT("MYCLASS"), TEXT("GAMEBOX"), 800, 600, 50))
		return 0;
	if (!GameInitialize())
		return 0;
	if (!GameEngineApplication::getpGameEngine()->CreateWnd(SW_SHOWNORMAL))
		return 0;
	if (!GameStart(GameEngineApplication::getpGameEngine()->gethWnd()))
		return 0;
	MSG msg;
	while (true) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			curtime = GetTickCount();
			if (curtime > amounttime) {
				GameUpdate();
				amounttime = curtime + GameEngineApplication::getpGameEngine()->getFrameDelay();
			}
		}
	}
	return 0;
}long CALLBACK WindowFun(HWND hwnd, UINT m, WPARAM w, LPARAM l) {
	return GameEngineApplication::getpGameEngine()->EventHandle(hwnd, m, w, l);
}

