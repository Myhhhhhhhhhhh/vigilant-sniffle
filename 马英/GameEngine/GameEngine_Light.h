#pragma once
#include"d3d9.h"
#include"d3dx9.h"
class GameEngine_Light
{
private:
	D3DLIGHT9 m_Light;
public:
    void SetDirection(
        D3DXVECTOR3 Dir,//���߷��� 
        D3DXCOLOR cAmbient, //��������ɫ
        D3DXCOLOR cDiffuse, //�������ɫ
        D3DXCOLOR cSpecular//�������ɫ
    );
    D3DLIGHT9* GetLight() { return &m_Light; }
};

