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
#include "EndScene.h"
#pragma endregion

#pragma region other includes
#include <math.h>
#pragma endregion


#pragma region public override function
void GPlayer::Update(float _deltaSeconds)
{
	Rotate();

	m_pHitzoneTexture->Update(_deltaSeconds); // update hitzone after changes in Rotate()
	m_pCurrentWalkAnimation->Update(_deltaSeconds); // update current animation after changes in Rotate()

	Move(_deltaSeconds);
	// if player was hit
	if (m_IsInvincible >= 0)
	{
		m_IsInvincible = std::fmax(0, m_IsInvincible - _deltaSeconds * 1000);

		if (m_IsInvincible % 100 < 10)
		{
			m_render = !m_render;
		}

		if (m_IsInvincible == 0)
		{
			m_render = true;
			m_IsInvincible = -1;
		}
	}

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

	for (CObject* pObject : m_colObject)
	{
		if (pObject->GetTag() == "Exit")
		{
			if (RectRectCollision(m_Hitzone, ((CTexturedObject*)pObject)->GetRect()))
			{
				ReachExit();
			}
		}
	}

	m_pUpperBody->SetRenderingIndicator(m_render);
	m_pUpperBody->SetPosition(SVector2(m_position.X, m_position.Y - GConfig::s_PlayerBottomHeight * 0.5));
	m_pUpperBody->Update(_deltaSeconds);

	m_pLowerBody->SetRenderingIndicator(m_render);
	m_pLowerBody->SetPosition(SVector2(m_position.X, m_position.Y + GConfig::s_PlayerTopHeight * 0.5));
	m_pLowerBody->Update(_deltaSeconds);

	CheckIfDead();
	RENDERER->SetCamera(m_position); // set camera position to player position
	CMoveObject::Update(_deltaSeconds); // update parent
}

void GPlayer::Render()
{
	m_pLowerBody->SetSrcRect(m_pCurrentWalkAnimation->GetNewSourceRect()); // set player source rect by current animation
	m_pHitzoneTexture->SetSrcRect(m_pAttack->GetNewSourceRect()); // set hitzone animation src rect

	m_pHitzoneTexture->Render();
	m_pUpperBody->Render();
	m_pLowerBody->Render();
	CTexturedObject::Render(); // render parent
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

	// calculating the 45° increment ((int X/45) * 45)
	angle = round(angle / 45) * 45;

	// calculate new hitzone rect position sin() und cos(), pi/180 = degree to radiant conversion since cos & sin use radiants in c++
	int hitzonePosX = m_position.X + (cos(angle * M_PI / 180) * (GConfig::s_PlayerWidth * 0.5 + m_Hitzone.w * 0.5));
	int hitzonePosY = m_position.Y - (sin(angle * M_PI / 180) * (GConfig::s_PlayerTotalHeight * 0.5 + m_Hitzone.h * 0.5));

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
	{
		m_pCurrentWalkAnimation = m_WalkAnimations[EPlayerWalkDirection::Right];
		m_pUpperBody->SetSrcRect(m_LookDirectionSrcRects[EPlayerLookDirection::Right]);
		break;
	}

	case 45:
	{
		m_pCurrentWalkAnimation = m_WalkAnimations[EPlayerWalkDirection::UpRight];
		m_pUpperBody->SetSrcRect(m_LookDirectionSrcRects[EPlayerLookDirection::UpRight]);
		break;
	}
	case 90:
	{
		m_pCurrentWalkAnimation = m_WalkAnimations[EPlayerWalkDirection::Up];
		m_pUpperBody->SetSrcRect(m_LookDirectionSrcRects[EPlayerLookDirection::Up]);
		break;
	}
	case 135:
	{
		m_pCurrentWalkAnimation = m_WalkAnimations[EPlayerWalkDirection::UpLeft];
		m_pUpperBody->SetSrcRect(m_LookDirectionSrcRects[EPlayerLookDirection::UpLeft]);
		break;
	}
	case 180:
	{
		m_pCurrentWalkAnimation = m_WalkAnimations[EPlayerWalkDirection::Left];
		m_pUpperBody->SetSrcRect(m_LookDirectionSrcRects[EPlayerLookDirection::Left]);
		break;
	}
	case 225:
	{
		m_pCurrentWalkAnimation = m_WalkAnimations[EPlayerWalkDirection::DownLeft];
		m_pUpperBody->SetSrcRect(m_LookDirectionSrcRects[EPlayerLookDirection::DownLeft]);
		break;
	}
	case 270:
	{
		m_pCurrentWalkAnimation = m_WalkAnimations[EPlayerWalkDirection::Down];
		m_pUpperBody->SetSrcRect(m_LookDirectionSrcRects[EPlayerLookDirection::Down]);
		break;
	}
	case 315:
	{
		m_pCurrentWalkAnimation = m_WalkAnimations[EPlayerWalkDirection::DownRight];
		m_pUpperBody->SetSrcRect(m_LookDirectionSrcRects[EPlayerLookDirection::DownRight]);
		break;
	}

	default:
		break;
	}
}

void GPlayer::Move(float _deltaSeconds)
{
	// move player by input
	if (CInput::GetKey(SDL_SCANCODE_W))
	{
		if (m_movement.Y > 0) // invert acceleration on 180° switch
			m_movement.Y *= -0.5;
		m_movement.Y -= m_AccelerationRate * _deltaSeconds; // subtract to move up on screen
		m_movement.Y = std::fmax(m_movement.Y, -1.0f); // cannot exceed highest acceleration of -1 for y up
	}
	else if (m_movement.Y < 0) // enter if player was accelerated upwards
	{
		m_movement.Y += m_DecelerationRate * _deltaSeconds; // decelerate
		m_movement.Y = std::fmin(m_movement.Y, 0.0f); // until 0 is reached
	}

	if (CInput::GetKey(SDL_SCANCODE_S))
	{
		if (m_movement.Y < 0)
			m_movement.Y *= -0.5;
		m_movement.Y += m_AccelerationRate * _deltaSeconds; // add to move down on screen
		m_movement.Y = std::fmin(m_movement.Y, 1.0f); // cannot exceed highest acceleration of 1 for y down
	}
	else if (m_movement.Y > 0) // enter if player was accelerated downwards
	{
		m_movement.Y -= m_DecelerationRate * _deltaSeconds;
		m_movement.Y = std::fmax(m_movement.Y, 0.0f);
	}

	if (CInput::GetKey(SDL_SCANCODE_A))
	{
		if (m_movement.X > 0)
			m_movement.X *= -0.5;
		m_movement.X -= m_AccelerationRate * _deltaSeconds; // subtract to move left on screen
		m_movement.X = std::fmax(m_movement.X, -1.0f); // cannot exceed highest acceleration of -1 for x left
	}
	else if (m_movement.X < 0) // enter if player was accelerated left
	{
		m_movement.X += m_DecelerationRate * _deltaSeconds; // decelerate
		m_movement.X = std::fmin(m_movement.X, 0.0f); // until 0 is reached
	}

	if (CInput::GetKey(SDL_SCANCODE_D))
	{
		if (m_movement.X < 0)
			m_movement.X *= -0.5;
		m_movement.X += m_AccelerationRate * _deltaSeconds; // add to move right on screen
		m_movement.X = std::fmin(m_movement.X, 1.0f); // cannot exceed highest acceleration of 1 for x right
	}
	else if (m_movement.X > 0) // enter if player was accelerated right
	{
		m_movement.X -= m_DecelerationRate * _deltaSeconds;
		m_movement.X = std::fmax(m_movement.X, 0.0f);
	}
}

void GPlayer::BasicAttack()
{
	m_AttackCooldown = 0.0f;
	m_pBasicAttackSound->Play();

	//check every scene object
	for (CObject* pObject : CTM->GetSceneObjects())
	{
		// if its not an enemy continue to next object
		if (pObject->GetTag() != "Enemy")
			continue;

		// if collision with range rect and current object rect
		if (RectRectCollision(m_Hitzone, ((GEntity*)pObject)->GetRect()))
		{
			//if collision enter, the take Damage funktion is called			
			((GEntity*)pObject)->TakeDamage(m_damage);
		}
	}
}

void GPlayer::ReachExit()
{
	GAME->m_Won = true;
	CTM->RemoveObject(this);
	ENGINE->ChangeScene(new GEndScene());
}

void GPlayer::CheckIfDead()
{
	if (m_health <= 0)
	{
		GAME->m_Won = false;
		CTM->RemoveObject(this);
		ENGINE->ChangeScene(new GEndScene());
	}
}

void GPlayer::UpdateStats()
{
	map<EUpgrades, float> playerStats = GUpgradeManager::GetInstance()->GetPlayerStats();
	m_speed = playerStats[EUpgrades::MovementSpeed];
	m_damage = playerStats[EUpgrades::Damage];
	m_AttacksPerSecond = playerStats[EUpgrades::AttackSpeed];
	m_Hitzone.w = playerStats[EUpgrades::AttackRange];
	m_Hitzone.h = playerStats[EUpgrades::AttackRange];
}

void GPlayer::TakeDamage(float _damage)
{
	if (m_IsInvincible > 0)
	{
		return;
	}

	m_health -= _damage;
	m_IsInvincible = 1000;
}
#pragma endregion
