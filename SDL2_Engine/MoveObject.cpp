#pragma region project include
#include "ContentManagement.h"
#include "Physic.h"
#include "Macro.h"
#include "MoveObject.h"
#pragma endregion

#pragma region public override function
// update every frame
void CMoveObject::Update(float _deltaSeconds)
{
	// set moveable default true
	bool moveable = true;

	// if no collision type
	if (m_colType == ECollisionType::NONE)
	{
		// set add position by movement and speed
		m_position += m_movement * m_speed * _deltaSeconds;

		// update parent and return
		CTexturedObject::Update(_deltaSeconds);
		return;
	}

	// get current rect
	SRect nextRect = m_rect;

	// if gravity active
	if (m_gravity)
	{
		// increase fall time
		m_fallTime += _deltaSeconds;

		// calculate rect position y with gravity and falltime
		nextRect.y += (GRAVITY * PIXEL_IN_METER) * m_fallTime * _deltaSeconds;

		// check every scene object
		for (CObject* pObject : CTM->GetSceneObjects())
		{
			// try to get textured object from current object
			CTexturedObject* pTexObj = dynamic_cast<CTexturedObject*>(pObject);

			// if no textured object or this continue to next object
			if (!pTexObj || pTexObj == this)
				continue;

			// if current object has no collision type continue to next object
			if (pTexObj->GetColType() == ECollisionType::NONE)
				continue;

			// set movable by check collision with other rect
			moveable = !RectRectCollision(nextRect, pTexObj->GetRect());

			// if not moveable stop checking coming objects
			if (!moveable)
			{
				OnCollisionEnter(pObject);
				break;
			}
		}

		// if still moveable
		if (moveable)
		{
			// check every persistent object
			for (CObject* pObject : CTM->GetPersistentObjects())
			{
				// try to get textured object from current object
				CTexturedObject* pTexObj = dynamic_cast<CTexturedObject*>(pObject);

				// if no textured object or this continue to next object
				if (!pTexObj || pTexObj == this)
					continue;

				// if current object has no collision type continue to next object
				if (pTexObj->GetColType() == ECollisionType::NONE)
					continue;

				// set movable by check collision with other rect
				moveable = !RectRectCollision(nextRect, pTexObj->GetRect());

				// if not moveable stop checking coming objects
				if (!moveable)
				{
					OnCollisionEnter(pObject);
					break;
				}
			}
		}

		// if still moveable
		if (moveable)
		{
			// add gravity movement to position
			m_position.Y += (GRAVITY * PIXEL_IN_METER) * m_fallTime * _deltaSeconds;

			// set rect to new position y
			m_rect.y = m_position.Y - m_rect.h * 0.5f;

			// reset next rect to current rect
			nextRect = m_rect;
		}

		// if not moveable
		else
		{
			// reset fall time
			m_fallTime = 0.0f;
		}

		// decrease position y of next rect to not stuck in ground
		nextRect.y--;

		// reset moveable true
		moveable = true;
	}

	// calculate next rect position by movement and speed
	nextRect.x += m_movement.X * m_speed * _deltaSeconds;
	nextRect.y += m_movement.Y * m_speed * _deltaSeconds;

	// check every scene object
	for (CObject* pObject : CTM->GetSceneObjects())
	{
		// try to get textured object from current object
		CTexturedObject* pTexObj = dynamic_cast<CTexturedObject*>(pObject);

		// if no textured object or this continue to next object
		if (!pTexObj || pTexObj == this)
			continue;

		// if current object has no collision type continue to next object
		if (pTexObj->GetColType() == ECollisionType::NONE)
			continue;

		// set movable by check collision with other rect
		moveable = !RectRectCollision(nextRect, pTexObj->GetRect());

		// if not moveable stop checking coming objects
		if (!moveable)
		{
			OnCollisionEnter(pObject);
			break;
		}
	}

	// if still moveable
	if (moveable)
	{
		// check every persistent object
		for (CObject* pObject : CTM->GetPersistentObjects())
		{
			// try to get textured object from current object
			CTexturedObject* pTexObj = dynamic_cast<CTexturedObject*>(pObject);

			// if no textured object or this continue to next object
			if (!pTexObj || pTexObj == this)
				continue;

			// if current object has no collision type continue to next object
			if (pTexObj->GetColType() == ECollisionType::NONE)
				continue;

			// set movable by check collision with other rect
			moveable = !RectRectCollision(nextRect, pTexObj->GetRect());

			// if not moveable stop checking coming objects
			if (!moveable)
			{
				OnCollisionEnter(pObject);
				break;
			}
		}
	}

	// if still moveable
	if (moveable)
		// add position by movement and speed
		m_position += m_movement * m_speed * _deltaSeconds;

	// update parent
	CTexturedObject::Update(_deltaSeconds);
}

// render every frame
void CMoveObject::Render()
{
	// render parent
	CTexturedObject::Render();
}
#pragma endregion
