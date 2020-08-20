#include "UpgradeIcon.h"

void GUpgradeIcon::Render()
{
	CTexturedObject::Render();
	m_pUpgradePointNumber->Render();
}

void GUpgradeIcon::Update(float _deltaSeconds)
{
	int CurrentUpgradePoints = GUpgradeManager::GetInstance()->GetUpgradePointCount();
	if (CurrentUpgradePoints != m_previousUPCount)
	{
		m_pUpgradePointNumber->SetText(to_string(CurrentUpgradePoints).c_str());
		m_previousUPCount = CurrentUpgradePoints;
	}

	m_pUpgradePointNumber->Update(_deltaSeconds);
	CTexturedObject::Update(_deltaSeconds);
}
