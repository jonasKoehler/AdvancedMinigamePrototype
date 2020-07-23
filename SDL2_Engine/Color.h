#pragma once

#pragma region system include
#include <SDL.h>
#pragma endregion

/// <summary>
/// struct for color values
/// </summary>
class SColor : public SDL_Color
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	SColor()
	{
		r, g, b = 0;
		a = 255;
	}

	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_r">red value</param>
	/// <param name="_g">green value</param>
	/// <param name="_b">blue value</param>
	/// <param name="_a">alpha value (0 is transparent)</param>
	SColor(Uint8 _r, Uint8 _g, Uint8 _b, Uint8 _a = 255)
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}
#pragma endregion
};