#pragma once

#pragma region forward decleration
class SDL_Window;
class SDL_Surface;
class CRenderer;
class CTime;
class CMouse;
class CContentManagement;
class CTextureManagement;
class CScene;
class CTexture;
#pragma endregion

#pragma region project include
#include "Vector2.h"
#pragma endregion

#pragma region value macro
#define ENGINE CEngine::Get()
#pragma endregion

/// <summary>
/// core engine class
/// </summary>
class CEngine
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	CEngine() {}
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// get width of screen
	/// </summary>
	/// <returns>width of screen</returns>
	inline int GetWidth() { return m_width; }

	/// <summary>
	/// get height of screen
	/// </summary>
	/// <returns>height of screen</returns>
	inline int GetHeight() { return m_height; }

	/// <summary>
	/// get sdl window
	/// </summary>
	/// <returns>sdl window reference</returns>
	inline SDL_Window* GetSdlWindow() { return m_pWindow; }

	/// <summary>
	/// get renderer
	/// </summary>
	/// <returns>renderer reference</returns>
	inline CRenderer* GetRenderer() { return m_pRenderer; }

	/// <summary>
	/// get content management
	/// </summary>
	/// <returns>content management reference</returns>
	inline CContentManagement* GetCTM() { return m_pCTM; }

	/// <summary>
	/// get texture management
	/// </summary>
	/// <returns>texture management reference</returns>
	inline CTextureManagement* GetTTM() { return m_pTTM; }

	/// <summary>
	/// get engine
	/// </summary>
	/// <returns>engine reference</returns>
	inline static CEngine* Get()
	{
		// static local variable is the same static variable as a member variable
		// it exists only one time
		// the new keyword is only used if the engine was not called before
		// every time after the first time the new keyword will be ignored
		static CEngine* pEngine = new CEngine();

		// returns the engine reference
		return pEngine;
	}
#pragma endregion

#pragma region public function
	/// <summary>
	/// initialize engine
	/// </summary>
	/// <returns></returns>
	int Init();

	/// <summary>
	/// run engine
	/// </summary>
	void Run();

	/// <summary>
	/// stop engine
	/// </summary>
	void Stop();

	/// <summary>
	/// clean up engine
	/// </summary>
	void Clean();

	/// <summary>
	/// set loading screen texture
	/// </summary>
	/// <param name="_pTexture">texture reference</param>
	void SetLoadingScreen(CTexture* _pTexture);

	/// <summary>
	/// change active scene
	/// </summary>
	/// <param name="_pScene">new scene reference</param>
	void ChangeScene(CScene* _pScene);

	/// <summary>
	/// set mouse visible
	/// </summary>
	/// <param name="_visible">visible or not</param>
	void SetMouseVisible(bool _visible);

	/// <summary>
	/// set texture of mouse
	/// </summary>
	/// <param name="_pTexture">texture to set</param>
	void SetMouseTexture(CTexture* _pTexture);

	/// <summary>
	/// set center of mouse
	/// </summary>
	/// <param name="_center">center of mouse between zero and 1</param>
	void SetMouseCenter(SVector2 _center);

	/// <summary>
	/// set size of mouse texture
	/// </summary>
	/// <param name="_size">size to set</param>
	void SetMouseSize(SVector2 _size);
#pragma endregion

private:
#pragma region private primitive variable
	/// <summary>
	/// engine is running
	/// </summary>
	bool m_isRunning = false;

	/// <summary>
	/// resolution should change at begin of next frame
	/// </summary>
	bool m_changeResolution = false;
	
	/// <summary>
	/// width of screen
	/// </summary>
	int m_width = 0;

	/// <summary>
	/// height of screen
	/// </summary>
	int m_height = 0;
#pragma endregion

#pragma region private pointer
	/// <summary>
	/// sdl window
	/// </summary>
	SDL_Window* m_pWindow = nullptr;

	/// <summary>
	/// sdl surface
	/// </summary>
	SDL_Surface* m_pSurface = nullptr;

	/// <summary>
	/// renderer to render textures
	/// </summary>
	CRenderer* m_pRenderer = nullptr;

	/// <summary>
	/// time
	/// </summary>
	CTime* m_pTime = nullptr;

	/// <summary>
	/// mouse
	/// </summary>
	CMouse* m_pMouse = nullptr;

	/// <summary>
	/// content management
	/// </summary>
	CContentManagement* m_pCTM = nullptr;

	/// <summary>
	/// texture management
	/// </summary>
	CTextureManagement* m_pTTM = nullptr;

	/// <summary>
	/// current active scene
	/// </summary>
	CScene* m_pScene = nullptr;

	/// <summary>
	/// loading screen screen
	/// </summary>
	CTexture* m_pLoadingScreen = nullptr;

	/// <summary>
	/// new scene to load at begin of next frame
	/// </summary>
	CScene* m_pChangeScene = nullptr;
#pragma endregion

#pragma region private function
	/// <summary>
	/// update every frame
	/// </summary>
	void Update();

	/// <summary>
	/// render every frame
	/// </summary>
	void Render();
#pragma endregion
};