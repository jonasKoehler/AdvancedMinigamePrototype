#pragma region engine include
#include "Input.h"
#include "ContentManagement.h"
#include "TextObject.h"
#include "Physic.h"
#pragma endregion

#pragma region game include
#include "Game.h"
#include "World.h"
#include "MainScene.h"
#include "MenuScene.h"
#include "UpgradeFrame.h"
#include "UpgradeManager.h"
#include "Player.h"
#include "Healthbar.h"
#include "UpgradeIcon.h"
#pragma endregion

// all Upgrade related code was done by Jonas

// initialize scene
void GMainScene::Init()
{
	// load world
	LoadWorldFromString();

	// UI Healthbar by Lukas
	GHealthbar* Healthbar = new GHealthbar(SVector2(300.0f, 40.0f), SVector2(200, 650));
	CTM->AddUiObject(Healthbar);

	// UI UpgradeIcon by Jonas
	GUpgradeIcon* UpgradeIcon = new GUpgradeIcon(SVector2(104.0f, 104.0f), SVector2(1200, 100));
	UpgradeIcon->SetInWorld(false);
	CTM->AddUiObject(UpgradeIcon);


	// load music
	m_pMusic = new CMusic("Sound/Music/M_Music.wav");
	m_pMusic->Play(true);

	// get player reference
	for (CObject* pObject : CTM->GetPersistentObjects()) // search all scene objects
	{
		if (pObject->GetTag() == "Player") // player is found
		{
			m_pPlayer = (GPlayer*)pObject; // get the reference
			break;
		}
	}

#pragma region Upgrade Menu by Jonas
	int upgradeFrameWidth = 200;
	int upgradeframeDistance = (SCREEN_WIDTH - (int)EUpgrades::MAX * upgradeFrameWidth) / ((int)EUpgrades::MAX + 1); // calculate the distance between each tile to have a centered layout

	CTextObject* updatemenuTitle = new CTextObject
	(
		"Upgrades",
		GAME->GetFont(),
		SVector2(400, 80),
		SVector2(upgradeframeDistance + 200, 220),
		SColor(255, 255, 255, 255)
	);
	updatemenuTitle->SetInWorld(false);

	CTM->AddUiObject(updatemenuTitle);
	m_UpgradeMenu.AddObject(updatemenuTitle);

	for (int i = 0; i < (int)EUpgrades::MAX; i++)
	{
		GUpgradeFrame* pTempFrame = new GUpgradeFrame(SVector2(upgradeframeDistance * (i+1) + upgradeFrameWidth * i + upgradeFrameWidth * 0.5, 360), (EUpgrades)i);
		CTM->AddUiObject(pTempFrame);
		m_UpgradeMenu.AddObject(pTempFrame);

		// determine the upgrade type and set icon and description accordingly. assign the tempPointer of the scope to the specific member pointer
		switch ((EUpgrades)i)
		{
		case EUpgrades::AttackSpeed:
			pTempFrame->SetDescription("Attackspeed +20%");
			pTempFrame->SetIcon("Texture/UI/Upgrades/T_AttackSpeed.png");
			m_pAttackSpeedUpgrade = pTempFrame;
			break;
		case EUpgrades::Damage:
			pTempFrame->SetDescription("Attack Damage +20%");
			pTempFrame->SetIcon("Texture/UI/Upgrades/T_AttackPower.png");
			m_pDamageUpgrade = pTempFrame;
			break;
		case EUpgrades::MovementSpeed:
			pTempFrame->SetDescription("Movementspeed +10%");
			pTempFrame->SetIcon("Texture/UI/Upgrades/T_MovementSpeed.png");
			m_pSpeedUpgrade = pTempFrame;
			break;
		case EUpgrades::AttackRange:
			pTempFrame->SetDescription("Range +4");
			pTempFrame->SetIcon("");
			m_pRangeUpgrade = pTempFrame;
			break;
		case EUpgrades::SpecialAttack:
			pTempFrame->SetDescription("Unlocks the UV-Laser");
			pTempFrame->SetIcon("Texture/UI/Upgrades/T_LaserUpgrade.png");
			m_pLaserUpgrade = pTempFrame;
			break;
		default:
			break;
		}
	}

	m_UpgradeMenu.SetVisible(false); // hide upgrade menu on start
#pragma endregion
}

// update every frame
void GMainScene::Update(float _deltaSeconds)
{
	// quit game
	if (CInput::GetKeyDown(SDL_SCANCODE_ESCAPE))
		ENGINE->ChangeScene(new GMenuScene());

	// upgrade menu toggle
	if (CInput::GetKeyDown(SDL_SCANCODE_U))
	{
		m_UpgradeMenuVisibility = !m_UpgradeMenuVisibility;
		m_UpgradeMenu.SetVisible(m_UpgradeMenuVisibility);
		m_pPlayer->UpdateStats();
	}

	if (CInput::GetMouseButtonDown(0) && m_UpgradeMenu.IsSetVisible())
	{
		for (CObject* pObject : m_UpgradeMenu.GetChildren())
		{
			if (dynamic_cast<GUpgradeFrame*>(pObject))
			{
				GUpgradeFrame* pTemp = (GUpgradeFrame*)pObject;
				SRect mouse = SRect(1, 1, CInput::GetMousePosition().X, CInput::GetMousePosition().Y);
				if (RectRectCollision(pTemp->GetRect(), mouse))
				{
					pTemp->OnClick();
				}
			}
		}
	}
}

// render every frame
void GMainScene::Render()
{

}

// clean up scene
void GMainScene::Clean()
{
	GUpgradeManager::GetInstance()->Reset(); // reset the UGM
	delete m_pMusic;
	CTM->CleanPersistentObjects(); // remove player, enemies, UPs, exit
}
