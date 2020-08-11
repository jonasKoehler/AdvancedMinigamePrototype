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

/// <summary>
/// player class
/// </summary>
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
	GPlayer(const char* _pFile, SVector2 _size, SVector2 _pos = SVector2()) : GEntity(_pFile, _size, _pos)
	{
		UpdateStats(GUpgradeManager::GetInstance()->GetPlayerStats());

		m_pHitzoneTexture = new CTexturedObject(_pFile, SVector2(), SVector2());
		m_pHitzoneTexture->SetRect(m_Hitzone);
		m_pHitzoneTexture->SetSrcRect(SRect(32, 32, 32, 160));

		SVector2 animationFrameSize = SVector2(GConfig::s_PlayerSrcWidth, GConfig::s_PlayerSrcHeight);
		SVector2 framePositionInTexture = SVector2(0, 0);
		m_pLookRight = new CAnimation(framePositionInTexture, animationFrameSize, 1, 4);
		m_pCurrentAnimation = m_pLookRight;

		framePositionInTexture.Y += animationFrameSize.Y; // next row of frames
		m_pLookUpwards = new CAnimation(framePositionInTexture, animationFrameSize, 1, 4);

		framePositionInTexture.Y += animationFrameSize.Y; // next row of frames
		m_pLookDownwards = new CAnimation(framePositionInTexture, animationFrameSize, 1, 4);

		framePositionInTexture.Y += animationFrameSize.Y; // next row of frames
		m_pLookUpRight = new CAnimation(framePositionInTexture, animationFrameSize, 1, 4);

		framePositionInTexture.Y += animationFrameSize.Y; // next row of frames
		m_pLookDownRight = new CAnimation(framePositionInTexture, animationFrameSize, 1, 4);

		framePositionInTexture.Y += animationFrameSize.Y; // next row of frames
		m_pAttack = new CAnimation(framePositionInTexture, animationFrameSize, 1 / (m_AttacksPerSecond * 1.5), 4, false);

		m_pBasicAttackSound = new CSound("Sound/Effects/spray.wav");

	}
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	virtual ~GPlayer()
	{
		delete m_pLookDownRight;
		delete m_pLookUpRight;
		delete m_pLookRight;
		delete m_pLookDownwards;
		delete m_pLookUpwards;
		delete m_pHitzoneTexture;
	}
#pragma endregion

#pragma region public override function
	/// <summary>
	/// update every frame
	/// </summary>
	/// <param name="_deltaSeconds">time since last frame</param>
	virtual void Update(float _deltaSeconds) override;

	/// <summary>
	/// render every frame
	/// </summary>
	virtual	void Render() override;

#pragma region private functions
private:
	void Rotate(); // by Jonas
	void Move(float _deltaSeconds); // by Jonas
	void BasicAttack();  // by Jonas
	void ReachExit(); // by Lukas
	void CheckIfDead() override; //by Lukas
	void UpdateStats(map<EUpgrades, float> _PlayerStats); // by Jonas
#pragma endregion


#pragma region private variables
private:
	int m_Angle = 0; // the angle between the cursor and player position
	SRect m_Hitzone = SRect(); // rect that determines if an enemy is in attack range
	float m_AttacksPerSecond = 1.5f; // the number of times the player can attack in a second
	float m_AttackCooldown = 1.0f; // one second attack cooldown	

	float m_AccelerationRate = 5.0f; // increases acceleration per sec (multiply with deltaTime)
	float m_DecelerationRate = 5.0f; // decreases acceleration per sec (multiply with deltaTime)

	CTexturedObject* m_pHitzoneTexture = nullptr;
	/*
	*	Animation Pointer
	*/
	CAnimation* m_pCurrentAnimation = nullptr;
	CAnimation* m_pLookUpwards = nullptr;
	CAnimation* m_pLookDownwards = nullptr;
	CAnimation* m_pLookRight = nullptr;
	CAnimation* m_pLookUpRight = nullptr;
	CAnimation* m_pLookDownRight = nullptr;
	CAnimation* m_pAttack = nullptr;
	/*
	*	Sound Pointer
	*/
	CSound* m_pBasicAttackSound = nullptr;
#pragma endregion

};