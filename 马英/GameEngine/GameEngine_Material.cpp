#include "GameEngine_Material.h"
void GameEngine_Material::SetMaterial(
    D3DXCOLOR cAmbient, //�����ⷴ����ɫ
    D3DXCOLOR cDiffuse, //����ⷴ����ɫ
    D3DXCOLOR cSpecular,//����ⷴ����ɫ 
    D3DXCOLOR Emissive,//�Է�����ɫ 
    float fPower//���
) {

    m_Material.Ambient = cAmbient;
    m_Material.Diffuse = cDiffuse;
    m_Material.Specular = cSpecular;
    m_Material.Emissive = Emissive;
    m_Material.Power = fPower;
}
