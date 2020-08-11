#pragma once
#include "MoveObject.h"
class GEntity :	public CMoveObject //by Lukas
{
public:
	GEntity(const char* _pFile, SVector2 _size, SVector2 _pos = SVector2()) : CMoveObject(_pFile, _size, _pos)
	{}

	virtual ~GEntity() {}

	//missing update and render

	inline float GetHealth() { return m_health; }
	void SetHealth(float _health); 
	void SetDamage(float _damage); // not needed, no outside class should be able to set the damage
	// missing gethealth
	void TakeDamage(float _damage, GEntity* _defender); // why defender? entity that calls the method should recieve the damage logic wise
	//Protected Vars
protected:
	float m_health = 100;
	float m_damage = 1;




	//Protected Virtual
	virtual void CheckIfDead();

};

