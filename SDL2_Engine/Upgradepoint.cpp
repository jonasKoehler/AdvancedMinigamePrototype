#include "Upgradepoint.h"
#include "UpgradeManager.h"
#include "Physic.h"

void GUpgradepoint::Render()
{
	CTexturedObject::Render();
}

void GUpgradepoint::Update(float _deltaSeconds)
{
	// get player reference
	if (!m_pPlayer)
	{
		for (CObject* pObject : CTM->GetPersistentObjects())
		{
			if (pObject->GetTag() == "Player")
			{
				m_pPlayer = (CTexturedObject*)pObject;
			}
		}
	}
	else // if player reference is set, check collision
	{
		if (RectRectCollision(m_rect, m_pPlayer->GetRect()) && m_render)
		{
			m_pPickUpSound->Play();
			GUpgradeManager::GetInstance()->AddUpgradePoint();
			m_render = false;
		}
	}

	// when invisible start timer until destruction to let the sound play
	if (!m_render)
	{
		m_DeathTimer -= _deltaSeconds;
		if (m_DeathTimer <= 0)
		{
			CTM->RemoveObject(this);
		}
	}

	CTexturedObject::Update(_deltaSeconds);
}
