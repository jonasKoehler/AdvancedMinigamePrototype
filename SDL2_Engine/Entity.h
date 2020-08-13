#pragma once
#include "MoveObject.h"
class GEntity : public CMoveObject //by Lukas
{
#pragma region constructor / destructor
public:
	GEntity(const char* _pFile, SVector2 _size, SVector2 _pos = SVector2()) : CMoveObject(_pFile, _size, _pos) {}

	virtual ~GEntity() {}
#pragma endregion

#pragma region public functions
public:
	//missing update and render
	inline float GetHealth() { return m_health; }
	inline void SetHealth(float _health) { m_health = _health; };
	virtual void TakeDamage(float _damage);
#pragma endregion

#pragma region protected functions
	virtual void CheckIfDead();
#pragma endregion

#pragma region protected variables
protected:
	float m_health = 100;
	float m_damage = 1;
#pragma endregion
};

