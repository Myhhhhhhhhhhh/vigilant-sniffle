#pragma once
#include <dinput.h>
class GameEngine_Input
{
private:
	IDirectInput8* m_pInput;
	//IDirectInput�ӿ�ָ��
	IDirectInputDevice8* m_pKeyboard;
	//Input�豸�����̣�
	IDirectInputDevice8* m_pMouse;
	//Input�豸����꣩
	char m_KeyBuffer[256];//���̻���
	DIMOUSESTATE m_MouseState;//��껺��
	long int m_lMouseX, m_lMouseY;
	//���ľ�������

public:
	GameEngine_Input();
	// ����IDirectInput8�ӿڶ���
	bool CreateDirectInput(HINSTANCE hInstance);
	// ��������
	bool CreateKeyDevice(HWND hWnd);
	// ��������豸
	bool CreateMouseDevice(HWND hWnd);
	// �жϰ����Ƿ񱻰���
	bool isKeyPress(int key);
	// ��ȡ��������
	bool ReadKeyboard();
	// ��ȡ�������
	bool ReadMouse();
	// �������Ƿ���
	bool isLBPress();
	// ����Ҽ��Ƿ���
	bool isRBPress();
	//�������Ƿ���
	bool isMBPress();
	void AcquireDevice(); //����豸
	void UnacquireDevice();//�ͷ��豸


};

