#include "GameEngine_Input.h"

GameEngine_Input::GameEngine_Input() {
	m_pInput = 0;
	m_pKeyboard = 0;
	m_pMouse = 0;
	m_lMouseX = 0;
	m_lMouseY = 0;
}

bool GameEngine_Input::CreateDirectInput(HINSTANCE hInstance) {
	HRESULT hr = DirectInput8Create(
		hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_pInput,
		NULL);
	if (FAILED(hr))
		return false;

	return true;
}

bool GameEngine_Input::CreateKeyDevice(HWND hWnd) {
	HRESULT hr = m_pInput->CreateDevice(GUID_SysKeyboard, &m_pKeyboard, NULL);
	if (FAILED(hr))
		return false;

	hr = m_pKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
		return false;

	hr = m_pKeyboard->SetCooperativeLevel(
		hWnd,
		DISCL_FOREGROUND | DISCL_EXCLUSIVE
	);
	if (FAILED(hr))
		return false;

	m_pKeyboard->Acquire();

	return true;
}

bool GameEngine_Input::CreateMouseDevice(HWND hWnd) {
	HRESULT hr = m_pInput->CreateDevice(GUID_SysMouse, &m_pMouse, NULL);
	if (FAILED(hr))
		return false;

	hr = m_pMouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(hr))
		return false;

	hr = m_pMouse->SetCooperativeLevel(
		hWnd,
		DISCL_FOREGROUND | DISCL_EXCLUSIVE
	);
	if (FAILED(hr))
		return false;

	m_pMouse->Acquire();

	return true;
}

bool GameEngine_Input::ReadKeyboard() {
	ZeroMemory(m_KeyBuffer, sizeof(m_KeyBuffer));
	HRESULT hr = m_pKeyboard->GetDeviceState(sizeof(m_KeyBuffer),
		(LPVOID)m_KeyBuffer);
	if (FAILED(hr))
		return false;

	return true;
}

bool GameEngine_Input::ReadMouse() {
	ZeroMemory(&m_MouseState, sizeof(m_MouseState));
	HRESULT hr = m_pMouse->GetDeviceState(sizeof(m_MouseState),
		(LPVOID)&m_MouseState);
	if (FAILED(hr))
		return false;

	m_lMouseX += m_MouseState.lX;
	m_lMouseY += m_MouseState.lY;

	return true;
}

bool GameEngine_Input::isKeyPress(int key) {
	if (m_KeyBuffer[key] & 0x80)
		return true;
	else
		return false;
}

bool GameEngine_Input::isLBPress() {
	if (m_MouseState.rgbButtons[0] & 0x80)
		return true;
	else
		return false;
}

bool GameEngine_Input::isRBPress() {
	if (m_MouseState.rgbButtons[1] & 0x80)
		return true;
	else
		return false;
}

bool GameEngine_Input::isMBPress() {
	if (m_MouseState.rgbButtons[2] & 0x80)
		return true;
	else
		return false;
}

void GameEngine_Input::AcquireDevice() {
	m_pKeyboard->Acquire();
	m_pMouse->Acquire();
}

void GameEngine_Input::UnacquireDevice() {
	m_pKeyboard->Unacquire();
	m_pMouse->Unacquire();
}
