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
<<<<<<< HEAD
	inline CFont* GetFont() { return m_pFont; }
=======
	inline CFont* GetMarioFont() { return m_pMarioFont; }
	inline CFont* GetMenuFont() { return m_pMenuFont; }
>>>>>>> b106dcf9a09264f72990a0542719cee969ac0614
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
<<<<<<< HEAD
	CFont* m_pFont = nullptr;
=======
	CFont* m_pMenuFont = nullptr;
	CFont* m_pMarioFont = nullptr;
>>>>>>> b106dcf9a09264f72990a0542719cee969ac0614
#pragma endregion
};