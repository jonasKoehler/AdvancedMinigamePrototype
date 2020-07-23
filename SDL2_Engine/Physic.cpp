#pragma region project include
#include "Physic.h"
#pragma endregion

#pragma region function
// check collision of two rects
bool RectRectCollision(SRect _rectOne, SRect _rectTwo)
{
	// if rect one is left of rect two no collision
	if (_rectOne.x + _rectOne.w < _rectTwo.x)
		return false;

	// if rect one is right of rect two no collision
	if (_rectOne.x > _rectTwo.x + _rectTwo.w)
		return false;

	// if rect one is over rect two no collision
	if (_rectOne.y + _rectOne.h < _rectTwo.y)
		return false;

	// if rect one is under rect two no collision
	if (_rectOne.y > _rectTwo.y + _rectTwo.h)
		return false;

	// otherwise collision
	return true;
}
#pragma endregion