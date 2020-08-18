#pragma once
#pragma region engine include
#include "Entity.h"
#include "Animation.h"
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
	};

	/// <summary>
	/// destructor
	/// </summary>
	virtual ~GEnemy() {}
#pragma endregion

#pragma region constructor / destructor
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

private:
#pragma region private variablea
	SVector2* m_playerpos = nullptr; // reference to position of the player !DO NOT DELETE!
#pragma endregion
};