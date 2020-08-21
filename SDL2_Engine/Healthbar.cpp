#include "Healthbar.h"
#include "Player.h"

void GHealthbar::Render()
{
	m_Bar.Render();
	m_Frame.Render();
}

void GHealthbar::Update(float _deltaSeconds)
{
	// get player reference
	if (!m_pPlayer)
	{
		m_pPlayer = GPlayer::GetInstance();
		if (m_pPlayer)
		{
			// set health values if reference is found
			m_PrevPlayerHealth = m_pPlayer->GetHealth();
			m_MaxPlayerHealth = m_PrevPlayerHealth;
		}
		return;
	}

	float currentPlayerHealth = m_pPlayer->GetHealth(); // current player health variable

	// only enter this statement if health actually changed, saves minor calculations
	if (m_PrevPlayerHealth != currentPlayerHealth)
	{
		SRect bar = m_Bar.GetRect(); // rect that will be transformed
		int newWidth = m_BaseWidth * (currentPlayerHealth / m_MaxPlayerHealth); // new width based on health percentage lost
		m_Bar.AddPosition(SVector2((bar.w - newWidth) * -0.5, 0)); // recalculation of position since its the center
		bar.w = newWidth;
		m_Bar.SetRect(bar);
		m_PrevPlayerHealth = currentPlayerHealth; // updating health values
	}

	m_Bar.Update(_deltaSeconds);
	m_Frame.Update(_deltaSeconds);
}