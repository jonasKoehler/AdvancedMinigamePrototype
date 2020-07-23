#pragma region engine include
#include "Input.h"
#include "Renderer.h"
#include "ContentManagement.h"
#include "Physic.h"
#pragma endregion

#pragma region game include
#include "Player.h"
#include "Game.h"
#pragma endregion

#pragma region public override function
// update every frame
void GPlayer::Update(float _deltaSeconds)
{
	// movement base
	SVector2 movement = SVector2();

	// move player by input
	if (CInput::GetKey(SDL_SCANCODE_W))
		movement.Y -= 1;
	if (CInput::GetKey(SDL_SCANCODE_S))
		movement.Y += 1;
	if (CInput::GetKey(SDL_SCANCODE_A))
	{
		movement.X -= 1;
		m_mirror.X = true;
	}
	if (CInput::GetKey(SDL_SCANCODE_D))
	{
		movement.X += 1;
		m_mirror.X = false;
	}

	// if left mouse button is pressed
	if (CInput::GetKeyDown(SDL_SCANCODE_RETURN))
	{
		m_Hitzone.w = 64;
		m_Hitzone.h = 64;
		m_Hitzone.x = m_HitzonePosition.X - m_Hitzone.w * 0.5f;
		m_Hitzone.y = m_HitzonePosition.Y - m_Hitzone.h * 0.5f;

		// check every persistent object
		for (CObject* pObject : CTM->GetPersistentObjects())
		{
			// if this continue to next object
			if (pObject == this)
				continue;

			// if collision with range rect and current object rect
			if (RectRectCollision(m_Hitzone, ((CTexturedObject*)pObject)->GetRect()))
			{
				// remove object and stop checkig other objects (remove only one enemy per key press)
				CTM->RemoveObject(pObject);
				break;
			}
		}
	}

	// set movement
	m_movement = movement;

	// update parent
	CMoveObject::Update(_deltaSeconds);

	// set camera position to player position
	RENDERER->SetCamera(m_position);
}

// render every frame
void GPlayer::Render()
{
	// render parent
	CTexturedObject::Render();
}
#pragma endregion