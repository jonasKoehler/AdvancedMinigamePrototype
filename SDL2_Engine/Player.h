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
	GPlayer(const char* _pFile, SVector2 _size, SVector2 _pos = SVector2()) : CMoveObject(_pFile, _size, _pos)
	{
		SVector2 animationFrameSize = SVector2(64, 64);
		SVector2 framePositionInTexture = SVector2(0, 0);
		m_pMoveRight = new CAnimation(framePositionInTexture, animationFrameSize, 1, 4);
		m_pCurrentAnimation = m_pMoveRight;

		framePositionInTexture.Y += animationFrameSize.Y; // next row of frames
		m_pMoveUpwards = new CAnimation(framePositionInTexture, animationFrameSize, 1, 4);

		framePositionInTexture.Y += animationFrameSize.Y; // next row of frames
		m_pMoveUpRight = new CAnimation(framePositionInTexture, animationFrameSize, 1, 4);

		framePositionInTexture.Y += animationFrameSize.Y; // next row of frames
		m_pMoveDownRight = new CAnimation(framePositionInTexture, animationFrameSize, 1, 4);
	}
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	virtual ~GPlayer()
	{
		delete m_pMoveDownRight;
		delete m_pMoveUpRight;
		delete m_pMoveRight;
		delete m_pMoveDownwards;
		delete m_pMoveUpwards;
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
#pragma endregion


#pragma region private variables
private:
	int m_Angle = 0; // the angle between the cursor and player position
	SRect m_Hitzone = SRect(); // rect that determines if an enemy is in attack range
	SVector2 m_HitzonePosition = m_position; // pivot of the hitzone rect; rotates with the players view direction
	float m_AttacksPerSecond = 1.5f; // the number of times the player can attack in a second
	float m_AttackCooldown = 1.0f; // one second attack cooldown
	int m_AttackRange = 64; // attack range in pixels

	/*
	*	Animation Pointer
	*/
	CAnimation* m_pCurrentAnimation = nullptr;
	CAnimation* m_pMoveUpwards = nullptr;
	CAnimation* m_pMoveDownwards = nullptr;
	CAnimation* m_pMoveRight = nullptr;
	CAnimation* m_pMoveUpRight = nullptr;
	CAnimation* m_pMoveDownRight = nullptr;
#pragma endregion

};