#pragma region system include
#include <SDL_image.h>
#pragma endregion

#pragma region project include
#include "Texture.h"
#include "Helper.h"
#include "Renderer.h"
#pragma endregion

#pragma region constructor
// constructor
CTexture::CTexture(const char* _pFile)
{
	// if file valid and not empty
	if(_pFile && _pFile != "")
		// load image from file
		m_pSdlTexture = IMG_LoadTexture(RENDERER->GetSdlRenderer(), GetAssetPath(_pFile).c_str());
}
#pragma endregion

#pragma region destructor
// destructor
CTexture::~CTexture()
{
	// destroy sdl texture
	SDL_DestroyTexture(m_pSdlTexture);
}
#pragma endregion

#pragma region public function
// set sdl texture
void CTexture::SetSdlTexture(SDL_Texture* _pSdlTexture)
{
	// if sdl texture valid destroy old texture
	if (m_pSdlTexture)
		SDL_DestroyTexture(m_pSdlTexture);

	// set new sdl texture reference
	m_pSdlTexture = _pSdlTexture;
}
#pragma endregion