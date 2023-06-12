#pragma once
#include"d3d9.h"
#include"d3dx9.h"
class GameEngine_Material
{
private:
	D3DMATERIAL9 m_Material;
public:
    void SetMaterial(
        D3DXCOLOR cAmbient, //�����ⷴ����ɫ
        D3DXCOLOR cDiffuse, //����ⷴ����ɫ
        D3DXCOLOR cSpecular,//����ⷴ����ɫ 
        D3DXCOLOR Emissive,//�Է�����ɫ 
        float fPower//���
    );
    D3DMATERIAL9* GetMaterial() {
        return &m_Material;
    }

};

