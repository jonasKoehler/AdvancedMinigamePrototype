#pragma region engine include
#include "Input.h"
#pragma endregion

#pragma region game include
#include "Game.h"
#include "World.h"
#include "MainScene.h"
#include "MenuScene.h"
#pragma endregion

#pragma region public override function
// initialize scene
void GMainScene::Init()
{
	// load world
	LoadWorldFromString();
	p_Music = new CMusic("Sound/Music/music.wav");
	p_Music->Play(true);
}

// update every frame
void GMainScene::Update(float _deltaSeconds)
{
	// quit game
	if (CInput::GetKeyDown(SDL_SCANCODE_ESCAPE))
		ENGINE->ChangeScene(new GMenuScene());
}

// render every frame
void GMainScene::Render()
{
	
}

// clean up scene
void GMainScene::Clean()
{
	delete p_Music;
}
#pragma endregion