#pragma region engine include
#include "Engine.h"
#pragma endregion

#pragma region game include
#include "Game.h"
#pragma endregion

#pragma region define
#undef main
#pragma endregion

/// <summary>
/// main entry point of application
/// </summary>
/// <returns>shutdown error code</returns>
int main()
{
	// initialize engine and save error code
	int error = ENGINE->Init();

	// if no error
	if (!error)
	{
		// inizialize game
		GAME->Init();

		// run engine
		ENGINE->Run();

		// clean up engine
		ENGINE->Clean();
	}

	// return shutdown error code
	return error;
}