#pragma once
#pragma region engine include
#include "Entity.h"
#include "Animation.h"
#include "Sound.h"
#pragma endregion

#pragma region game includes
#include "Config.h"
#include "UpgradeManager.h"
#pragma endregion

#pragma region std includes
#include <map>
using namespace std;
#pragma endregion

class GEnemy;

enum class EPlayerWalkDirection
{
	Right,
	Left,
	Down,
	Up,
	UpLeft,
	DownRight,
	UpRight,
	DownLeft,
	MAX
};

enum class EPlayerLookDirection
{
	Down,
	Up,
	Right,
	Left,
	DownRight,
	UpRight,
	DownLeft,
	UpLeft,
	MAX
};

class GPlayer : public GEntity
{
public:

#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pFileName">texture relative file path</param>
	/// <param name="_size">size of texture</param>
	/// <param name="_pos">position of player</param>
	GPlayer(const char* _pFile, SVector2 _size, SVector2 _pos = SVector2()) : GEntity("", _size, _pos)
	{
		UpdateStats();
		SetColType(ECollisionType::DYNAMIC);
		SetTag("Player");

		m_pHitzoneTexture = new CTexturedObject(_pFile, SVector2(), SVector2());
		m_pHitzoneTexture->SetRect(m_Hitzone);
		m_pHitzoneTexture->SetSrcRect(SRect(0, 330, 0, 5656));

		m_pUpperBody = new CTexturedObject
		(
			_pFile,
			SVector2(GConfig::s_PlayerWidth, GConfig::s_PlayerTopHeight),
			_pos
		);

		m_pLowerBody = new CTexturedObject
		(
			_pFile,
			SVector2(GConfig::s_PlayerWidth, GConfig::s_PlayerBottomHeight),
			_pos
		);

		for (int i = 0; i < (int)EPlayerLookDirection::MAX; i++)
		{
			m_LookDirectionSrcRects[(EPlayerLookDirection)i] = SRect(GConfig::s_PlayerSrcWidth, GConfig::s_PlayerTopSrcHeight, i * GConfig::s_PlayerSrcWidth, 0);
		}

		for (int i = 0; i < (int)EPlayerWalkDirection::MAX; i++)
		{
			m_WalkAnimations[(EPlayerWalkDirection)i] = new CAnimation
			(
				SVector2(0, GConfig::s_PlayerTopSrcHeight + i * GConfig::s_PlayerBottomSrcHeight),
				SVector2(GConfig::s_PlayerSrcWidth, GConfig::s_PlayerBottomSrcHeight),
				1,
				3,
				true
			);
		}

		m_pDeathRect = new CTexturedObject
		(
			"Texture/Character/Player/T_PlayerDeath.png",
			SVector2(GConfig::s_PlayerWidth, GConfig::s_PlayerTotalHeight),
			_pos
		);
		m_pDeathRect->SetRenderingIndicator(false);

		m_pDeath = new CAnimation
		(
			SVector2(),
			SVector2(1230, 2016),
			1.5,
			7,
			false
		);

		m_pAttack = new CAnimation
		(
			SVector2(-330, 5656),
			SVector2(330, 307),
			0.1,
			2,
			false
		);

		m_pBasicAttackSound = new CSound("Sound/Effects/spray.wav");
	}
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	virtual ~GPlayer()
	{
		delete m_pBasicAttackSound;
		m_WalkAnimations.clear(); // clear map, invalidating all pointers
		delete m_pAttack;
		delete m_pLowerBody;
		delete m_pUpperBody;
		delete m_pHitzoneTexture;
	}
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

	void UpdateStats(); // by Jonas
#pragma region private functions
private:
	void Rotate(); // by Jonas
	void Move(float _deltaSeconds); // by Jonas
	void BasicAttack();  // by Jonas
	void ReachExit(); // by Lukas
	void CheckIfDead() override; //by Lukas
	void TakeDamage(float _damage) override; // by Jonas
#pragma endregion


#pragma region private variables
private:
	int m_Angle = 0; // the angle between the cursor and player position
	SRect m_Hitzone = SRect(); // rect that determines if an enemy is in attack range
	float m_AttacksPerSecond = 1.5f; // the number of times the player can attack in a second
	float m_AttackCooldown = 1.0f; // one second attack cooldown	

	int m_IsInvincible = 0; // milliseconds of invincibility after getting hit
	float m_ChangeSceneCountdownOnDeath = 0; // seconds after player dies until scene change

	float m_AccelerationRate = 5.0f; // increases acceleration per sec (multiply with deltaTime)
	float m_DecelerationRate = 5.0f; // decreases acceleration per sec (multiply with deltaTime)

	CTexturedObject* m_pHitzoneTexture = nullptr; // texture rect for attackzone
	CTexturedObject* m_pUpperBody = nullptr; // texture rect for upperbody
	CTexturedObject* m_pLowerBody = nullptr; // texture rect for legs
	CTexturedObject* m_pDeathRect = nullptr; // texture rect for death animation

	CAnimation* m_pAttack = nullptr; // attack animation pointer
	CAnimation* m_pCurrentWalkAnimation = nullptr; // current walk animation pointer
	CAnimation* m_pDeath = nullptr; // death animation

	map<EPlayerLookDirection, SRect> m_LookDirectionSrcRects; // map containing the source rects for each look direction
	map<EPlayerWalkDirection, CAnimation*> m_WalkAnimations; // map containing animations for all walk directions

	CSound* m_pBasicAttackSound = nullptr; // attack sound pointer
#pragma endregion

};