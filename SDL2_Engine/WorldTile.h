#pragma once
#include "TexturedObject.h"
class GWorldTile : public CTexturedObject
{
#pragma region contructor / destructor
public:
	GWorldTile(const char* _pFileName, SVector2 _size, SVector2 _pos = SVector2()) : CTexturedObject(_pFileName, _size, _pos)
	{

	}

	~GWorldTile()
	{
		delete m_pDetail;
	}
#pragma endregion

#pragma region public functions
public:
	void Render() override;

	void Update(float _deltaSeconds) override;

	inline void SetDetailObject(CTexturedObject* _detail) { m_pDetail = _detail; }
#pragma endregion

#pragma region private member variables
	CTexturedObject* m_pDetail = nullptr;
#pragma endregion

};

