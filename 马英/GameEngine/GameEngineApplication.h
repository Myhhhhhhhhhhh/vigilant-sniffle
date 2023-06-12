#pragma once
#include<Windows.h>
#include<d3d9.h>
bool GameInitialize();//��Ϸ��ʼ��
bool GameStart(HWND hWnd);//������ʼ��
void GameUpdate();//���³���
void GameEnd();//��Ϸ����
class GameEngineApplication
{
private:
	GameEngineApplication(HINSTANCE hInstance, LPCTSTR szWndClassName, LPCTSTR szWndName, int iWidth, int iHeight, int iFrameDelay);
	static GameEngineApplication* m_pGameEngine;

	HWND m_hWnd;//���ھ��
	HINSTANCE m_hInstance;//ʵ�����
	TCHAR m_szWndClassNmae[20];//����������
	TCHAR m_szWndNmae[20];//���ڵ�����
	int m_iWidth, m_iHeight;//���ڵĿ�͸�
	int m_iFrameDelay;//���µ�ʱ��������λ����

public:
	static GameEngineApplication* getpGameEngine() { return m_pGameEngine; }
	static bool initialize(HINSTANCE hInstance, LPCTSTR szWndClassName, LPCTSTR szWndName, int iWidth, int iHeight, int iFrameDelay);
	bool CreateWnd(int iShowMode);
	long EventHandle(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	HWND gethWnd() { return m_hWnd; }
	int getFrameDelay() { return m_iFrameDelay; }
	HINSTANCE GetInstance() { return m_hInstance; }
};

