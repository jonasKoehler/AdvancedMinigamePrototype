#pragma once

#pragma region forward decleration
class SDL_Texture;
#pragma endregion

/// <summary>
/// class with texture inormation
/// </summary>
class CTexture
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pFile">relative file path</param>
	CTexture(const char* _pFile);
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	~CTexture();
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// get sdl texture
	/// </summary>
	/// <returns>sdl texture reference</returns>
	inline SDL_Texture* GetSdlTexture() { return m_pSdlTexture; }
#pragma endregion

#pragma region public function
	/// <summary>
	/// set sdl texture
	/// </summary>
	/// <param name="_pSdlTexture">sdl texture reference to set</param>
	void SetSdlTexture(SDL_Texture* _pSdlTexture);
#pragma endregion

private:
#pragma region private pointer
	/// <summary>
	/// sdl texture
	/// </summary>
	SDL_Texture* m_pSdlTexture = nullptr;
#pragma endregion
};