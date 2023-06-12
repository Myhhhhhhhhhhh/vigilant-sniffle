#include "GameEngine_Light.h"
void GameEngine_Light::SetDirection(
    D3DXVECTOR3 Dir,//���߷��� 
    D3DXCOLOR cAmbient, //��������ɫ
    D3DXCOLOR cDiffuse, //�������ɫ
    D3DXCOLOR cSpecular//�������ɫ
) {
	m_Light.Type = D3DLIGHT_DIRECTIONAL;
	m_Light.Direction =Dir;
	m_Light.Diffuse = cDiffuse;
	m_Light.Specular = cSpecular;
	m_Light.Ambient = cAmbient;
}
