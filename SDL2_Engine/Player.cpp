#pragma region engine include
#include "Input.h"
#include "Renderer.h"
#include "ContentManagement.h"
#include "Physic.h"
#include "Macro.h"
#pragma endregion

#pragma region game include
#include "Player.h"
#include "Game.h"
#pragma endregion

#pragma region std includes
#include <math.h>
using namespace std;
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

void GPlayer::Rotate() // Jonas
{
	float angle = 0.0f;
	// calculate cursor world position
	SVector2 mouseWorldPos = CInput::GetMousePosition();
	mouseWorldPos.X += RENDERER->GetCamera().X - SCREEN_WIDTH * 0.5f;
	mouseWorldPos.Y += RENDERER->GetCamera().Y - SCREEN_HEIGHT * 0.5f;

	// angle between player and mouse position using atan2 and radiant to degree constant
	if (mouseWorldPos.Y < m_position.Y)
	{
		angle = atan2(mouseWorldPos.Y - m_position.Y, mouseWorldPos.X - m_position.X) * (180 / M_PI);
	}
	else
	{
		angle = atan2(m_position.Y - mouseWorldPos.Y, m_position.X - mouseWorldPos.X) * (180 / M_PI);
		angle -= 180;
	}
	angle *= -1;

	// calculating the 45° increment ((int X/45) * 45)
	angle = round(angle / 45) * 45;
	LOG(angle);

	// berechnen der neuen position vom hitzone rect mit sin() und cos()

	// neue currentAnimation anhand des winkels ermitteln
	m_mirror.X = false;
	m_mirror.Y = false;
	switch ((int)angle)
	{
	case 0:
	case 360:
	case 180:
	{
		m_pCurrentAnimation = m_pMoveRight;
		break;
	}
	case 45:
	case 135:
	{
		m_pCurrentAnimation = m_pMoveUpRight;
		break;
	}
	case 225:
	case 315:
	{
		m_pCurrentAnimation = m_pMoveDownRight;
		break;
	}
	case 90:
	case 270:
	{
		m_pCurrentAnimation = m_pMoveUpwards;
		break;
	}
	default:
		break;
	}
	// ermitteln ob die animation geflipt wird
	if (angle > 90 && angle < 270)
	{
		m_mirror.X = true;
	}

	if (angle == 270)
	{
		m_mirror.Y = true;
	}
}

void GPlayer::Move() // Jonas
{
	// movement base
	SVector2 movement = SVector2();

	// move player by input
	if (CInput::GetKey(SDL_SCANCODE_W))
		movement.Y -= 1;
	if (CInput::GetKey(SDL_SCANCODE_S))
		movement.Y += 1;
	if (CInput::GetKey(SDL_SCANCODE_A))
		movement.X -= 1;
	if (CInput::GetKey(SDL_SCANCODE_D))
		movement.X += 1;

	// set movement
	m_movement = movement;
}

void GPlayer::BasicAttack() // Jonas
{
	m_AttackCooldown = 0.0f;

	m_HitzonePosition = m_position;
	m_Hitzone.w = m_AttackRange;
	m_Hitzone.h = m_AttackRange;
	m_Hitzone.x = m_HitzonePosition.X - m_Hitzone.w * 0.5f;
	m_Hitzone.y = m_HitzonePosition.Y - m_Hitzone.h * 0.5f;

	//check every scene object
	for (CObject* pObject : CTM->GetSceneObjects())
	{
		// if its not an enemy continue to next object
		if (pObject->GetTag() != "Enemy")
			continue;

		// if collision with range rect and current object rect
		if (RectRectCollision(m_Hitzone, ((CTexturedObject*)pObject)->GetRect()))
		{
			// remove object and stop checkig other objects
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