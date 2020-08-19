#include "WobbleAnimation.h"
#include <math.h>

void CWobbleAnimation::Update(float _deltaSeconds)
{
	if (!m_IsRunning)
		return;

	m_VerticalDegreeCounter += m_VerticalWobbleSpeed; // increase by speed
	m_VerticalDegreeCounter %= 360; // modulo to keep it in range of 0 to 359

	m_HorizontalDegreeCounter += m_HorizontalWobbleSpeed;
	m_HorizontalDegreeCounter %= 360;

	float verticalFactor = sinf(m_VerticalDegreeCounter * M_PI / 180); // sinus value
	float horizontalFactor = sinf(m_HorizontalDegreeCounter * M_PI / 180);

	verticalFactor *= verticalFactor > 0 ? m_VerticalStretchIntensity : m_VerticalSqueezeIntensity; // mutiply by (when positive) stretch / (when negative) squeeze
	horizontalFactor *= horizontalFactor > 0 ? m_HorizontalStretchIntensity : m_HorizontalSqueezeIntensity;

	m_pAnimationRect->h = m_baseRect.h + verticalFactor;
	m_pAnimationRect->w = m_baseRect.w + horizontalFactor;
}

void CWobbleAnimation::InitVertical(float _stretch, float _squeeze, int _speed)
{
	m_VerticalStretchIntensity = _stretch;
	m_VerticalSqueezeIntensity = _squeeze;
	m_VerticalWobbleSpeed = _speed;
}

void CWobbleAnimation::InitHorizontal(float _stretch, float _squeeze, int _speed)
{
	m_HorizontalStretchIntensity = _stretch;
	m_HorizontalSqueezeIntensity = _squeeze;
	m_HorizontalWobbleSpeed = _speed;
}
