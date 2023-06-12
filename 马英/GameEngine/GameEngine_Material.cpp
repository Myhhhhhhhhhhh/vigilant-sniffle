#include "GameEngine_Material.h"
void GameEngine_Material::SetMaterial(
    D3DXCOLOR cAmbient, //环境光反射颜色
    D3DXCOLOR cDiffuse, //漫射光反射颜色
    D3DXCOLOR cSpecular,//镜面光反射颜色 
    D3DXCOLOR Emissive,//自发光颜色 
    float fPower//锐度
) {

    m_Material.Ambient = cAmbient;
    m_Material.Diffuse = cDiffuse;
    m_Material.Specular = cSpecular;
    m_Material.Emissive = Emissive;
    m_Material.Power = fPower;
}
