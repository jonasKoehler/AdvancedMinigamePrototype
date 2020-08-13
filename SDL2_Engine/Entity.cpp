#include "Entity.h"
#include <math.h>

void GEntity::SetHealth(float _health)
{
	m_health = _health;
}

void GEntity::SetDamage(float _damage)
{
	m_damage = _damage;
}

void GEntity::TakeDamage(float _damage)
{
	m_health -= _damage;
}

void GEntity::CheckIfDead() // purpose of the method?
{

}
