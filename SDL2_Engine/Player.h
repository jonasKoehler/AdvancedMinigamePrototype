#pragma once

#pragma region engine include
#include "MoveObject.h"
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
	GPlayer(const char* _pFile, SVector2 _size, SVector2 _pos = SVector2()) : CMoveObject(_pFile, _size, _pos) {}
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	virtual ~GPlayer() {}
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

#pragma region private variables
private:
	SRect m_Hitzone = SRect(); // rect that determines if an enemy is in attack range
	SVector2 m_HitzonePosition = m_position; // pivot of the hitzone rect; rotates with the players view direction
#pragma endregion

};