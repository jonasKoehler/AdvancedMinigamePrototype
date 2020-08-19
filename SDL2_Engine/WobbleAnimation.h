#pragma once
#pragma region engine includes
#include "Rect.h"
#pragma endregion

/// <summary>
/// A class for a squeeze and stretch animation (wobble in short)
/// Call the Init() function per axis as desired
/// </summary>
class CWobbleAnimation // by Jonas
{
#pragma region constructor / destructor
public:
	CWobbleAnimation(SRect* _rect) 
	{
		m_pAnimationRect = _rect;
		m_baseRect = *_rect;
	}

	~CWobbleAnimation() {}
#pragma endregion

#pragma region public member functions
public:
	void Update(float _deltaSeconds);

	/// <summary>
	/// Setup the vertical wobble animation
	/// </summary>
	/// <param name="_stretch">Stretch intensity</param>
	/// <param name="_squeeze">Squeeze intensity</param>
	/// <param name="_speed">Wobble Speed</param>
	void InitVertical(float _stretch, float _squeeze, int _speed);

	/// <summary>
	/// Setup the horizontal wobble animation
	/// </summary>
	/// <param name="_stretch">Stretch intensity</param>
	/// <param name="_squeeze">Squeeze intensity</param>
	/// <param name="_speed">Wobble Speed</param>
	void InitHorizontal(float _stretch, float _squeeze, int _speed);

	/// <summary>
	/// Stops the animation and resets the rect
	/// </summary>
	inline void Stop() 
	{ 
		m_IsRunning = false; 
		*m_pAnimationRect = m_baseRect;
	}

	/// <summary>
	/// Starts the animation. Animation is started by default. Only call this to restart it.
	/// </summary>
	inline void Start() { m_IsRunning = true; }
#pragma endregion

#pragma region private member variables
private:
	SRect* m_pAnimationRect = nullptr; // rect that the animation is applied to
	SRect m_baseRect; // base rect values of the animRect for resetting

	float m_VerticalStretchIntensity = 0; // the intensity of the vertical stretch
	float m_VerticalSqueezeIntensity = 0; // the intensity of the vertical squeeze
	int m_VerticalWobbleSpeed = 0; // speed of the animation on the vertical axis
	int m_VerticalDegreeCounter = 0; // used for sin calculation

	float m_HorizontalStretchIntensity = 0; // the intensity of the Horizontal stretch
	float m_HorizontalSqueezeIntensity = 0; // the intensity of the Horizontal squeeze
	int m_HorizontalWobbleSpeed = 0; // speed of the animation on thje horizontal axis
	int m_HorizontalDegreeCounter = 0; // used for sin calculation

	bool m_IsRunning = true; // toggles if the animation is played or paused
#pragma endregion


};

