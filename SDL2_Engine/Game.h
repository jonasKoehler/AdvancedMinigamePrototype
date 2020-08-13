#pragma once

#pragma region game include
#include "MenuScene.h"
#include "Config.h"
#pragma endregion

#pragma region value macro
#define GAME GGame::Get()
#pragma endregion

#pragma region forward decleration
class CFont;
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
	bool m_Won = false;
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

	/// <summary>
	/// get mario font
	/// </summary>
	/// <returns>mario font reference</returns>
	inline CFont* GetMarioFont() { return m_pMarioFont; }
	inline CFont* GetMenuFont() { return m_pMenuFont; }
#pragma endregion

#pragma region public function
	/// <summary>
	/// initialize game
	/// </summary>
	void Init();

	/// <summary>
	/// quit game
	/// </summary>
	void Quit();
#pragma endregion

private:
#pragma region private pointer
	/// <summary>
	/// mario font
	/// </summary>
	CFont* m_pMenuFont = nullptr;
	CFont* m_pMarioFont = nullptr;
#pragma endregion
};