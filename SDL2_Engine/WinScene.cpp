#include "WinScene.h"
#include "TextObject.h"
#include "Game.h"
#include "ContentManagement.h"
#include "Input.h"
#include "Physic.h"
#include "MainScene.h"

#pragma region pulic override function
// initialize scene
void GWinScene::Init()
{
	// create Won text
	CTextObject* pWon = new CTextObject("You won!", GAME->GetMarioFont(), SVector2(128.0f, 32.0f), SVector2(512.0f, 256.0f), SColor(255, 0, 0));
	pWon->SetInWorld(false);
	CTM->AddUiObject(pWon);

	// create quit text
	CTextObject* pQuit = new CTextObject("Quit Game", GAME->GetMarioFont(), SVector2(128.0f, 32.0f), SVector2(512.0f, 480.0f), SColor(255, 0, 0));
	pQuit->SetInWorld(false);
	pQuit->SetTag("Quit");
	CTM->AddUiObject(pQuit);
}

// update every frame
void GWinScene::Update(float _deltaSeconds)
{
	// if mouse left clicked check every ui objects
	if (CInput::GetMouseButtonDown(0))
		for (CObject* pObject : CTM->GetUiObjects())
			// if current object is textured object
			if (dynamic_cast<CTexturedObject*>(pObject))
				// check collision with current object rect and mouse position as 1x1 rect
				if (RectRectCollision(((CTexturedObject*)(pObject))->GetRect(), SRect(1, 1, CInput::GetMousePosition().X, CInput::GetMousePosition().Y)))															
	// if hit object has quit tag quit game
					 if (pObject->GetTag() == "Quit")
						GAME->Quit();
}

// render every frame
void GWinScene::Render()
{

}

// clean up scene
void GWinScene::Clean()
{

}
#pragma endregion