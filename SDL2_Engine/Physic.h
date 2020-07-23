#pragma once

#pragma region project include
#include "Rect.h"
#pragma endregion

#pragma region function
/// <summary>
/// check collision of two rects
/// </summary>
/// <param name="_rectOne">rect one</param>
/// <param name="_rectTwo">rect two</param>
/// <returns>if collision or not</returns>
bool RectRectCollision(SRect _rectOne, SRect _rectTwo);
#pragma endregion