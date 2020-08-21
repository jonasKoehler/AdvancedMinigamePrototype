#pragma region system include
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#pragma endregion

#pragma region project include
#include "Engine.h"
#include "Macro.h"
#include "Renderer.h"
#include "Time.h"
#include "Mouse.h"
#include "ContentManagement.h"
#include "TextureManagement.h"
#include "Scene.h"
#include "Input.h"
#pragma endregion

#pragma region public function
// initialize engine
int CEngine::Init()
{
	// init sdl video and log error if not initialized
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL not initialized");
		return -1;
	}

	// init sdl ttf and log error if not initialized
	if (TTF_Init() < 0)
	{
		LOG("SDL TTF not initialized");
		return -2;
	}

	// init sdl mixer and log error if not initialized
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, MIX_CHANNELS, 4096) < 0)
	{
		LOG("SDL Mixer not initialized");
		return -3;
	}

	// create sdl window
	m_pWindow = SDL_CreateWindow(
		"SDL2 Engine",			// name of window
		SDL_WINDOWPOS_CENTERED,	// position x
		SDL_WINDOWPOS_CENTERED,	// position y
		SCREEN_WIDTH,			// width
		SCREEN_HEIGHT,			// height
		SDL_WINDOW_SHOWN		// flags
	);

	// if window not created log error
	if (!m_pWindow)
	{
		LOG("Window not created");
		return -4;
	}

	// get sdl surface from sdl window
	m_pSurface = SDL_GetWindowSurface(m_pWindow);

	// if surface not created log error
	if (!m_pSurface)
	{
		LOG("Surface not created");
		return -5;
	}

	// create renderer
	m_pRenderer = new CRenderer(m_pWindow);

	// if renderer not created log error
	if (!m_pRenderer)
	{
		LOG("Renderer not created");
		return -100;
	}

	// create time
	m_pTime = new CTime();

	// if time not created log error
	if (!m_pTime)
	{
		LOG("Time not created");
		return -101;
	}

	// create mouse
	m_pMouse = new CMouse("", SVector2(32.0f, 32.0f), SVector2());

	// if mouse not created log error
	if (!m_pMouse)
	{
		LOG("Mouse not created");
		return -102;
	}

	// hide system mouse
	SDL_ShowCursor(0);

	// set mouse rendered in screen space
	m_pMouse->SetInWorld(false);

	// create content management
	m_pCTM = new CContentManagement();

	// if ctm not created log error
	if (!m_pCTM)
	{
		LOG("Content Management not created");
		return -103;
	}

	// create texture management
	m_pTTM = new CTextureManagement();

	// if ttm not created log error
	if (!m_pTTM)
	{
		LOG("Texture Management not created");
		return -104;
	}

	// save width and height
	m_width = SCREEN_WIDTH;
	m_height = SCREEN_HEIGHT;

	// set engine running and return no error
	m_isRunning = true;
	return 0;
}

// run engine
void CEngine::Run()
{
	// while engine is running
	while (m_isRunning)
	{
		// update and render every frame
		Update();
		Render();
	}
}

// stop engine
void CEngine::Stop()
{
	m_isRunning = false;
}

// clean up engine
void CEngine::Clean()
{
	// chane scene to nullptr
	ChangeScene(nullptr);

	// delete textures
	delete m_pTTM;

	// delete content
	delete m_pCTM;

	// delete mouse
	delete m_pMouse;

	// delete time
	delete m_pTime;

	// delete renderer
	delete m_pRenderer;

	// free sdl surface, destroy sdl window, quit sdl ttf, mixer and sdl
	SDL_FreeSurface(m_pSurface);
	SDL_DestroyWindow(m_pWindow);
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
}

// set loading screen texture
void CEngine::SetLoadingScreen(CTexture* _pTexture)
{
	// if loading screen exists and not given texture
	if (m_pLoadingScreen && m_pLoadingScreen != _pTexture)
	{
		// delete loading screen
		delete m_pLoadingScreen;
		m_pLoadingScreen = nullptr;
	}

	// if new texture valid
	if (_pTexture)
		// set loading screen
		m_pLoadingScreen = _pTexture;
}

// change active scene
void CEngine::ChangeScene(CScene* _pScene)
{
	// if current active scene valid
	if (m_pScene)
	{
		// clean and delete scene
		m_pScene->Clean();
		delete m_pScene;
	}

	// clean content
	m_pCTM->CleanUiObjects();
	m_pCTM->CleanSceneObjects();

	// set active scene
	m_pScene = _pScene;

	// if active scene valid
	if (m_pScene)
	{
		// if loading screen valid
		if (m_pLoadingScreen)
		{
			// clear screen
			m_pRenderer->ClearScreen();

			// render loading screen
			m_pRenderer->RenderTexture(m_pLoadingScreen, nullptr);

			// present rendered images
			m_pRenderer->Present();
		}

		// initialize scene
		m_pScene->Init();
	}
}

// set mouse visible
void CEngine::SetMouseVisible(bool _visible)
{
	m_pMouse->SetVisible(_visible);
}

// set texture of mouse
void CEngine::SetMouseTexture(CTexture* _pTexture)
{
	m_pMouse->SetTexture(_pTexture);
}

// set center of mouse
void CEngine::SetMouseCenter(SVector2 _center)
{
	m_pMouse->SetCenter(_center);
}

// set size of mouse texture
void CEngine::SetMouseSize(SVector2 _size)
{
	m_pMouse->SetRect(SRect(_size));
}
#pragma endregion

#pragma region private function
// update every frame
void CEngine::Update()
{
	// update time at beginning or end of frame
	m_pTime->Update();

	// refresh input state
	CInput::RefreshState();

	// sdl event to handle
	SDL_Event e;

	// while event is left
	while (SDL_PollEvent(&e))
	{
		// if sdl quit event set engine running false
		if (e.type == SDL_EventType::SDL_QUIT)
			m_isRunning = false;

		// if event is key down or key up parse event to input
		else if (e.type == SDL_EventType::SDL_KEYDOWN || e.type == SDL_EventType::SDL_KEYUP)
			CInput::ParseEvent(e);

		// if event is mouse event parse mouse event to input
		else if (e.type == SDL_EventType::SDL_MOUSEMOTION || e.type == SDL_EventType::SDL_MOUSEBUTTONDOWN || e.type == SDL_EventType::SDL_MOUSEBUTTONUP)
			CInput::ParseMouseEvent(e);
	}

	// update mouse
	m_pMouse->Update(m_pTime->GetDeltaSeconds());

	// if active scene valid update scene
	if (m_pScene)
		m_pScene->Update(m_pTime->GetDeltaSeconds());

	CScene* pScene = m_pScene;

	// update content
	m_pCTM->Update(m_pTime->GetDeltaSeconds());

	if (m_pScene != pScene)
	{
		CTM->Update(0);
	}
}

// render every frame
void CEngine::Render()
{
	// clear screen
	m_pRenderer->ClearScreen();

	// if active scene valid render scene
	if (m_pScene)
		m_pScene->Render();

	// if active scene not valid log error
	else
		LOG("NO VALID SCENE");

	// render content
	m_pCTM->Render();

	// render mouse
	m_pMouse->Render();

	// present rendered images
	m_pRenderer->Present();
}
#pragma endregion