#pragma region project include
#include "Mouse.h"
#include "Input.h"
#pragma endregion

#pragma region public override function
// update every frame
void CMouse::Update(float _deltaSeconds)
{
	// set mouse position
	m_position = CInput::GetMousePosition();

	// set rect position
	m_rect.x = m_position.X - m_center.X * m_rect.w;
	m_rect.y = m_position.Y - m_center.Y * m_rect.h;
}

// render every frame
void CMouse::Render()
{
	CTexturedObject::Render();
}
#pragma endregion