#pragma once

#pragma region system include
#include <time.h>
#pragma endregion

/// <summary>
/// time class
/// </summary>
class CTime
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	CTime() {}
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// get current frames per second
	/// </summary>
	/// <returns>current frames per second</returns>
	static inline int GetFPS() { return s_fps; }

	/// <summary>
	/// get time since last frame
	/// </summary>
	/// <returns>time since last frame in seconds</returns>
	static inline float GetDeltaSeconds() { return s_deltaSeconds; }
#pragma endregion

#pragma region public function
	/// <summary>
	/// update time
	/// </summary>
	void Update();
#pragma endregion

private:
#pragma region private primitive variable
	/// <summary>
	/// current frames per second
	/// </summary>
	static int s_fps;

	/// <summary>
	/// time since last frame
	/// </summary>
	static float s_deltaSeconds;

	/// <summary>
	/// frames since last time stamp
	/// </summary>
	int m_frameSinceLastTimeStamp = 0;

	/// <summary>
	/// last update
	/// </summary>
	long m_lastUpdate = 0.0f;

	/// <summary>
	/// time since last time stamp
	/// </summary>
	long m_timeSinceLastTimeStamp = 0.0f;
#pragma endregion
};