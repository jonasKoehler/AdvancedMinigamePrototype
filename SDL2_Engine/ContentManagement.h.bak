#pragma once

#pragma region system include
#include <list>
#pragma endregion

#pragma region project include
#include "Engine.h"
#pragma endregion

#pragma region forward decleration
class CObject;
#pragma endregion

#pragma region using
using namespace std;
#pragma endregion

#pragma region value macro
#define CTM CEngine::Get()->GetCTM()
#pragma endregion

/// <summary>
/// class to handle content
/// </summary>
class CContentManagement
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	CContentManagement() {}
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	~CContentManagement();
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// add object to scene list
	/// </summary>
	/// <param name="_pObject">object reference to add</param>
	inline void AddSceneObject(CObject* _pObject) { m_sceneObjects.push_back(_pObject); }

	/// <summary>
	/// get all scene objects
	/// </summary>
	/// <returns>list of all scene objects</returns>
	inline list<CObject*> GetSceneObjects() { return m_sceneObjects; }

	/// <summary>
	/// get all persistent objects
	/// </summary>
	/// <returns>list of all persistent objects</returns>
	inline list<CObject*> GetPersistentObjects() { return m_persistentObjects; }

	/// <summary>
	/// get all ui objects
	/// </summary>
	/// <returns>list of all ui objects</returns>
	inline list<CObject*> GetUiObjects() { return m_uiObjects; }

	/// <summary>
	/// add object to persistent list
	/// </summary>
	/// <param name="_pObject">object reference to add</param>
	inline void AddPersistentObject(CObject* _pObject) { m_persistentObjects.push_back(_pObject); }

	/// <summary>
	/// add object to ui list
	/// </summary>
	/// <param name="_pObject">object reference to add</param>
	inline void AddUiObject(CObject* _pObject) { m_uiObjects.push_back(_pObject); }

	/// <summary>
	/// remove object
	/// </summary>
	/// <param name="_pObject">object referece to remove</param>
	inline void RemoveObject(CObject* _pObject) { m_removeObjects.push_front(_pObject); }
#pragma endregion

#pragma region public function
	/// <summary>
	/// update every frame
	/// </summary>
	/// <param name="_deltaSeconds">time since last frame</param>
	void Update(float _deltaSeconds);

	/// <summary>
	/// render every frame
	/// </summary>
	void Render();

	/// <summary>
	/// delete all scene objects
	/// </summary>
	void CleanSceneObjects();

	/// <summary>
	/// delete all persistent objects
	/// </summary>
	void CleanPersistentObjects();

	/// <summary>
	/// delete all ui objects
	/// </summary>
	void CleanUiObjects();
#pragma endregion

private:
#pragma region private variable
	/// <summary>
	/// all scene objects list
	/// </summary>
	list<CObject*> m_sceneObjects;

	/// <summary>
	/// all persistent objects list
	/// </summary>
	list<CObject*> m_persistentObjects;

	/// <summary>
	/// all ui objects list
	/// </summary>
	list<CObject*> m_uiObjects;

	/// <summary>
	/// all objects to remove
	/// </summary>
	list<CObject*> m_removeObjects;
#pragma endregion
};