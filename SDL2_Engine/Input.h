#pragma once

#pragma region system include
#include <SDL.h>
#pragma endregion

#pragma region project include
#include "Vector2.h"
#pragma endregion

/// <summary>
/// class to handle input
/// </summary>
class CInput
{
public:
#pragma region public inline function
	/// <summary>
	/// get mouse position
	/// </summary>
	/// <returns>mouse position on screen</returns>
	static inline SVector2 GetMousePosition() { return s_mousePosition; }
#pragma endregion

#pragma region public function
	/// <summary>
	/// parse sdl event
	/// </summary>
	/// <param name="_event">sdl event</param>
	static void ParseEvent(SDL_Event _event);

	/// <summary>
	/// parse sdl mouse event
	/// </summary>
	/// <param name="_event">sdl event</param>
	static void ParseMouseEvent(SDL_Event _event);

	/// <summary>
	/// refresh input state
	/// </summary>
	static void RefreshState();

	/// <summary>
	/// get key is pressed
	/// </summary>
	/// <param name="_key">key</param>
	/// <returns>key is pressed</returns>
	static bool GetKey(SDL_Scancode _key);

	/// <summary>
	/// get key is pressed down this frame
	/// </summary>
	/// <param name="_key">key</param>
	/// <returns>key is pressed down this frame</returns>
	static bool GetKeyDown(SDL_Scancode _key);

	/// <summary>
	/// get key is released this frame
	/// </summary>
	/// <param name="_key">key</param>
	/// <returns>key is released this frame</returns>
	static bool GetKeyUp(SDL_Scancode _key);

	/// <summary>
	/// get mouse button clicked
	/// </summary>
	/// <param name="_index">mouse button index</param>
	/// <returns>mouse button is clicked</returns>
	static bool GetMouseButton(int _index);

	/// <summary>
	/// get mouse button clicked this frame
	/// </summary>
	/// <param name="_index">mouse button index</param>
	/// <returns>mouse button is clicked this frame</returns>
	static bool GetMouseButtonDown(int _index);

	/// <summary>
	/// get mouse button released
	/// </summary>
	/// <param name="_index">mouse button index</param>
	/// <returns>mouse button is released this frame</returns>
	static bool GetMouseButtonUp(int _index);
#pragma endregion

private:
#pragma region private primitive variable
	/// <summary>
	/// key states last frame
	/// </summary>
	static bool s_keyWasDown[256];

	/// <summary>
	/// key state this frame
	/// </summary>
	static bool s_keyIsDown[256];

	/// <summary>
	/// mouse button states last frame
	/// </summary>
	static bool s_mouseWasDown[3];

	/// <summary>
	/// mouse button states this frame
	/// </summary>
	static bool s_mouseIsDown[3];

	/// <summary>
	/// mouse position on screen
	/// </summary>
	static SVector2 s_mousePosition;
#pragma endregion
};