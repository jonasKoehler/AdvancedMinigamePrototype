#pragma once

#pragma region project include
#include "Engine.h"
#include "Vector2.h"
#pragma endregion

#pragma region forward decleration
class SRect;
class CTexture;
class SDL_Window;
class SDL_Renderer;
#pragma endregion

#pragma region value macro
#define RENDERER CEngine::Get()->GetRenderer()
#pragma endregion

/// <summary>
/// class to render textures
/// </summary>
class CRenderer
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pWindow">sdl window reference</param>
	CRenderer(SDL_Window* _pWindow);
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	~CRenderer();
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// get camera position
	/// </summary>
	/// <returns>camera world position</returns>
	inline SVector2 GetCamera() { return m_camera; }

	/// <summary>
	/// set camera position
	/// </summary>
	/// <param name="_pos">camera world position to set</param>
	inline void SetCamera(SVector2 _pos) { m_camera = _pos; }

	/// <summary>
	/// get sdl renderer
	/// </summary>
	/// <returns>sdl renderer reference</returns>
	inline SDL_Renderer* GetSdlRenderer() { return m_pSdlRenderer; }
#pragma endregion

#pragma region public function
	/// <summary>
	/// clear screen
	/// </summary>
	void ClearScreen();
	
	/// <summary>
	/// render texture
	/// </summary>
	/// <param name="_pTexture">texture reference</param>
	/// <param name="_pRect">destination rect on screen</param>
	/// <param name="_angle">angle of rect</param>
	/// <param name="_pSrcRect">source rect of textre</param>
	/// <param name="_inWorld">texture is rendered in world space</param>
	/// <param name="_mirror">mirror (x is true = horizontal and y is true = vertical)</param>
	void RenderTexture(CTexture* _pTexture, SRect* _pDstRect, float _angle = 0.0f, SRect* _pSrcRect = nullptr,
		bool _inWorld = true, SVector2 _mirror = SVector2());

	/// <summary>
	/// present rendered textures
	/// </summary>
	void Present();
#pragma endregion

private:
#pragma region private variable
	/// <summary>
	/// camera world position
	/// </summary>
	SVector2 m_camera = SVector2();
#pragma endregion

#pragma region private pointer
	/// <summary>
	/// sdl renderer
	/// </summary>
	SDL_Renderer* m_pSdlRenderer = nullptr;
#pragma endregion
};