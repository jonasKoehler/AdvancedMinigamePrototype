#pragma once

#pragma region project include
#include "Vector2.h"
#include "ContentManagement.h"
#pragma endregion

/// <summary>
/// base object class
/// </summary>
class CObject
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	CObject() {}


#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	virtual ~CObject() {}
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// get tag
	/// </summary>
	/// <returns>tag of object</returns>
	inline const char* GetTag() { return m_pTag; }

	/// <summary>
	/// set tag
	/// </summary>
	/// <param name="_pTag">tag to set</param>
	inline void SetTag(const char* _pTag) { m_pTag = _pTag; }

	/// <summary>
	/// get layer
	/// </summary>
	/// <returns>rendering layer</returns>
	inline int GetLayer() { return m_layer; }

	/// <summary>
	/// set rendering layer
	/// </summary>
	/// <param name="_layer">layer to set</param>
	inline void SetLayer(int _layer) 
	{
		// set layer and sort object
		m_layer = _layer;
		CTM->SortObjects(this);
	}

	/// <summary>
	/// get position
	/// </summary>
	/// <returns>position of object</returns>
	inline SVector2 GetPosition() { return m_position; }

	/// <summary>
	/// set position
	/// </summary>
	/// <param name="_pos">position to set</param>
	inline void SetPosition(SVector2 _pos) { m_position = _pos; }

	/// <summary>
	/// add position
	/// </summary>
	/// <param name="_pos">position to add to object</param>
	inline void AddPosition(SVector2 _pos) { m_position += _pos; }


	inline bool GetRenderingIndicator() { return m_render; }
#pragma endregion

#pragma region public virtual function
	/// <summary>
	/// update every frame
	/// </summary>
	/// <param name="_deltaSeconds">time since last frame</param>
	virtual void Update(float _deltaSeconds) = 0;

	/// <summary>
	/// render every frame
	/// </summary>
	virtual void Render() = 0;

	virtual void OnCollisionEnter(CObject* pObject) {};

	inline virtual void SetRenderingIndicator(bool _render) { m_render = _render; }
#pragma endregion

protected:
#pragma region protected primitive variable
	/// <summary>
	/// tag of object
	/// </summary>
	const char* m_pTag = "";

	/// <summary>
	/// rendering layer
	/// higher values are closer to the camera
	/// </summary>
	int m_layer = 0;

	/// <summary>
	/// bool that determines if the object should be rendered
	/// </summary>
	bool m_render = true;
#pragma endregion

#pragma region protected variable
	/// <summary>
	/// position of object
	/// </summary>
	
	SVector2 m_position = SVector2();
#pragma endregion
};