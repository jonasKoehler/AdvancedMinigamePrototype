#pragma once

#pragma region project include
#include "TexturedObject.h"
#include "Color.h"
#pragma endregion

#pragma region forward decleration
class CFont;
#pragma endregion

/// <summary>
/// class for text objects
/// </summary>
class CTextObject : public CTexturedObject
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pText">text</param>
	/// <param name="_pFont">font reference</param>
	/// <param name="_size">size of rect</param>
	/// <param name="_pos">position on screen</param>
	/// <param name="_color">color</param>
	CTextObject(const char* _pText, CFont* _pFont, SVector2 _size, SVector2 _pos, SColor _color);
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	virtual ~CTextObject() {}
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

protected:
#pragma region protected primitive variable
	/// <summary>
	/// text to show
	/// </summary>
	const char* m_pText = "";
#pragma endregion

#pragma region protected variable
	/// <summary>
	/// color
	/// </summary>
	SColor m_color = SColor();
#pragma endregion

#pragma region protected pointer
	/// <summary>
	/// font reference
	/// </summary>
	CFont* m_pFont = nullptr;
#pragma endregion

private:
#pragma region private function
	/// <summary>
	/// load text
	/// </summary>
	void Load();
#pragma endregion
};