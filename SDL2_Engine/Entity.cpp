#include "Entity.h"
#include <math.h>

void GEntity::TakeDamage(float _damage)
{
	m_health -= _damage;
}

void GEntity::CheckIfDead() // purpose of the method?
{

}
