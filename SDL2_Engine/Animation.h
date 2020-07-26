#pragma once

#pragma region project include
#include "Vector2.h"
#pragma endregion

/// <summary>
/// class for animation values
/// </summary>
class CAnimation
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_startPos">start position of animation in texture</param>
	/// <param name="_size">size of a single animation frame</param>
	/// <param name="_animationTime">complete length of animation in seconds</param>
	/// <param name="_count">number of frames, default 1</param>
	CAnimation(SVector2 _startPos, SVector2 _size, float _animationTime ,int _count = 1)
	{
		// set values
		m_startPos = _startPos;
		m_size = _size;
		m_count = _count;
		m_animationTime = _animationTime;
	}
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// set time that is needed for a complete animation
	/// </summary>
	/// <param name="_animTime">time that is needed for a complete animation in seconds</param>
	inline void SetAnimationTime(float _animTime) { m_animationTime = _animTime; }

	/// <summary>
	/// get size of a single animation frame
	/// </summary>
	/// <returns>size of a single animation frame</returns>
	inline SVector2 GetSize() { return m_size; }
#pragma endregion
	
#pragma region public function
	/// <summary>
	/// update every frame
	/// </summary>
	/// <param name="_deltaSeconds">time since last frame</param>
	void Update(float _deltaSeconds);

	/// <summary>
	/// get current position of the animation in the texture
	/// </summary>
	/// <returns>current position of the animation in the texture</returns>
	SVector2 GetCurrentTexturePosition();
#pragma endregion

protected:
#pragma region protected primitive variable
	/// <summary>
	/// current frame of animation index
	/// </summary>
	int m_current = 0;

	/// <summary>
	/// number of frames for complete animation
	/// </summary>
	int m_count = 0;

	/// <summary>
	/// time that is needed for a complete animation
	/// </summary>
	float m_animationTime = 0.0f;

	/// <summary>
	/// time in current animation frame
	/// </summary>
	float m_timer = 0.0f;
#pragma endregion

#pragma region protected variable
	/// <summary>
	/// start position of animation in texture
	/// </summary>
	SVector2 m_startPos = SVector2();

	/// <summary>
	/// size of a single animation frame
	/// </summary>
	SVector2 m_size = SVector2();
#pragma endregion
};