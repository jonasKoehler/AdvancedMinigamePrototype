#pragma region engine includes
#include "TextureManagement.h"
#pragma endregion

#pragma region Game inlcudes
#include "UpgradeManager.h"
#include "UpgradeFrame.h"
#include "Game.h"
#pragma endregion


GUpgradeFrame::GUpgradeFrame(SVector2 _position, EUpgrades _upgradeType)
{
	m_position = _position;
	m_UpgradeType = _upgradeType;
	m_FrameRect.x = _position.X;
	m_FrameRect.y = _position.Y;
	m_FrameRect.h = 200;
	m_FrameRect.w = 200;

	m_Frame = CTexturedObject
	(
		"Texture/UI/Upgrades/T_UpgradeFrame.png",
		SVector2(m_FrameRect.w, m_FrameRect.h),
		_position
	);

	m_Icon = CTexturedObject
	(
		"",
		SVector2(100, 100),
		SVector2(_position.X, _position.Y - 30)
	);

	m_Description = new CTextObject
	(
		"",
		GAME->GetFont(),
		SVector2(190, 20),
		SVector2(_position.X, _position.Y + 35),
		SColor()
	);

	m_UpgradeCost = new CTextObject
	(
		to_string(GUpgradeManager::GetInstance()->GetUpgradePrice(_upgradeType)).c_str(),
		GAME->GetFont(),
		SVector2(40, 40),
		SVector2(_position.X - 70, _position.Y + 70),
		SColor()
	);

	string upgradelevel = to_string(GUpgradeManager::GetInstance()->GetUpgradeLevel(_upgradeType)) + "/" + to_string(GUpgradeManager::GetInstance()->GetUpgradeMaxLevel(_upgradeType));
	m_UpgradeLevel = new CTextObject
	(
		upgradelevel.c_str(),
		GAME->GetFont(),
		SVector2(60, 40),
		SVector2(_position.X + 60, _position.Y + 70),
		SColor()
	);

	// all child elements are ui objects and are not rendered in the world
	m_Icon.SetInWorld(false);
	m_Frame.SetInWorld(false);
	m_UpgradeCost->SetInWorld(false);
	m_UpgradeLevel->SetInWorld(false);
	m_Description->SetInWorld(false);
}

void GUpgradeFrame::Update(float _deltaSeconds)
{
	m_Frame.Update(_deltaSeconds);
	m_Icon.Update(_deltaSeconds);
	m_UpgradeCost->Update(_deltaSeconds);
	m_UpgradeLevel->Update(_deltaSeconds);
	m_Description->Update(_deltaSeconds);
}

void GUpgradeFrame::Render()
{
	m_Frame.Render();
	m_Icon.Render();
	m_UpgradeCost->Render();
	m_UpgradeLevel->Render();
	m_Description->Render();
}

void GUpgradeFrame::SetRenderingIndicator(bool _toggle)
{
	m_Frame.SetRenderingIndicator(_toggle);
	m_Icon.SetRenderingIndicator(_toggle);
	m_UpgradeCost->SetRenderingIndicator(_toggle);
	m_UpgradeLevel->SetRenderingIndicator(_toggle);
	m_Description->SetRenderingIndicator(_toggle);
}

void GUpgradeFrame::OnClick()
{
	GUpgradeManager::GetInstance()->BuyUpgrade(m_UpgradeType); // attempts the purchase of the upgrade

	// update cost and level numbers
	m_UpgradeCost->SetText(to_string(GUpgradeManager::GetInstance()->GetUpgradePrice(m_UpgradeType)).c_str());
	string upgradelevel = to_string(GUpgradeManager::GetInstance()->GetUpgradeLevel(m_UpgradeType)) + "/" + to_string(GUpgradeManager::GetInstance()->GetUpgradeMaxLevel(m_UpgradeType));
	m_UpgradeLevel->SetText(upgradelevel.c_str());
}

void GUpgradeFrame::SetIcon(const char* _filePath)
{
	m_Icon.SetTexture(TTM->GetTexture(_filePath));
}

void GUpgradeFrame::SetDescription(string _description)
{
	m_Description->SetText(_description.c_str());
}
