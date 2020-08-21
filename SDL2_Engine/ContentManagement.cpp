#pragma region system include
#include <algorithm>
#pragma endregion

#pragma region project include
#include "ContentManagement.h"
#include "MoveObject.h"
#include "Time.h"
#pragma endregion

#pragma region destructor
// destructor
CContentManagement::~CContentManagement()
{
	// remove first object of scene list until no object left
	while (m_sceneObjects.size())
		m_sceneObjects.pop_front();

	// remove first object of persistent list until no object left
	while (m_persistentObjects.size())
		m_persistentObjects.pop_front();

	// remove first object of ui list until no object left
	while (m_uiObjects.size())
		m_uiObjects.pop_front();
}
#pragma endregion

#pragma region public function
// update every frame
void CContentManagement::Update(float _deltaSeconds)
{
	// while objects to remove left
	while (m_removeObjects.size())
	{
		// get first object of list to remove
		CObject* pObject = m_removeObjects.front();

		// remove object reference from lists
		m_sceneObjects.remove(pObject);
		m_persistentObjects.remove(pObject);
		m_uiObjects.remove(pObject);
		m_removeObjects.remove(pObject);
		m_moveObjects.remove((CMoveObject*)pObject);

		// free object memory
		delete pObject;
	}

	// increase collision timer
	m_colTimer += _deltaSeconds;

	// while collision timer is high enough
	while (m_colTimer >= 0.2f / m_moveObjects.size())
	{
		// get first move object
		CMoveObject* pMoveObject = m_moveObjects.front();

		// set collision objects
		pMoveObject->SetColObjects();

		// remove move object and add to end of list
		m_moveObjects.remove(pMoveObject);
		m_moveObjects.push_back(pMoveObject);

		// if move objects more than frames per second
		if (m_moveObjects.size() > CTime::GetFPS())
			// decrease collision timer
			m_colTimer -= 0.2f / CTime::GetFPS();

		// if move objects not more than frames per second
		else
			// reset collision timer
			m_colTimer = 0.0f;
	}

	// update every scene object
	for (CObject* pObject : m_sceneObjects)
		pObject->Update(_deltaSeconds);

	// update every persistent object
	for (CObject* pObject : m_persistentObjects)
		pObject->Update(_deltaSeconds);

	// update every ui object
	for (CObject* pObject : m_uiObjects)
		pObject->Update(_deltaSeconds);
}

// render every frame
void CContentManagement::Render()
{
	// render every scene object
	for (CObject* pObject : m_sceneObjects)
		pObject->Render();

	// render every persistent object
	for (CObject* pObject : m_persistentObjects)
		pObject->Render();

	// render every ui object
	for (CObject* pObject : m_uiObjects)
		pObject->Render();
}

// delete all scene objects
void CContentManagement::CleanSceneObjects()
{
	// add every scene object to remove objects list
	for (CObject* pObject : m_sceneObjects)
		m_removeObjects.push_front(pObject);
}

// delete all persistent objects
void CContentManagement::CleanPersistentObjects()
{
	// add every persistent object to remove objects list
	for (CObject* pObject : m_persistentObjects)
		m_removeObjects.push_front(pObject);
}

// delete all ui objects
void CContentManagement::CleanUiObjects()
{
	// add every ui object to remove objects list
	for (CObject* pObject : m_uiObjects)
		m_removeObjects.push_front(pObject);
}

// sort objects
void CContentManagement::SortObjects(CObject* _pObject)
{
	// iterator and current list reference
	list<CObject*>::iterator it;
	list<CObject*>* pList = &m_sceneObjects;

	// check every list
	for (int i = 0; i < 3; i++)
	{
		// try to find object in current list
		it = find(pList->begin(), pList->end(), _pObject);

		// if object is in current list
		if (it != pList->end())
		{
			// remove object from list
			pList->remove(_pObject);

			// if list is empty
			if (!pList->size())
			{
				// add object at front of list
				pList->push_front(_pObject);
			}

			// if list not empty
			else
			{
				// iterator to insert object into list
				list<CObject*>::iterator insertIt = pList->begin();

				// check every object in list
				for (insertIt = pList->begin(); insertIt != pList->end(); ++insertIt)
				{
					// if objects layer is lower than current objects layer from list
					if (_pObject->GetLayer() < (*insertIt)->GetLayer())

						// if current obeject is the front of the list
						if (insertIt == pList->begin())
							// add object at front of list
							pList->push_front(_pObject);

					// if current object is not at front os list
						else
							// insert object before current object in list
							pList->insert(insertIt, _pObject);
				}

				// try to find object in list
				it = find(pList->begin(), pList->end(), _pObject);

				// if object not in list
				if (it == pList->end())
					// add object at end of list
					pList->push_back(_pObject);
			}
		}

		// if current index is one
		if (!i)
			// set current list to persistent object list
			pList = &m_persistentObjects;

		// if current index is not one
		else
			// set current list to ui object list
			pList = &m_uiObjects;
	}
}
#pragma endregion

#pragma region private function
// add object to list
void CContentManagement::AddObject(CObject* _pObject, list<CObject*>* _pList)
{
	// add object to list
	_pList->push_back(_pObject);
	SortObjects(_pObject);

	// try to get move object
	CMoveObject* pMoveObject = dynamic_cast<CMoveObject*>(_pObject);

	// if no move object return
	if (!pMoveObject)
		return;

	// add object to move object list and calculate collision objects
	m_moveObjects.push_back(pMoveObject);
	pMoveObject->SetColObjects();
}
#pragma endregion