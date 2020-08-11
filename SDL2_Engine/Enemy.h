#pragma once

#pragma region engine include
#include "Entity.h"
#include "Animation.h"
#pragma endregion

#pragma region game include
#include "Config.h"
class GPlayer;

#pragma endregion

/// <summary>
/// class for enemy behaviour
/// </summary>
class GEnemy : public GEntity
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pFileName">texture relative file path</param>
	/// <param name="_size">size of texture</param>
	/// <param name="_pos">position of player</param>
	GEnemy(const char* _pFile, SVector2 _size, SVector2 _pos = SVector2()) : GEntity(_pFile, _size, _pos) 
	{
		SetColType(ECollisionType::DYNAMIC);
		SetSpeed(50);
		SetTag("Enemy");
		m_damage = 10;
	};
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
	

protected:

	void CheckIfDead() override;
	void MoveToPlayer();
	void OnCollisionEnter(CObject* pObject) override;


#pragma endregion

protected:
#pragma region protected primitive variable
	/// <summary>
	/// time in movement direction
	/// </summary>
	float m_timerInMovement = 1.0f;

	SVector2 m_playerpos; //position of the player
#pragma endregion
};