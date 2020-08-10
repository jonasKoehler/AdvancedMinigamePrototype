#pragma once

#pragma region system include
#include <iostream>
#pragma endregion

#pragma region using
using namespace std;
#pragma endregion

#pragma region value macro
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define PIXEL_IN_METER 64
#define GRAVITY 9.81f // m/s^2
#define DRAW_DEBUG true
#pragma endregion

#pragma region function macro
#define LOG(TEXT) cout << TEXT << endl
#pragma endregion