#include "Entity.h"

void GEntity::SetHealth(float _health)
{
	m_health = _health;
}

void GEntity::SetDamage(float _damage)
{
	m_damage = _damage;
}

void GEntity::TakeDamage(float _damage, GEntity* _defender)
{
	_defender->SetHealth(_defender->GetHealth() - _damage);
}

void GEntity::CheckIfDead() // purpose of the method?
{

}
