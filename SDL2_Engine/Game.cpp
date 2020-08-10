#pragma region engine include
#include "Engine.h"
#include "Font.h"
#include "Texture.h"
#pragma endregion

#pragma region game include
#include "Game.h"
#pragma endregion

#pragma region public function
// initialize game
void GGame::Init()
{
	// load config
	GConfig::LoadConfig();

	// create mario font
	m_pMarioFont = new CFont("Font/F_Mario.ttf", 72);

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