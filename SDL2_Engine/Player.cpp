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
	Rotate();

	Move();

	if (m_AttackCooldown < 1.0f)
	{
		m_AttackCooldown += _deltaSeconds * m_AttacksPerSecond; // attackspeed 
	}

	// if left mouse button is pressed and attack cooled down
	if (CInput::GetMouseButton(0) && m_AttackCooldown >= 1.0f)
	{
		BasicAttack();
	}

	// update parent
	CMoveObject::Update(_deltaSeconds);

	// set camera position to player position
	RENDERER->SetCamera(m_position);

	// update current animation
	m_pCurrentAnimation->Update(_deltaSeconds);
}

void GPlayer::Rotate()
{
}

void GPlayer::Move()
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
		m_mirror.X = true; // remove when rotation is implemented
	}
	if (CInput::GetKey(SDL_SCANCODE_D))
	{
		movement.X += 1;
		m_mirror.X = false; // remove when rotation is implemented
	}

	// set movement
	m_movement = movement;
}

void GPlayer::BasicAttack()
{
	m_AttackCooldown = 0.0f;

	m_HitzonePosition = m_position;
	m_Hitzone.w = m_AttackRange;
	m_Hitzone.h = m_AttackRange;
	m_Hitzone.x = m_HitzonePosition.X - m_Hitzone.w * 0.5f;
	m_Hitzone.y = m_HitzonePosition.Y - m_Hitzone.h * 0.5f;

	// check every persistent object
	for (CObject* pObject : CTM->GetSceneObjects())
	{
		// if this continue to next object
		if (pObject->GetTag() != "Enemy")
			continue;

		// if collision with range rect and current object rect
		if (RectRectCollision(m_Hitzone, ((CTexturedObject*)pObject)->GetRect()))
		{
			// remove object and stop checkig other objects (remove only one enemy per key press)
			CTM->RemoveObject(pObject); // replace with enemy take damage function
			break; // remove when hp system is implemented
		}
	}
}

// render every frame
void GPlayer::Render()
{
	// set source rect by current animation
	m_srcRect.x = m_pCurrentAnimation->GetCurrentTexturePosition().X;
	m_srcRect.y = m_pCurrentAnimation->GetCurrentTexturePosition().Y;
	m_srcRect.w = m_pCurrentAnimation->GetSize().X;
	m_srcRect.h = m_pCurrentAnimation->GetSize().Y;

	// render parent
	CTexturedObject::Render();
}
#pragma endregion