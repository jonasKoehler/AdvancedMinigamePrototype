#pragma once
#include "MoveObject.h"
class GEntity :	public CMoveObject
{
public:
	GEntity(const char* _pFile, SVector2 _size, SVector2 _pos = SVector2()) : CMoveObject(_pFile, _size, _pos)
	{}

	virtual ~GEntity() {}

	inline float GetHealth() { return m_health; }
	void SetHealth(float _health);
	void SetDamage(float _damage);

	void TakeDamage(float _damage, GEntity* _defender);
	//Protected Vars
protected:
	float m_health = 100;
	float m_damage = 1;




	//Protected Virtual
	virtual void CheckIfDead();

};

