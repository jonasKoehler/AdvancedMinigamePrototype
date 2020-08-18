#include "WorldTile.h"

void GWorldTile::Render()
{
	if (m_pDetail)
		m_pDetail->Render();

	CTexturedObject::Render();
}

void GWorldTile::Update(float _deltaSeconds)
{
	if (m_pDetail)
	{
		m_pDetail->SetPosition(m_position);
		m_pDetail->Update(_deltaSeconds);
	}
	CTexturedObject::Update(_deltaSeconds);
}
