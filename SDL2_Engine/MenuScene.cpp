#pragma region engine include
#include "ContentManagement.h"
#include "TextureManagement.h"
#include "UpgradeFrame.h"
#include "EUpgrades.h"
#include "TextObject.h"
#include "Input.h"
#include "Physic.h"
#include "Macro.h"
#pragma endregion

#pragma region game include
#include "Game.h"
#include "MainScene.h"
#include "MenuScene.h"
#pragma endregion


#pragma region pulic override function
// initialize scene
void GMenuScene::Init() //by Lukas
{
	//Create Backround 
	CTexturedObject* pBackground = new CTexturedObject("Texture/Menu/T_Mainmenu.png", SVector2());
	CTM->AddSceneObject(pBackground);

	//Create Instructions Background
	m_pTutorialImage = new CTexturedObject("Texture/Menu/T_Instructions.png", SVector2());
	m_pTutorialImage->SetRenderingIndicator(false);
	CTM->AddSceneObject(m_pTutorialImage);

	//Button Backround
	CTexturedObject* pStartBackground = new CTexturedObject("Texture/Menu/T_Button.png", SVector2(228.0f, 62.0f), SVector2(SCREEN_WIDTH * 0.5, 300));
	CTexturedObject* pTutorialBackground = new CTexturedObject("Texture/Menu/T_Button.png", SVector2(228.0f, 62.0f), SVector2(SCREEN_WIDTH * 0.5, 400));
	CTexturedObject* pQuitBackground = new CTexturedObject("Texture/Menu/T_Button.png", SVector2(228.0f, 62.0f), SVector2(SCREEN_WIDTH * 0.5, 500));
	pStartBackground->SetInWorld(false);
	pTutorialBackground->SetInWorld(false);
	pQuitBackground->SetInWorld(false);
	CTM->AddUiObject(pStartBackground);
	CTM->AddUiObject(pTutorialBackground);
	CTM->AddUiObject(pQuitBackground);

	// create start text
	CTextObject* pStart = new CTextObject("Start Game", GAME->GetMenuFont(), SVector2(128.0f, 32.0f), SVector2(SCREEN_WIDTH * 0.5, 300), SColor(255, 0, 0));
	pStart->SetInWorld(false);
	pStart->SetTag("Start");
	CTM->AddUiObject(pStart);

	// create tutorial text
	CTextObject* pTutorial = new CTextObject("How to Play", GAME->GetMenuFont(), SVector2(128.0f, 32.0f), SVector2(SCREEN_WIDTH * 0.5, 400), SColor(255, 0, 0));
	pTutorial->SetInWorld(false);
	pTutorial->SetTag("Tutorial");
	CTM->AddUiObject(pTutorial);

	// create quit text
	CTextObject* pQuit = new CTextObject("Quit Game", GAME->GetMenuFont(), SVector2(128.0f, 32.0f), SVector2(SCREEN_WIDTH * 0.5, 500), SColor(255, 0, 0));
	pQuit->SetInWorld(false);
	pQuit->SetTag("Quit");
	CTM->AddUiObject(pQuit);

	// add button ui objects to canvas
	m_ButtonCanvas.AddObject(pStartBackground);
	m_ButtonCanvas.AddObject(pTutorialBackground);
	m_ButtonCanvas.AddObject(pQuitBackground);
	m_ButtonCanvas.AddObject(pStart);
	m_ButtonCanvas.AddObject(pTutorial);
	m_ButtonCanvas.AddObject(pQuit);

	// set music
	m_pMenuTheme = new CMusic("Sound/Music/M_MenuMusic.wav");
	m_pMenuTheme->Play(true);

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
					{
						ENGINE->ChangeScene(new GMainScene());
						return;
					}
					// if hit object has quit tag quit game
					else if (pObject->GetTag() == "Quit")
						GAME->Quit();
					else if (pObject->GetTag() == "Tutorial")
					{
						m_pTutorialImage->SetRenderingIndicator(true);
						m_ButtonCanvas.SetVisible(false);
					}
				}
			}
		}
	}

	if (CInput::GetKeyDown(SDL_SCANCODE_ESCAPE))
	{
		m_pTutorialImage->SetRenderingIndicator(false);
		m_ButtonCanvas.SetVisible(true);
	}
}

// render every frame
void GMenuScene::Render()
{

}

// clean up scene
void GMenuScene::Clean()
{
	delete m_pMenuTheme;
}
#pragma endregion