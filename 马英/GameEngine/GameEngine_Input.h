#pragma once
#include <dinput.h>
class GameEngine_Input
{
private:
	IDirectInput8* m_pInput;
	//IDirectInput接口指针
	IDirectInputDevice8* m_pKeyboard;
	//Input设备（键盘）
	IDirectInputDevice8* m_pMouse;
	//Input设备（鼠标）
	char m_KeyBuffer[256];//键盘缓存
	DIMOUSESTATE m_MouseState;//鼠标缓存
	long int m_lMouseX, m_lMouseY;
	//鼠标的绝对坐标

public:
	GameEngine_Input();
	// 创建IDirectInput8接口对象
	bool CreateDirectInput(HINSTANCE hInstance);
	// 创建键盘
	bool CreateKeyDevice(HWND hWnd);
	// 创建鼠标设备
	bool CreateMouseDevice(HWND hWnd);
	// 判断按键是否被按下
	bool isKeyPress(int key);
	// 读取键盘数据
	bool ReadKeyboard();
	// 读取鼠标数据
	bool ReadMouse();
	// 鼠标左键是否按下
	bool isLBPress();
	// 鼠标右键是否按下
	bool isRBPress();
	//鼠标滚轮是否按下
	bool isMBPress();
	void AcquireDevice(); //获得设备
	void UnacquireDevice();//释放设备


};

