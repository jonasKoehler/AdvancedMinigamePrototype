#pragma region engine include
#include "Engine.h"
#include "Font.h"
#include "Texture.h"
#pragma endregion

#pragma region game include
#include "Game.h"
#pragma endregion

#pragma region std includes
#include <time.h>
#pragma endregion

#pragma region public function
// initialize game
void GGame::Init()
{
	// seed for rng
	srand(time(0));

	// load config
	GConfig::LoadConfig();

	// create base font
	m_pFont = new CFont("Font/F_Arial.ttf", 72);

	// create Menu Font
	m_pMenuFont = new CFont("Font/F_Menufont.ttf", 72);

	// set mouse texture and default visible
	ENGINE->SetMouseVisible(true);

	// load menu scene
	ENGINE->ChangeScene(new GMenuScene());
}

// quit game
void GGame::Quit()
{
	ENGINE->Stop();
}
#pragma endregion