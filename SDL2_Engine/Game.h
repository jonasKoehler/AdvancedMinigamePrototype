#pragma once

#pragma region engine include
#include "Engine.h"
#include "Font.h"
#pragma endregion

#pragma region game include
#include "MenuScene.h"
#pragma endregion

#pragma region value macro
#define GAME GGame::Get()
#pragma endregion

/// <summary>
/// core game class
/// </summary>
class GGame
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	GGame() {}
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// get game
	/// </summary>
	/// <returns>game reference</returns>
	inline static GGame* Get()
	{
		// create new game if not exists and return game
		static GGame* pGame = new GGame();
		return pGame;
	}
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// initialize game
	/// </summary>
	inline void Init()
	{
		// create mario font and load menu scene
		m_pMarioFont = new CFont("Font/F_Mario.ttf", 72);
		ENGINE->ChangeScene(new GMenuScene());
	}

	/// <summary>
	/// get mario font
	/// </summary>
	/// <returns>mario font reference</returns>
	inline CFont* GetMarioFont() { return m_pMarioFont; }

	/// <summary>
	/// quit game
	/// </summary>
	void Quit() { ENGINE->Stop(); }
#pragma endregion

private:
#pragma region private pointer
	/// <summary>
	/// mario font
	/// </summary>
	CFont* m_pMarioFont = nullptr;
#pragma endregion
};