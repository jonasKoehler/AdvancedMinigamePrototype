#pragma once

#pragma region system include
#include <SDL_mixer.h>
#pragma endregion

#pragma region engine include
#include "Helper.h"
#pragma endregion

/// <summary>
/// music class
/// </summary>
class CMusic
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pFileName">relative file path name</param>
	CMusic(const char* _pFileName)
	{
		// load music from file
		m_pMusic = Mix_LoadMUS(GetAssetPath(_pFileName, 4).c_str());
	}
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	~CMusic()
	{
		// free music
		Mix_FreeMusic(m_pMusic);
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
		Mix_VolumeMusic(_volume);
	}

	/// <summary>
	/// play music
	/// </summary>
	/// <param name="_loop">loop times (-1 endless)</param>
	inline void Play(bool _loop)
	{
		// loop none or endless
		int loop = 0;
		if (_loop)
			loop = -1;

		// play music by loop
		Mix_PlayMusic(m_pMusic, loop);
	}

	/// <summary>
	/// stop music
	/// </summary>
	inline void Stop()
	{
		Mix_HaltMusic();
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
	/// music
	/// </summary>
	Mix_Music* m_pMusic = nullptr;
#pragma endregion
};