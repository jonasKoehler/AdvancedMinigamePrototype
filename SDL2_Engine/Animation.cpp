#pragma region project include
#include "Animation.h"
#pragma endregion

#pragma region public function
// update every frame
void CAnimation::Update(float _deltaSeconds)
{
	// skip following logic if paused
	if (m_isStopped)
	{
		return;
	}

	// increase timer
	m_timer += _deltaSeconds;

	// if timer is higher than time needed for a single frame
	if (m_timer > m_animationTime / m_count)
	{
		// increase current frame index
		m_current++;

		// if frame index higher than count reset current
		if (m_current > m_count - 1)
			m_current = 0;

		// reset timer
		m_timer = 0.0f;
	}
}

// get current position of the animation in the texture
SVector2 CAnimation::GetCurrentTexturePosition()
{
	// return vector
	SVector2 v = SVector2();

	// get current position of animation by current index and width
	v.X = m_startPos.X + m_current * m_size.X;
	v.Y = m_startPos.Y;

	// return position
	return v;
}

SRect CAnimation::GetNewSourceRect()
{
	return SRect(GetSize(), GetCurrentTexturePosition());
}

void CAnimation::Stop(bool _reset)
{
	m_isStopped = true;

	if (_reset)
	{
		m_timer = 0.0f;
		m_current = 0;
	}
}
#pragma endregion