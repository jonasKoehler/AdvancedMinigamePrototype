#include "EndScene.h"
#include "TextObject.h"
#include "Game.h"
#include "ContentManagement.h"
#include "Input.h"
#include "Physic.h"
#include "MainScene.h"

#pragma region pulic override function
// initialize scene
void GEndScene::Init()
{

	// When the Game is won
	if (GAME->m_Won == true)
	{
		CTextObject* pWon = new CTextObject("You won!", GAME->GetFont(), SVector2(228.0f, 32.0f), SVector2(512.0f, 256.0f), SColor(0, 255, 0));
		pWon->SetInWorld(false);
		CTM->AddUiObject(pWon);
	}

	// When the Game is lose
	if (GAME->m_Won == false)
	{
		CTextObject* pWon = new CTextObject("Oh No! You died!", GAME->GetFont(), SVector2(228.0f, 32.0f), SVector2(512.0f, 256.0f), SColor(255,0, 0));
		pWon->SetInWorld(false);
		CTM->AddUiObject(pWon);
	}

	//create restart text
	CTextObject* pRestart = new CTextObject("Restart", GAME->GetFont(), SVector2(128.0f, 32.0f), SVector2(512.0f, 480.0f), SColor(255, 0, 0));
	pRestart->SetInWorld(false);
	pRestart->SetTag("Restart");
	CTM->AddUiObject(pRestart);

	// create quit text
	CTextObject* pQuit = new CTextObject("Quit Game", GAME->GetFont(), SVector2(128.0f, 32.0f), SVector2(512.0f, 680.0f), SColor(255, 0, 0));
	pQuit->SetInWorld(false);
	pQuit->SetTag("Quit");
	CTM->AddUiObject(pQuit);
}

// update every frame
void GEndScene::Update(float _deltaSeconds)
{
	// if mouse left clicked check every ui objects
	if (CInput::GetMouseButtonDown(0))
		for (CObject* pObject : CTM->GetUiObjects())
			// if current object is textured object
			if (dynamic_cast<CTexturedObject*>(pObject))
				// check collision with current object rect and mouse position as 1x1 rect
				if (RectRectCollision(((CTexturedObject*)(pObject))->GetRect(), SRect(1, 1, CInput::GetMousePosition().X, CInput::GetMousePosition().Y)))
					// if hit object has quit tag quit game
					if (pObject->GetTag() == "Restart")
						ENGINE->ChangeScene(new GMainScene());
					else if (pObject->GetTag() == "Quit")
						GAME->Quit();
}

// render every frame
void GEndScene::Render()
{

}

// clean up scene
void GEndScene::Clean()
{
	CTM->CleanUiObjects();
}
#pragma endregion