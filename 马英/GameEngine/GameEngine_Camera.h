#pragma once
#include<d3dx9.h>
class GameEngine_Camera
{
private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_right;
	D3DXVECTOR3 m_up;

	D3DXVECTOR3 m_look;
public:
	GameEngine_Camera(D3DXVECTOR3 pos, D3DXVECTOR3 r, D3DXVECTOR3 u, D3DXVECTOR3 l);
	void GetMatrixView(D3DXMATRIX& m);
	void CameraRotation_RIGHT(float angle);
	void CameraRotation_UP(float angle);
	void CameraRotation_LOOK(float angle);
	void CameraMove_LR(float f);
	void CameraMove_UD(float f);
	void CameraMove_FN(float f);
	D3DXVECTOR3 GetPos() { return m_pos; }
};

