#pragma once
#include "TextObject.h"
#include "Game.h"
#include "UpgradeManager.h"
#include <string>

class GUpgradeIcon : public CTexturedObject
{
#pragma region constructor / destructor
public:
	GUpgradeIcon(SVector2 _size, SVector2 _pos) : CTexturedObject("Texture/UI/IngameHUD/T_UpgradeIcon.png", _size, _pos)
	{
		m_previousUPCount = GUpgradeManager::GetInstance()->GetUpgradePointCount();
		m_pUpgradePointNumber = new CTextObject(to_string(m_previousUPCount).c_str(), GAME->GetFont(), SVector2(25, 25), SVector2(_pos.X, _pos.Y + 40), SColor(255, 255, 255, 255));
		m_pUpgradePointNumber->SetInWorld(false);
	}

	~GUpgradeIcon()
	{
		delete m_pUpgradePointNumber;
	}
#pragma endregion

#pragma region public member functions
public:
	void Render() override;

	void Update(float _deltaSeconds) override;
#pragma endregion

#pragma region private variables
private:
	int m_previousUPCount = 0;
	CTextObject* m_pUpgradePointNumber = nullptr;
#pragma endregion

};

