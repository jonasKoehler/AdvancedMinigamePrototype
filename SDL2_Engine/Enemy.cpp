#pragma region game include
#include "Enemy.h"
#include "Player.h"
#include "ContentManagement.h"
#pragma endregion

#pragma region public override function
// update every frame
void GEnemy::Update(float _deltaSeconds)
{
	MoveToPlayer();
	
		
		CMoveObject::Update(_deltaSeconds);

		
}

// render every frame
void GEnemy::Render()
{
	
	// render parent
	CMoveObject::Render();
}

void GEnemy::MoveToPlayer()
{
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

	if (m_position.X >= m_playerpos.X)
	{
		m_movement.X = -1.0f;
	}
	if (m_position.X <= m_playerpos.X)
	{
		m_movement.X = 1.0f;
	}
	if (m_position.Y >= m_playerpos.Y)
	{
		m_movement.Y = -1.0f;
	}
	if (m_position.Y <= m_playerpos.Y)
	{
		m_movement.Y = 1.0f;
	}


	if (m_position.X == m_playerpos.X)
	{
		m_movement.X = 0;
	}
	if (m_position.Y == m_playerpos.Y)
	{
		m_movement.Y = 0;
	}

	
}
#pragma endregion