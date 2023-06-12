#pragma once
#include<d3d9.h>
#include<d3dx9.h>
class GameEngine_SceneManager;
class GameEngine_Texture

{
private:
	IDirect3DTexture9* m_pTexture;//����ָ��
	GameEngine_SceneManager* m_pSceneManager;
public:
	//��������
	bool LoadTextureFromFile(
		LPCTSTR szTextureFileName//����ͼƬ���ƣ���·��
	);
	//��������ָ��
	IDirect3DTexture9* GetTexture() {
		return m_pTexture;
	}
	GameEngine_Texture(GameEngine_SceneManager* pScene);
	virtual ~GameEngine_Texture();

};

