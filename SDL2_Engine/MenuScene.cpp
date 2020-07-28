#include "MenuScene.h"
#include "TextObject.h"
#include "Game.h"
#include "ContentManagement.h"
#include "Input.h"
#include "Physic.h"
#include "MainScene.h"

#pragma region pulic override function
// initialize scene
void GMenuScene::Init()
{
	CTextObject* pTitle = new CTextObject("Covid Operations", GAME->GetMarioFont(), SVector2(428.0f, 32.0f), SVector2(512.0f, 56.0f), SColor(255, 0, 0));
	pTitle->SetInWorld(false);
	CTM->AddUiObject(pTitle);
	// create start text
	CTextObject* pStart = new CTextObject("Start Game", GAME->GetMarioFont(), SVector2(128.0f, 32.0f), SVector2(512.0f, 256.0f), SColor(255, 0, 0));
	pStart->SetInWorld(false);
	pStart->SetTag("Start");
	CTM->AddUiObject(pStart);

	// create quit text
	CTextObject* pQuit = new CTextObject("Quit Game", GAME->GetMarioFont(), SVector2(128.0f, 32.0f), SVector2(512.0f, 480.0f), SColor(255, 0, 0));
	pQuit->SetInWorld(false);
	pQuit->SetTag("Quit");
	CTM->AddUiObject(pQuit);
}

// update every frame
void GMenuScene::Update(float _deltaSeconds)
{
	// if mouse left clicked check every ui objects
	if (CInput::GetMouseButtonDown(0))
		for (CObject* pObject : CTM->GetUiObjects())
			// if current object is textured object
			if (dynamic_cast<CTexturedObject*>(pObject))
				// check collision with current object rect and mouse position as 1x1 rect
				if (RectRectCollision(((CTexturedObject*)(pObject))->GetRect(), SRect(1, 1, CInput::GetMousePosition().X, CInput::GetMousePosition().Y)))
					// if hit object has start tag change scene to main scene
					if (pObject->GetTag() == "Start")
						ENGINE->ChangeScene(new GMainScene());
					// if hit object has quit tag quit game
					else if (pObject->GetTag() == "Quit")
						GAME->Quit();
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