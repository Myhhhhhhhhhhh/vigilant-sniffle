#include "GameEngine_Light.h"
void GameEngine_Light::SetDirection(
    D3DXVECTOR3 Dir,//光线方向 
    D3DXCOLOR cAmbient, //背景光颜色
    D3DXCOLOR cDiffuse, //漫射光颜色
    D3DXCOLOR cSpecular//镜面光颜色
) {
	m_Light.Type = D3DLIGHT_DIRECTIONAL;
	m_Light.Direction =Dir;
	m_Light.Diffuse = cDiffuse;
	m_Light.Specular = cSpecular;
	m_Light.Ambient = cAmbient;
}
