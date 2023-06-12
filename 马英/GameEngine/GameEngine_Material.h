#pragma once
#include"d3d9.h"
#include"d3dx9.h"
class GameEngine_Material
{
private:
	D3DMATERIAL9 m_Material;
public:
    void SetMaterial(
        D3DXCOLOR cAmbient, //环境光反射颜色
        D3DXCOLOR cDiffuse, //漫射光反射颜色
        D3DXCOLOR cSpecular,//镜面光反射颜色 
        D3DXCOLOR Emissive,//自发光颜色 
        float fPower//锐度
    );
    D3DMATERIAL9* GetMaterial() {
        return &m_Material;
    }

};

