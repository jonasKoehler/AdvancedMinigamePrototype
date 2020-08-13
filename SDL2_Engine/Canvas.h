#pragma region engine includes
#include "Object.h"
#pragma endregion

#pragma region std includes
#include <list>
using namespace std;
#pragma endregion

#pragma once
class CCanvas // by Jonas
{
#pragma region constructor / destructor
public:
	CCanvas() {}

	~CCanvas() {}
#pragma endregion

#pragma region public functions
public:
	/// <summary>
	/// toggles visibility of child objects
	/// </summary>
	/// <param name="_toggle"></param>
	inline void SetVisible(bool _toggle)
	{
		m_IsSetVisible = _toggle;
		for (CObject* pChild : m_Children)
		{
			pChild->SetRenderingIndicator(m_IsSetVisible);
		}
	}

	/// <summary>
	/// adds object to list
	/// </summary>
	/// <param name="_pObject"></param>
	inline void AddObject(CObject* _pObject) { m_Children.push_front(_pObject); }

	/// <summary>
	/// returns list of child objects
	/// </summary>
	/// <returns></returns>
	inline list<CObject*> GetChildren() { return m_Children; }

	/// <summary>
	/// returns current visibility state
	/// </summary>
	/// <returns></returns>
	inline bool IsSetVisible() { return m_IsSetVisible; }
#pragma endregion

#pragma region private variables
private:
	list<CObject*> m_Children; // list of child objects
	bool m_IsSetVisible = true; // current visibility state
#pragma endregion
};

