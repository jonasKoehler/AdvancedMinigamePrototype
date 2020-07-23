#pragma region game include
#include "Enemy.h"
#pragma endregion

#pragma region public override function
// update every frame
void GEnemy::Update(float _deltaSeconds)
{
	// set movement depending on movement right
	if (m_movementRight)
		m_movement.X = 1.0f;
	else
		m_movement.X = -1.0f;

	// increase time in movement direction
	m_timerInMovement += _deltaSeconds;

	// if time over one second
	if (m_timerInMovement >= 1.0f)
	{
		// change movement direction and reset timer
		m_movementRight = !m_movementRight;
		m_timerInMovement = 0.0f;
	}

	// update parent
	CMoveObject::Update(_deltaSeconds);
}

// render every frame
void GEnemy::Render()
{
	CMoveObject::Render();
}
#pragma endregion