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

	// set falltime negativ to jump
	if (CInput::GetKeyDown(SDL_SCANCODE_SPACE) && !m_fallTime)
		m_fallTime -= 0.6f;

	// if key enter / return pressed
	if (CInput::GetKeyDown(SDL_SCANCODE_RETURN))
	{
		// rect to check nearby enemies
		SRect rect;
		rect.w = 512;
		rect.h = 512;
		rect.x = m_position.X - 256;
		rect.y = m_position.Y - 256;

		// check every persistent object
		for (CObject* pObject : CTM->GetPersistentObjects())
		{
			// if this continue to next object
			if (pObject == this)
				continue;

			// if collision with range rect and current object rect
			if (RectRectCollision(rect, ((CTexturedObject*)pObject)->GetRect()))
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