#pragma once

#pragma region engine include
#include "MoveObject.h"
#include "Animation.h"
#pragma endregion

#pragma region game include
#include "Config.h"
class GPlayer;

#pragma endregion

/// <summary>
/// class for enemy behaviour
/// </summary>
class GEnemy : public CMoveObject
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pFileName">texture relative file path</param>
	/// <param name="_size">size of texture</param>
	/// <param name="_pos">position of player</param>
	GEnemy(const char* _pFile, SVector2 _size, SVector2 _pos = SVector2()) : CMoveObject(_pFile, _size, _pos)
	{
		m_anim.SetAnimationTime(0.5f);
	}
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	virtual ~GEnemy() {}
#pragma endregion

#pragma region public  function
	/// <summary>
	/// update every frame
	/// </summary>
	/// <param name="_deltaSeconds">time since last frame</param>
	virtual void Update(float _deltaSeconds) override;

	/// <summary>
	/// render every frame
	/// </summary>
	virtual	void Render() override;
	
	inline float GetHealth() { return m_health; }
	void SetHealth(float _health);



protected:

	void CheckIfDead();
	void MoveToPlayer();
	void OnCollisionEnter(CObject* pObject) override;
	void TakeDamage(float _damage, GPlayer* _player);

#pragma endregion

protected:
#pragma region protected primitive variable
	/// <summary>
	/// time in movement direction
	/// </summary>
	float m_timerInMovement = 1.0f;
	float m_health = 100;
	float m_damage = 1; //damage of the entity
	SVector2 m_playerpos; //position of the player
#pragma endregion

#pragma region protected variable
	/// <summary>
	/// animation
	/// </summary>
	CAnimation m_anim = CAnimation(SVector2(), SVector2(PLAYER_SRC_WALK_WIDTH, PLAYER_SRC_WALK_HEIGHT), 4);
#pragma endregion
};