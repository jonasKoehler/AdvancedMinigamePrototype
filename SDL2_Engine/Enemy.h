#pragma once
#pragma region engine include
#include "Entity.h"
#include "WobbleAnimation.h"
#pragma endregion

/// <summary>
/// class for enemy behaviour
/// </summary>
class GEnemy : public GEntity
{
#pragma region constructor / destructor
public:
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

		m_animation.InitHorizontal(20, 0, 2);
		m_animation.InitVertical(10, 10, 1);
	};

	/// <summary>
	/// destructor
	/// </summary>
	virtual ~GEnemy() {}
#pragma endregion

#pragma region public functions
	/// <summary>
	/// update every frame
	/// </summary>
	/// <param name="_deltaSeconds">time since last frame</param>
	virtual void Update(float _deltaSeconds) override;

	/// <summary>
	/// render every frame
	/// </summary>
	virtual	void Render() override;
#pragma endregion

#pragma region private funtions
private:
	void CheckIfDead() override;
	void MoveToPlayer();
	void OnCollisionEnter(CObject* pObject) override;
#pragma endregion

#pragma region private variablea
private:
	SVector2* m_playerpos = nullptr; // reference to position of the player !DO NOT DELETE!
	CWobbleAnimation m_animation = CWobbleAnimation(&m_rect);
	int m_DetectionRange = 500; // range in pixels which the enemy detects the player
	bool m_Engaged = false; // determines if enemy walks towards player
#pragma endregion
};