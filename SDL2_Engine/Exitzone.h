#pragma once
#pragma region engine includes
#include "TexturedObject.h"
#pragma endregion


class GExitzone :	public CTexturedObject
{
#pragma region constructor / destructor
public:
	GExitzone(const char* _pFile, SVector2 _size, SVector2 _pos = SVector2()) : CTexturedObject(_pFile, _size, _pos)
	{}

	virtual ~GExitzone() 
	{}
#pragma endregion

#pragma region public member functions
	void Render() override;

	void Update(float _deltaSeconds) override;
#pragma endregion

#pragma region private member variables
	CTexturedObject* m_pPlayer = nullptr; // reference on player in CTM
#pragma endregion
};

