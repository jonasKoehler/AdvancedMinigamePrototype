#pragma once

#pragma region engine include
#include "MoveObject.h"
#include "Animation.h"
#pragma endregion

/// <summary>
/// player class
/// </summary>
class GPlayer : public CMoveObject
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pFileName">texture relative file path</param>
	/// <param name="_size">size of texture</param>
	/// <param name="_pos">position of player</param>
	GPlayer(const char* _pFile, SVector2 _size, SVector2 _pos = SVector2()) : CMoveObject(_pFile, _size, _pos) // Jonas
	{
		m_Hitzone.w = m_AttackRange;
		m_Hitzone.h = m_AttackRange;

		SVector2 animationFrameSize = SVector2(32, 32);
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
#pragma endregion

#pragma region private functions
private:
	void Rotate();
	void Move();
	void BasicAttack();
#pragma endregion


#pragma region private variables
private:
	int m_Angle = 0; // the angle between the cursor and player position
	SRect m_Hitzone = SRect(); // rect that determines if an enemy is in attack range
	float m_AttacksPerSecond = 1.5f; // the number of times the player can attack in a second
	float m_AttackCooldown = 1.0f; // one second attack cooldown
	int m_AttackRange = 20; // attack range in pixels

	/*
	*	Animation Pointer
	*/
	CAnimation* m_pCurrentAnimation = nullptr;
	CAnimation* m_pLookUpwards = nullptr;
	CAnimation* m_pLookDownwards = nullptr;
	CAnimation* m_pLookRight = nullptr;
	CAnimation* m_pLookUpRight = nullptr;
	CAnimation* m_pLookDownRight = nullptr;
#pragma endregion

};