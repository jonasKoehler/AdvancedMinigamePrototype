#pragma once

#pragma region system include
#include <SDL_ttf.h>
#pragma endregion

/// <summary>
/// class for font informations
/// </summary>
class CFont
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pFile">relative file path</param>
	/// <param name="_size">font size</param>
	CFont(const char* _pFile, int _size = 12);
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	~CFont();
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// get sdl font
	/// </summary>
	/// <returns>sdl font reference</returns>
	inline TTF_Font* GetSdlFont() { return m_pSdlFont; }
#pragma endregion

private:
#pragma region private pointer
	/// <summary>
	/// sdl font
	/// </summary>
	TTF_Font* m_pSdlFont = nullptr;
#pragma endregion
};