#pragma region game include
#include "Enemy.h"
#include "ContentManagement.h"
#include "Player.h"
#pragma endregion

#pragma region public override function
// update every frame
void GEnemy::Update(float _deltaSeconds)
{
	CheckIfDead();
	MoveToPlayer();
	CMoveObject::Update(_deltaSeconds);
}

// render every frame
void GEnemy::Render()
{
	// render parent
	CMoveObject::Render();
}

//Search for the Position and then Move to Player
void GEnemy::SetHealth(float _health)
{
	m_health = _health;
}

void GEnemy::CheckIfDead()
{
	if (m_health <= 0)
	{
		CTM->RemoveObject(this);
	}
}

void GEnemy::MoveToPlayer()
{
	//Find the Player and his Position
	for (CObject* pObject : CTM->GetPersistentObjects())
	{
		// if its not an enemy continue to next object
		if (pObject->GetTag() != "Player")
			continue;
		else
		{
			m_playerpos = pObject->GetPosition();
		}
	}

	//Check Position X and Walks to this Position
	if (m_position.X >= m_playerpos.X)
	{
		m_movement.X = -1.0f; //Walks to his Position
	}
	if (m_position.X <= m_playerpos.X)
	{
		m_movement.X = 1.0f;
	}
	if (m_position.X == m_playerpos.X)
	{
		m_movement.X = 0;
	}

	//Check Position Y and Walks to this Position
	if (m_position.Y >= m_playerpos.Y)
	{
		m_movement.Y = -1.0f;
	}
	if (m_position.Y <= m_playerpos.Y)
	{
		m_movement.Y = 1.0f;
	}
	if (m_position.Y == m_playerpos.Y)
	{
		m_movement.Y = 0;
	}
}

void GEnemy::OnCollisionEnter(CObject* pObject)
{
	if (pObject->GetTag() == "Player")
	{
		GPlayer* player = (GPlayer*)pObject;
		TakeDamage(m_damage, player);
	}
}

void GEnemy::TakeDamage(float _damage, GPlayer* _player)
{
	float playerhealth = _player->GetHealth();
	playerhealth -= _damage;
	_player->SetHealth(playerhealth);
}

#pragma endregion