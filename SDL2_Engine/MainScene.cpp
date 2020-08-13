#pragma region engine include
#include "Input.h"
#include "ContentManagement.h"
#include "TextObject.h"
#pragma endregion

#pragma region game include
#include "Game.h"
#include "World.h"
#include "MainScene.h"
#include "MenuScene.h"
#include "UpgradeFrame.h"
#include "UpgradeManager.h"
#pragma endregion

#pragma region public override function
// initialize scene
void GMainScene::Init()
{
	// load world
	LoadWorldFromString();
	m_pMusic = new CMusic("Sound/Music/music.wav");
	m_pMusic->Play(true);

	// upgrade menu
	CTextObject* updatemenuTitle = new CTextObject
	(
		"Upgrades",
		GAME->GetFont(),
		SVector2(400, 80),
		SVector2(300, 60),
		SColor(255, 255, 255, 255)
	);
	updatemenuTitle->SetInWorld(false);

	m_pAttackSpeedUpgrade = new GUpgradeFrame(SVector2(100, 360), EUpgrades::AttackSpeed);
	m_pAttackSpeedUpgrade->SetDescription("Attackspeed +20%");
	m_pAttackSpeedUpgrade->SetIcon("Texture/UI/Upgrades/T_AttackSpeed.png");
	
	m_pDamageUpgrade = new GUpgradeFrame(SVector2(320, 360), EUpgrades::Damage);
	m_pDamageUpgrade->SetDescription("Attack Damage +20%");
	m_pDamageUpgrade->SetIcon("Texture/UI/Upgrades/T_AttackPower.png");
	
	m_pRangeUpgrade = new GUpgradeFrame(SVector2(540, 360), EUpgrades::AttackRange);
	m_pRangeUpgrade->SetDescription("Range +4");
	m_pRangeUpgrade->SetIcon("");
	
	m_pSpeedUpgrade = new GUpgradeFrame(SVector2(760, 360), EUpgrades::MovementSpeed);
	m_pSpeedUpgrade->SetDescription("Movementspeed +20%");
	m_pSpeedUpgrade->SetIcon("Texture/UI/Upgrades/T_MovementSpeed.png");
	
	m_pLaserUpgrade = new GUpgradeFrame(SVector2(980, 360), EUpgrades::SpecialAttack);
	m_pLaserUpgrade->SetDescription("Unlocks the UV-Laser");
	m_pLaserUpgrade->SetIcon("Texture/UI/Upgrades/T_LaserUpgrade.png");

	CTM->AddUiObject(m_pAttackSpeedUpgrade);
	CTM->AddUiObject(m_pDamageUpgrade);
	CTM->AddUiObject(m_pRangeUpgrade);
	CTM->AddUiObject(m_pSpeedUpgrade);
	CTM->AddUiObject(m_pLaserUpgrade);
	CTM->AddUiObject(updatemenuTitle);

	m_UpgradeMenu.AddObject(updatemenuTitle);
	m_UpgradeMenu.AddObject(m_pAttackSpeedUpgrade);
	m_UpgradeMenu.AddObject(m_pDamageUpgrade);
	m_UpgradeMenu.AddObject(m_pRangeUpgrade);
	m_UpgradeMenu.AddObject(m_pSpeedUpgrade);
	m_UpgradeMenu.AddObject(m_pLaserUpgrade);

	m_UpgradeMenu.SetVisible(false);
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
	}
}

// render every frame
void GMainScene::Render()
{

}

// clean up scene
void GMainScene::Clean()
{
	delete m_pMusic;
	delete m_pRangeUpgrade;
	delete m_pAttackSpeedUpgrade;
	delete m_pSpeedUpgrade;
	delete m_pLaserUpgrade;
	delete m_pDamageUpgrade;
}
#pragma endregion