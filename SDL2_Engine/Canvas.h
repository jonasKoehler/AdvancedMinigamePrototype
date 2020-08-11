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
	CCanvas() {}

	~CCanvas() {}

public:
	inline void SetVisible(bool _toggle)
	{
		for (CObject* pChild : m_Children)
		{
			// set rendering of child to toggle
		}
	}

	inline void AddObject(CObject* _pObject) { m_Children.push_front(_pObject); }

private:
	list<CObject*> m_Children;
};

