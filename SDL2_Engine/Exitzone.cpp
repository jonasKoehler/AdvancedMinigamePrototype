#include "Exitzone.h"
#include "Physic.h"
#include "Game.h"
#include "EndScene.h"

void GExitzone::Render()
{
	CTexturedObject::Render();
}

void GExitzone::Update(float _deltaSeconds)
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
		if (RectRectCollision(m_rect, m_pPlayer->GetRect()))
		{
			GAME->m_Won = true;
			ENGINE->ChangeScene(new GEndScene());
			return;
		}
	}

	CTexturedObject::Update(_deltaSeconds);
}
