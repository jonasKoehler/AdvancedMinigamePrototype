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
	m_animation.Update(_deltaSeconds);
	CMoveObject::Update(_deltaSeconds); // call update of direct parent: entity
}

// render every frame
void GEnemy::Render()
{
	// render parent
	CMoveObject::Render();
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
	m_movement.X = 0;
	m_movement.Y = 0;

	if (!m_playerpos)
	{
		//Find the Player and his Position
		for (CObject* pObject : CTM->GetPersistentObjects())
		{
			// if its not an enemy continue to next object
			if (pObject->GetTag() != "Player")
				continue;
			else
			{
				m_playerpos = pObject->GetPositionPointer();
			}
		}
		return; // do nothing if playerpos is nullpointer
	}

	if (!m_Engaged)
	{
		SVector2 distance = *m_playerpos - m_position;
		if (distance.SqrMagnitude() <= pow(m_DetectionRange, 2))
			m_Engaged = true;
		return;
	}

	//Check Position X and Walks to this Position
	if (m_position.X > m_playerpos->X)
	{
		m_movement.X = -1.0f; //Walks to his Position
	}
	if (m_position.X < m_playerpos->X)
	{
		m_movement.X = 1.0f;
	}

	//Check Position Y and Walks to this Position
	if (m_position.Y > m_playerpos->Y)
	{
		m_movement.Y = -1.0f;
	}
	if (m_position.Y < m_playerpos->Y)
	{
		m_movement.Y = 1.0f;
	}
}

void GEnemy::OnCollisionEnter(CObject* pObject)
{
	if (pObject->GetTag() == "Player")
	{
		((GEntity*)pObject)->TakeDamage(m_damage);
	}
}
#pragma endregion