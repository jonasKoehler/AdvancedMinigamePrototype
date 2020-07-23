#pragma region project include
#include "Input.h"
#pragma endregion

#pragma region variable
bool CInput::s_keyIsDown[];
bool CInput::s_keyWasDown[];
bool CInput::s_mouseIsDown[];
bool CInput::s_mouseWasDown[];
SVector2 CInput::s_mousePosition = SVector2();
#pragma endregion

#pragma region public function
// parse sdl event
void CInput::ParseEvent(SDL_Event _event)
{
	// if scancode of event is in range of input scancode
	if (_event.key.keysym.scancode < 256)
		// set key is down this frame depending on event type
		s_keyIsDown[_event.key.keysym.scancode] = _event.type == SDL_KEYDOWN;
}

// parse sdl mouse event
void CInput::ParseMouseEvent(SDL_Event _event)
{
	// if mouse was moved
	if (_event.type == SDL_MOUSEMOTION)
	{
		// set position of mouse
		s_mousePosition.X = _event.motion.x;
		s_mousePosition.Y = _event.motion.y;
	}

	// if mouse is clicked or released
	else
	{
		// set state of mouse button
		s_mouseIsDown[_event.button.button - 1] = _event.type == SDL_MOUSEBUTTONDOWN;
	}
}

// refresh input state
void CInput::RefreshState()
{
	// set key states from is down to was down
	for (int i = 0; i < 256; i++)
		s_keyWasDown[i] = s_keyIsDown[i];

	// set mouse states from is down to was down
	for (int i = 0; i < 3; i++)
		s_mouseWasDown[i] = s_mouseIsDown[i];
}

// get key is pressed
bool CInput::GetKey(SDL_Scancode _key)
{
	return s_keyIsDown[_key];
}

// get key is pressed down this frame
bool CInput::GetKeyDown(SDL_Scancode _key)
{
	return s_keyIsDown[_key] && !s_keyWasDown[_key];
}

// get key is released this frame
bool CInput::GetKeyUp(SDL_Scancode _key)
{
	return !s_keyIsDown[_key] && s_keyWasDown[_key];
}

// get mouse button clicked
bool CInput::GetMouseButton(int _index)
{
	return s_mouseIsDown[_index];
}

// get mouse button clicked this frame
bool CInput::GetMouseButtonDown(int _index)
{
	return s_mouseIsDown[_index] && !s_mouseWasDown[_index];
}

// get mouse button released
bool CInput::GetMouseButtonUp(int _index)
{
	return !s_mouseIsDown[_index] && s_mouseWasDown[_index];
}
#pragma endregion