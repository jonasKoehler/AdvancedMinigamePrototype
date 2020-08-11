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

		// check collision with objects in range
		moveable = !CheckCollision(nextRect);

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

	// check collision with objects in range
	moveable = !CheckCollision(nextRect);

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

#pragma region public function
// set collision objects in move range
void CMoveObject::SetColObjects()
{
	// collision rect around object
	SRect colRect;
	colRect.x = m_position.X - m_speed - m_rect.w;
	colRect.y = m_position.Y - m_speed - m_rect.h;
	colRect.w = m_speed * 2.0f + 2.0f * m_rect.w;
	colRect.h = m_speed * 2.0f + 2.0f * m_rect.h;

	// if gravity enabled
	if (m_gravity)
	{
		// calculate collision rect y and h by absolute fall time
		float falltime = m_fallTime < 0.0f ? -m_fallTime : m_fallTime;
		colRect.y = m_position.Y - PIXEL_IN_METER * GRAVITY * (falltime + 1.0f) - m_rect.h;
		colRect.h = 2.0f * PIXEL_IN_METER * GRAVITY * (falltime + 1.0f) + 2.0f * m_rect.h;
	}

	// clear all collision objects
	m_colObject.clear();

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

		// if collision add current object to collision object list
		if (RectRectCollision(colRect, pTexObj->GetRect()))
			m_colObject.push_front(pTexObj);
		else
		{
			OnCollisionEnter(pObject);
		}
		

	}

	// check every scene object
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

		// if collision add current object to collision object list
		if (RectRectCollision(colRect, pTexObj->GetRect()))
			m_colObject.push_front(pTexObj);
		else
		{
			OnCollisionEnter(pObject);
		}
	}
}
#pragma endregion

#pragma region private function
// check collision with possible objects
bool CMoveObject::CheckCollision(SRect _nextRect)
{
	// check every collision object
	for (CTexturedObject* pObject : m_colObject)
		// check collision with current object
		if (RectRectCollision(_nextRect, pObject->GetRect()))
			// if collision return true
			return true;

		 else
		{
			OnCollisionEnter(pObject);
		}

	// if no collision with any object return false
	return false;
}




#pragma endregion