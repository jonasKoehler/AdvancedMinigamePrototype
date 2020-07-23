#pragma once

#pragma region project include
#include "Object.h"
#include "Rect.h"
#include "Enums.h"
#pragma endregion

#pragma region forward decleration
class CTexture;
#pragma endregion

/// <summary>
/// class for objects with texture and rect
/// </summary>
class CTexturedObject : public CObject
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	CTexturedObject() {}

	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pFileName">texture relative file path</param>
	/// <param name="_size">size of texture</param>
	/// <param name="_pos">position of object</param>
	CTexturedObject(const char* _pFileName, SVector2 _size, SVector2 _pos = SVector2());
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	virtual ~CTexturedObject();
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
	/// if object is rendered in world
	/// </summary>
	/// <returns>object is rendered in world space</returns>
	inline bool GetInWorld() { return m_inWorld; }

	/// <summary>
	/// set object is rendered in world
	/// </summary>
	/// <param name="_inWorld">object is rendered in world space</param>
	inline void SetInWorld(bool _inWorld) { m_inWorld = _inWorld; }

	/// <summary>
	/// get angle
	/// </summary>
	/// <returns>angle of texture</returns>
	inline float GetAngle() { return m_angle; }

	/// <summary>
	/// set angle of texture
	/// </summary>
	/// <param name="_angle">angle to set</param>
	inline void SetAngle(float _angle) { m_angle = _angle; }

	/// <summary>
	/// get collision type
	/// </summary>
	/// <returns>collision type</returns>
	inline ECollisionType GetColType() { return m_colType; }

	/// <summary>
	/// set collision type
	/// </summary>
	/// <param name="_colType">collision type to set</param>
	inline void SetColType(ECollisionType _colType) { m_colType = _colType; }

	/// <summary>
	/// get mirror
	/// </summary>
	/// <returns>mirror (x is true = horizontal and y is true = vertical)</returns>
	inline SVector2 GetMirror() { return m_mirror; }

	/// <summary>
	/// set mirror
	/// </summary>
	/// <param name="_mirror">mirror (x is true = horizontal and y is true = vertical)</param>
	inline void SetMirror(SVector2 _mirror) { m_mirror = _mirror; }

	/// <summary>
	/// get rect
	/// </summary>
	/// <returns>rect of texture</returns>
	inline SRect GetRect() { return m_rect; }

	/// <summary>
	/// set rect of texture
	/// </summary>
	/// <param name="_rect">rect to set</param>
	inline void SetRect(SRect _rect) { m_rect = _rect; }

	/// <summary>
	/// get source rect
	/// </summary>
	/// <returns>source rect of texture</returns>
	inline SRect GetSrcRect() { return m_srcRect; }

	/// <summary>
	/// set source rect of texture
	/// </summary>
	/// <param name="_rect">source rect to set</param>
	inline void SetSrcRect(SRect _rect) { m_srcRect = _rect; }

	/// <summary>
	/// set texture
	/// </summary>
	/// <param name="_pTexture">texture reference to set</param>
	inline void SetTexture(CTexture* _pTexture) { m_pTexture = _pTexture; };
#pragma endregion

protected:
#pragma region protected primitive variable
	/// <summary>
	/// if object is rendered in world space
	/// </summary>
	bool m_inWorld = true;

	/// <summary>
	/// angle of texture
	/// </summary>
	float m_angle = 0.0f;
#pragma endregion

#pragma region protected variable
	/// <summary>
	/// collision type
	/// </summary>
	ECollisionType m_colType = ECollisionType::NONE;

	/// <summary>
	/// mirror (x is true = horizontal and y is true = vertical)
	/// </summary>
	SVector2 m_mirror = SVector2();

	/// <summary>
	/// rect of texture
	/// </summary>
	SRect m_rect = SRect();

	/// <summary>
	/// source rect of texture
	/// </summary>
	SRect m_srcRect = SRect();
#pragma endregion

#pragma region protected pointer
	/// <summary>
	/// texture
	/// </summary>
	CTexture* m_pTexture = nullptr;
#pragma endregion
};