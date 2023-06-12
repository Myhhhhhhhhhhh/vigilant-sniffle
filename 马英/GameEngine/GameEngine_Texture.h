#pragma once
#include<d3d9.h>
#include<d3dx9.h>
class GameEngine_SceneManager;
class GameEngine_Texture

{
private:
	IDirect3DTexture9* m_pTexture;//纹理指针
	GameEngine_SceneManager* m_pSceneManager;
public:
	//加载纹理
	bool LoadTextureFromFile(
		LPCTSTR szTextureFileName//纹理图片名称，带路径
	);
	//访问纹理指针
	IDirect3DTexture9* GetTexture() {
		return m_pTexture;
	}
	GameEngine_Texture(GameEngine_SceneManager* pScene);
	virtual ~GameEngine_Texture();

};

