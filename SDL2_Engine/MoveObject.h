#pragma once

#pragma region system include
#include <list>
#pragma endregion

#pragma region project include
#include "TexturedObject.h"
#pragma endregion

#pragma region using
using namespace std;
#pragma endregion

/// <summary>
/// class that can automatically move and collide
/// </summary>
class CMoveObject : public CTexturedObject
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pFileName">texture relative file path</param>
	/// <param name="_size">size of texture</param>
	/// <param name="_pos">position of object</param>
	CMoveObject(const char* _pFileName, SVector2 _size, SVector2 _pos = SVector2()) : CTexturedObject(_pFileName, _size, _pos) 
	{
		SetLayer(5);
	}
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	virtual ~CMoveObject() {}
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
	virtual void Render() override;
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// activate gravity
	/// </summary>
	inline void ActivateGravity() { m_gravity = true; }

	/// <summary>
	/// deactivate gravity
	/// </summary>
	inline void DeactivateGravity() { m_gravity = false; }

	/// <summary>
	/// get speed
	/// </summary>
	/// <returns>speed in meter per second</returns>
	inline float GetSpeed() { return m_speed; }

	/// <summary>
	/// set speed
	/// </summary>
	/// <param name="_speed">speed in meter per second</param>
	inline void SetSpeed(float _speed) { m_speed = _speed; }

	/// <summary>
	/// get movement
	/// </summary>
	/// <returns>movement vertical and horizontal</returns>
	inline SVector2 GetMovement() { return m_movement; }

	/// <summary>
	/// set movement
	/// </summary>
	/// <param name="_movement">movement vertical and horizontal</param>
	inline void SetMovement(SVector2 _movement) { m_movement = _movement; }
#pragma endregion

#pragma region public function
	/// <summary>
	/// set collision objects in move range
	/// </summary>
	void SetColObjects();
#pragma endregion

protected:
#pragma region protected primitive variable
	/// <summary>
	/// gravity
	/// </summary>
	bool m_gravity = false;

	/// <summary>
	/// time in fall if gravity active
	/// </summary>
	float m_fallTime = 0.0f;

	/// <summary>
	/// speed in meter per second
	/// </summary>
	float m_speed = 0.0f;
#pragma endregion

#pragma region protected variable
	/// <summary>
	/// movement vertical and horizontal
	/// </summary>
	SVector2 m_movement = SVector2();
#pragma endregion

protected:
#pragma region protected variable
	/// <summary>
	/// list with all possible objects to collide with in range
	/// </summary>
	list<CTexturedObject*> m_colObject;
#pragma endregion

private:
#pragma region private function
	/// <summary>
	/// check collision with possible objects
	/// </summary>
	/// <param name="_nextRect">rect next frame</param>
	/// <returns>if collision with any object</returns>
	bool CheckCollision(SRect _nextRect);

#pragma endregion
};