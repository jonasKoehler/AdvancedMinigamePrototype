#pragma region engine include
#include "ContentManagement.h"
#include "TextureManagement.h"
#include "TextObject.h"
#include "Music.h"
#include "Input.h"
#include "Physic.h"
#pragma endregion

#pragma region game include
#include "Game.h"
#include "MainScene.h"
#include "MenuScene.h"
#pragma endregion


#pragma region pulic override function
// initialize scene
void GMenuScene::Init()
{

	//Create Backround 
#pragma region Background
	CTexture* pBackgroundTexture = new CTexture("Texture/Menu/T_Mainmenu.png");
	
	CTexturedObject* pBackground = new CTexturedObject(
		"",
		SVector2()
	);
	pBackground->SetTexture(pBackgroundTexture);
	CTM->AddSceneObject(pBackground);

#pragma endregion
	

	//Button Backround
	CTexturedObject* pStartBackground = new CTexturedObject("Texture/Menu/T_Button.png", SVector2(228.0f, 62.0f), SVector2(12.0f, -70.0f));
	CTM->AddUiObject(pStartBackground);
	CTexturedObject* pQuitBackground = new CTexturedObject("Texture/Menu/T_Button.png", SVector2(228.0f, 62.0f), SVector2(12.0f, 30.0f));
	CTM->AddUiObject(pQuitBackground);

	// create start text
	CTextObject* pStart = new CTextObject("Start Game", GAME->GetMarioFont(), SVector2(128.0f, 32.0f), SVector2(652.0f, 300.0f), SColor(255, 0, 0));
	pStart->SetInWorld(false);
	pStart->SetTag("Start");
	CTM->AddUiObject(pStart);

	// create quit text
	CTextObject* pQuit = new CTextObject("Quit Game", GAME->GetMarioFont(), SVector2(128.0f, 32.0f), SVector2(652.0f, 400.0f), SColor(255, 0, 0));
	pQuit->SetInWorld(false);
	pQuit->SetTag("Quit");
	CTM->AddUiObject(pQuit);

	// set mouse and loading screen texture
	ENGINE->SetMouseTexture(TTM->GetTexture("Texture/Mouse/T_Mouse.png"));
	ENGINE->SetLoadingScreen(TTM->GetTexture("Texture/Loading/T_Loading.png"));

	// show mouse
	ENGINE->SetMouseVisible(true);
}

// update every frame
void GMenuScene::Update(float _deltaSeconds)
{
	// if mouse left clicked check every ui objects
	if (CInput::GetMouseButtonDown(0))
	{
		for (CObject* pObject : CTM->GetUiObjects()) {
			// if current object is textured object
			if (dynamic_cast<CTexturedObject*>(pObject))
			{
				// check collision with current object rect and mouse position as 1x1 rect
				if (RectRectCollision(((CTexturedObject*)(pObject))->GetRect(), SRect(1, 1, CInput::GetMousePosition().X, CInput::GetMousePosition().Y)))
				{
					// breakout when the object is not visible, thus inactive
					if (!pObject->GetRenderingIndicator())
						break;
					// if hit object has start tag change scene to main scene
					if (pObject->GetTag() == "Start")
						ENGINE->ChangeScene(new GMainScene());
					// if hit object has quit tag quit game
					else if (pObject->GetTag() == "Quit")
						GAME->Quit();
				}
			}
		}
	}
}

// render every frame
void GMenuScene::Render()
{

}

// clean up scene
void GMenuScene::Clean()
{

}
#pragma endregion