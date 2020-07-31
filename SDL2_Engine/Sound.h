#pragma once

#pragma region system include
#include <SDL_mixer.h>
#pragma endregion

#pragma region engine include
#include "Helper.h"
#pragma endregion

/// <summary>
/// sound class
/// </summary>
class CSound
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pFileName">relative file path name</param>
	CSound(const char* _pFileName)
	{
		// load sound chunk from file
		m_pSound = Mix_LoadWAV(GetAssetPath(_pFileName, 4).c_str());
	}
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	~CSound()
	{
		// free chunk
		Mix_FreeChunk(m_pSound);
	}
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// get volume
	/// </summary>
	/// <returns>volume value</returns>
	inline int GetVolume()
	{
		return m_volume;
	}

	/// <summary>
	/// set volume
	/// </summary>
	/// <param name="_volume">volume to set</param>
	inline void SetVolume(int _volume)
	{
		// set volume and volume of music
		m_volume = _volume;
		Mix_VolumeChunk(m_pSound, _volume);
	}

	/// <summary>
	/// play music
	/// </summary>
	inline void Play()
	{
		// play sound one time
		Mix_PlayChannel(-1, m_pSound, 0);
	}
#pragma endregion

protected:
#pragma region protected primitive varibale
	/// <summary>
	/// volume value
	/// </summary>
	int m_volume = 100;
#pragma endregion

#pragma region protected pointer
	/// <summary>
	/// chunk
	/// </summary>
	Mix_Chunk* m_pSound = nullptr;
#pragma endregion
};