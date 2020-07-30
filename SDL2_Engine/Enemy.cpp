#pragma region game include
#include "Enemy.h"
#include "Physic.h"
#include "ContentManagement.h"


class GPlayer;
#pragma endregion

#pragma region public override function
// update every frame
void GEnemy::Update(float _deltaSeconds)
{
	
	if(m_movetoPlayer)
	{
			m_movement.X = 1.0f;
			m_mirror.X = false;
		}
	else
	{
		m_movement.X = -1.0f;
		m_mirror.X = true;
	}


	// increase time in movement direction
	m_timerInMovement += _deltaSeconds;

	// if time over one second
	if (m_timerInMovement >= 1.0f)
	{
		// change movement direction and reset timer
		m_movetoPlayer = !m_movetoPlayer;
		m_timerInMovement = 0.0f;
	}

	// update parent
	CMoveObject::Update(_deltaSeconds);

	// update current animation
	m_anim.Update(_deltaSeconds);
}

// render every frame
void GEnemy::Render()
{	
	// render parent
	CMoveObject::Render();
}


void GEnemy::Damage(float _damage)
{
	if (_damage < 0)
		return;

	m_health -= _damage;
	if (m_health < 0)
	{
		m_health = 0;
	}
}


void GEnemy::TakeDamage(GPlayer* _defender)
{

}
#pragma endregion