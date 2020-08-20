#pragma once
#pragma region engine includes
#include "Rect.h"
#include "TextObject.h"
#pragma endregion

#pragma region game includes
#include "EUpgrades.h"
#pragma endregion

#pragma region std includes
#include <string>
#pragma endregion


class GUpgradeFrame : public CObject // by Jonas
{
#pragma region Constructor / Destructor
public:
	GUpgradeFrame(SVector2 _position, EUpgrades _upgradeType);

	virtual ~GUpgradeFrame() 
	{
		delete m_Description;
		delete m_UpgradeCost;
		delete m_UpgradeLevel;
	}
#pragma endregion

#pragma region public methods
// the class handles updating and rendering for its child elements
public:
	void Update(float _deltaSeconds) override;
	void Render() override;
	void SetRenderingIndicator(bool _toggle) override;
	void OnClick();
	void SetIcon(const char* _filePath);
	void SetDescription(string _description);
	inline SRect GetRect() { return m_FrameRect; }
#pragma endregion

#pragma region private variables
private:
	SRect m_FrameRect = SRect();
	EUpgrades m_UpgradeType;
	CTexturedObject m_Frame;
	CTexturedObject m_Icon;
	CTextObject* m_UpgradeLevel;
	CTextObject* m_UpgradeCost;
	CTextObject* m_Description;
#pragma endregion

};

