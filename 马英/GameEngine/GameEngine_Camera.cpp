#include "GameEngine_Camera.h"
GameEngine_Camera::GameEngine_Camera(D3DXVECTOR3 pos, D3DXVECTOR3 r, D3DXVECTOR3 u, D3DXVECTOR3 l) {
	m_pos = pos;
	m_look = l;
	m_right = r;
	m_up = u;
}
void GameEngine_Camera::GetMatrixView(D3DXMATRIX& m) {
	D3DXVec3Normalize(&m_look, &m_look);
	D3DXVec3Cross(&m_up, &m_look, &m_right);
	D3DXVec3Normalize(&m_up, &m_up);
	D3DXVec3Cross(&m_right, &m_up, &m_look);
	D3DXVec3Normalize(&m_right, &m_right);
	m._11 = m_right.x; m._12 = m_up.x; m._13 = m_look.x; m._14 = 0;
	m._21 = m_right.y; m._22 = m_up.y; m._23 = m_look.y; m._24 = 0;
	m._31 = m_right.z; m._32 = m_up.z; m._33 = m_look.z; m._34 = 0;
	m._41 = -D3DXVec3Dot(&m_pos, &m_right);
	m._42 = -D3DXVec3Dot(&m_pos, &m_up);
	m._43 = -D3DXVec3Dot(&m_pos, &m_look);
	m._44 = 1;

}
void GameEngine_Camera::CameraRotation_RIGHT(float angle){
	D3DXMATRIX R;
	D3DXMatrixRotationAxis(&R, &m_right, angle);
	D3DXVec3TransformCoord(&m_up, &m_up, &R);
	D3DXVec3TransformCoord(&m_look, &m_look, &R);

}
void GameEngine_Camera::CameraRotation_LOOK(float angle) {
	D3DXMATRIX R;
	D3DXMatrixRotationAxis(&R, &m_look, angle);
	D3DXVec3TransformCoord(&m_up, &m_up, &R);
	D3DXVec3TransformCoord(&m_right, &m_right, &R);

}
void GameEngine_Camera::CameraRotation_UP(float angle) {
	D3DXMATRIX R;
	D3DXMatrixRotationAxis(&R, &m_up, angle);
	D3DXVec3TransformCoord(&m_right, &m_right, &R);
	D3DXVec3TransformCoord(&m_look, &m_look, &R);

}
void GameEngine_Camera::CameraMove_LR(float f) {
	m_pos += m_right *f;
}
void GameEngine_Camera::CameraMove_UD(float f) {
	m_pos += m_up * f;
}
void GameEngine_Camera::CameraMove_FN(float f) {
	m_pos += m_look * f;
}
