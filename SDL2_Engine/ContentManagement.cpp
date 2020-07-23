#pragma region engine include
#include "ContentManagement.h"
#include "Object.h"
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

		// free object memory
		delete pObject;
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
#pragma endregion