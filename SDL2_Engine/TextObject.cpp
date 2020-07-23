#pragma region system include
#include <SDL_ttf.h>
#pragma endregion

#pragma region project include
#include "TextObject.h"
#include "Font.h"
#include "Renderer.h"
#include "Texture.h"
#pragma endregion

#pragma region constructor
// constructor
CTextObject::CTextObject(const char* _pText, CFont* _pFont, SVector2 _size, SVector2 _pos, SColor _color)
{
	// set variables
	m_pText = _pText;
	m_pFont = _pFont;
	m_rect.w = _size.X;
	m_rect.h = _size.Y;
	m_position = _pos;
	m_color = _color;

	// create new empty texture
	m_pTexture = new CTexture("");

	// load text
	Load();
}
#pragma endregion

#pragma region public override function
// update every frame
void CTextObject::Update(float _deltaSeconds)
{
	CTexturedObject::Update(_deltaSeconds);
}

// render every frame
void CTextObject::Render()
{
	CTexturedObject::Render();
}
#pragma endregion

#pragma region private function
// load text
void CTextObject::Load()
{
	// create sdl surface from font, text and color
	SDL_Surface* pSurface = TTF_RenderText_Blended(m_pFont->GetSdlFont(), m_pText, m_color);

	// create texture from surface
	m_pTexture->SetSdlTexture(SDL_CreateTextureFromSurface(RENDERER->GetSdlRenderer(), pSurface));

	// free surface
	SDL_FreeSurface(pSurface);
}
#pragma endregion