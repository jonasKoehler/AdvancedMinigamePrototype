#pragma region engine include
#include "Input.h"
#include "Renderer.h"
#include "ContentManagement.h"
#include "Physic.h"
#include "Macro.h"
#include "Exitzone.h"
#pragma endregion

#pragma region game include
#include "Player.h"
#include "Enemy.h"
#include "Game.h"
#include "Config.h"
#include "LoseScene.h"
#include "WinScene.h"
#pragma endregion

#pragma region other includes
#include <math.h>
#pragma endregion


#pragma region public override function
void GPlayer::Update(float _deltaSeconds)
{
	Rotate();

	m_pHitzoneTexture->Update(_deltaSeconds); // update hitzone after changes in Rotate()
	m_pCurrentAnimation->Update(_deltaSeconds); // update current animation after changes in Rotate()

	Move();

	if (m_AttackCooldown < 1.0f)
	{
		m_AttackCooldown += _deltaSeconds * m_AttacksPerSecond; // attackspeed 
		m_pAttack->Update(_deltaSeconds); // update attack animation only when the player actually attacked
	}

	// if left mouse button is pressed and attack cooled down
	if (CInput::GetMouseButton(0) && m_AttackCooldown >= 1.0f)
	{
		BasicAttack();
		m_pAttack->Start();
		// add attack sound
	}
	for (CObject* pObject : CTM->GetSceneObjects())
	{
		if (pObject->GetTag() == "Exit")
		{
			if (RectRectCollision(m_Hitzone, ((CTexturedObject*)pObject)->GetRect()))
			{
				ReachExit();
			}
		}
	}
	CheckIfDead();
	RENDERER->SetCamera(m_position); // set camera position to player position
	CMoveObject::Update(_deltaSeconds); // update parent
}

void GPlayer::Render()
{
	m_srcRect = m_pCurrentAnimation->GetNewSourceRect(); // set player source rect by current animation
	m_pHitzoneTexture->SetSrcRect(m_pAttack->GetNewSourceRect()); // set hitzone animation src rect

	m_pHitzoneTexture->Render();
	CTexturedObject::Render(); // render parent
}

void GPlayer::SetHealth(float _health)
{
	m_health = _health;
}

#pragma endregion

#pragma region private functions
void GPlayer::Rotate()
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

	// calculating the 45� increment ((int X/45) * 45)
	angle = round(angle / 45) * 45;

	// calculate new hitzone rect position sin() und cos(), pi/180 = degree to radiant conversion since cos & sin use radiants in c++
	int hitzonePosX = m_position.X + (cos(angle * M_PI / 180) * (PLAYER_WIDTH * 0.5 + m_Hitzone.w * 0.5));
	int hitzonePosY = m_position.Y - (sin(angle * M_PI / 180) * (PLAYER_HEIGHT * 0.5 + m_Hitzone.h * 0.5));

	m_Hitzone.x = hitzonePosX - m_Hitzone.w * 0.5f;
	m_Hitzone.y = hitzonePosY - m_Hitzone.h * 0.5f;

	m_pHitzoneTexture->SetPosition(SVector2(hitzonePosX, hitzonePosY));
	m_pHitzoneTexture->SetAngle(angle);

	// neue currentAnimation anhand des winkels ermitteln
	m_mirror.X = false;
	m_mirror.Y = false;
	switch ((int)angle)
	{
	case 0:
	case 360:
	case 180:
	{
		m_pCurrentAnimation = m_pLookRight;
		break;
	}
	case 45:
	case 135:
	{
		m_pCurrentAnimation = m_pLookUpRight;
		break;
	}
	case 225:
	case 315:
	{
		m_pCurrentAnimation = m_pLookDownRight;
		break;
	}
	case 90:
	{
		m_pCurrentAnimation = m_pLookUpwards;
		break;
	}
	case 270:
	{
		m_pCurrentAnimation = m_pLookDownwards;
		break;
	}
	default:
		break;
	}

	// determine flippping of animation on X axis
	if (angle > 90 && angle < 270)
	{
		m_mirror.X = true;
	}
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
		movement.X -= 1;
	if (CInput::GetKey(SDL_SCANCODE_D))
		movement.X += 1;

	// set movement
	m_movement = movement;
}

void GPlayer::BasicAttack()
{
	m_AttackCooldown = 0.0f;

	//check every scene object
	for (CObject* pObject : CTM->GetSceneObjects())
	{
		// if its not an enemy continue to next object
		if (pObject->GetTag() != "Enemy")
			continue;

		// if collision with range rect and current object rect
		if (RectRectCollision(m_Hitzone, ((CTexturedObject*)pObject)->GetRect()))
		{
			//if collision enter, the take Damage funktion is running			
			GEnemy* enemy = (GEnemy*)pObject;
			TakeDamage(m_damage, enemy);
			break;
		}
	}
}

void GPlayer::TakeDamage(float _damage, GEnemy* _enemy)
{
	float enemyhealth = _enemy->GetHealth();

	enemyhealth -= _damage;

	_enemy->SetHealth(enemyhealth);
}

void GPlayer::ReachExit()
{
	CTM->RemoveObject(this);
	ENGINE->ChangeScene(new GWinScene());
}

void GPlayer::CheckIfDead()
{
	if (m_health <= 0)
	{
		CTM->RemoveObject(this);
		ENGINE->ChangeScene(new GLoseScene());
	}
}
#pragma endregion
