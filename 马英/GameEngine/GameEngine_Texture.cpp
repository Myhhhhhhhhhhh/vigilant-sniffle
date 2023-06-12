#include "GameEngine_Texture.h"
#include"GameEngine_SceneManager.h"
GameEngine_Texture::GameEngine_Texture(GameEngine_SceneManager* pScene) {
	m_pSceneManager = pScene;
	m_pTexture = NULL;
}
bool GameEngine_Texture::LoadTextureFromFile(
	LPCTSTR szTextureFileName//纹理图片名称，带路径
) {
	int hr = D3DXCreateTextureFromFile(m_pSceneManager->GetDevice(), szTextureFileName, &m_pTexture);
	if (FAILED(hr))
		return false;

	m_pSceneManager->GetDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	m_pSceneManager->GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pSceneManager->GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	return true;
}
GameEngine_Texture::~GameEngine_Texture() {
	m_pSceneManager = NULL;
	if (m_pTexture) {
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
