#pragma once
#pragma region engine includes
#include "TexturedObject.h"
#include "Sound.h"
#pragma endregion

class GUpgradepoint : public CTexturedObject
{
#pragma region constructor / destructor
public:
	GUpgradepoint(const char* _pFile, SVector2 _size, SVector2 _pos = SVector2()) : CTexturedObject(_pFile, _size, _pos) 
	{
		m_pPickUpSound = new CSound("Sound/Effects/S_Collect.wav");
	}

	~GUpgradepoint()
	{
		delete m_pPickUpSound;
	}
#pragma endregion

#pragma region public member functions
	void Render() override;

	void Update(float _deltaSeconds) override;
#pragma endregion

#pragma region private member variables
	CTexturedObject* m_pPlayer = nullptr;
	CSound* m_pPickUpSound = nullptr;
	float m_DeathTimer = 3.0f; // timer in seconds for object deletion
#pragma endregion
};

