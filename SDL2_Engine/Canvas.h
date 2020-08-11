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

public:
	inline void SetVisible(bool _toggle)
	{
		for (CObject* pChild : m_Children)
		{
			pChild->SetRenderingIndicator(_toggle);
		}
	}

	inline void AddObject(CObject* _pObject) { m_Children.push_front(_pObject); }

private:
	list<CObject*> m_Children;
};

