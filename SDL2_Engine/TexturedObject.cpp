#pragma region project include
#include "TexturedObject.h"
#include "TextureManagement.h"
#include "Texture.h"
#include "Renderer.h"
#pragma endregion

#pragma region constructor
// constructor
CTexturedObject::CTexturedObject(const char* _pFileName, SVector2 _size, SVector2 _pos)
{
	// create texture, set rect size and object position
	m_pTexture = TTM->GetTexture(_pFileName);
	m_rect.w = _size.X;
	m_rect.h = _size.Y;
	m_position = _pos;
}
#pragma endregion

#pragma region public override function
// update every frame
void CTexturedObject::Update(float _deltaSeconds)
{
	// set rect so that position of object in center of rect is
	m_rect.x = m_position.X - m_rect.w * 0.5f;
	m_rect.y = m_position.Y - m_rect.h * 0.5f;
}

// render every frame
void CTexturedObject::Render()
{
	// return if object shouldnt be rendered
	if (!m_render)
		return;
	// render texture at rect with angle, source rect and in world or screen space
	RENDERER->RenderTexture(m_pTexture, &m_rect, m_angle, &m_srcRect, m_inWorld, m_mirror);
}
#pragma endregion