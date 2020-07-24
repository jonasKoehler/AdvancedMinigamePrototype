#pragma once

#pragma region project include
#include "TexturedObject.h"
#pragma endregion

/// <summary>
/// mouse class
/// </summary>
class CMouse : public CTexturedObject
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	CMouse() {}

	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pFileName">texture relative file path</param>
	/// <param name="_size">size of texture</param>
	/// <param name="_pos">position of object</param>
	CMouse(const char* _pFileName, SVector2 _size, SVector2 _pos = SVector2()) : CTexturedObject(_pFileName, _size, _pos) {}
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	virtual ~CMouse() {}
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
	/// set center of mouse position in texture
	/// </summary>
	/// <param name="_center">center of mouse position in texture</param>
	inline void SetCenter(SVector2 _center) { m_center = _center; }
#pragma endregion

protected:
#pragma region protected variable
	/// <summary>
	/// center of mouse position in texture
	/// </summary>
	SVector2 m_center = SVector2();
#pragma endregion
};