#pragma region game include
#include "Enemy.h"
#pragma endregion

#pragma region public override function
// update every frame
void GEnemy::Update(float _deltaSeconds)
{
	// set movement depending on movement right
	if (m_movetoPlayer)
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
	// set source rect by current animation
	m_srcRect.x = m_anim.GetCurrentTexturePosition().X;
	m_srcRect.y = m_anim.GetCurrentTexturePosition().Y;
	m_srcRect.w = m_anim.GetSize().X;
	m_srcRect.h = m_anim.GetSize().Y;

	// render parent
	CMoveObject::Render();
}
#pragma endregion