#pragma once
#include<Windows.h>
#include<d3d9.h>
bool GameInitialize();//游戏初始化
bool GameStart(HWND hWnd);//场景初始化
void GameUpdate();//更新场景
void GameEnd();//游戏结束
class GameEngineApplication
{
private:
	GameEngineApplication(HINSTANCE hInstance, LPCTSTR szWndClassName, LPCTSTR szWndName, int iWidth, int iHeight, int iFrameDelay);
	static GameEngineApplication* m_pGameEngine;

	HWND m_hWnd;//窗口句柄
	HINSTANCE m_hInstance;//实例句柄
	TCHAR m_szWndClassNmae[20];//窗口类类名
	TCHAR m_szWndNmae[20];//窗口的名字
	int m_iWidth, m_iHeight;//窗口的宽和高
	int m_iFrameDelay;//更新的时间间隔，单位毫秒

public:
	static GameEngineApplication* getpGameEngine() { return m_pGameEngine; }
	static bool initialize(HINSTANCE hInstance, LPCTSTR szWndClassName, LPCTSTR szWndName, int iWidth, int iHeight, int iFrameDelay);
	bool CreateWnd(int iShowMode);
	long EventHandle(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	HWND gethWnd() { return m_hWnd; }
	int getFrameDelay() { return m_iFrameDelay; }
	HINSTANCE GetInstance() { return m_hInstance; }
};

