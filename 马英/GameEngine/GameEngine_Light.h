#pragma once
#include"d3d9.h"
#include"d3dx9.h"
class GameEngine_Light
{
private:
	D3DLIGHT9 m_Light;
public:
    void SetDirection(
        D3DXVECTOR3 Dir,//光线方向 
        D3DXCOLOR cAmbient, //背景光颜色
        D3DXCOLOR cDiffuse, //漫射光颜色
        D3DXCOLOR cSpecular//镜面光颜色
    );
    D3DLIGHT9* GetLight() { return &m_Light; }
};

