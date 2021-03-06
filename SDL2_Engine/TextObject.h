#pragma once

#pragma region project include
#include "TexturedObject.h"
#include "Color.h"
#include "Texture.h"
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
	CTextObject() {}

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
	virtual ~CTextObject()
	{
		// delete texture
		delete m_pTexture;
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
	virtual void Render() override;
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// set text
	/// </summary>
	/// <param name="_pText">text to set</param>
	inline void SetText(const char* _pText)
	{
		// set and load text
		m_pText = _pText;
		Load();
	}

	/// <summary>
	/// set color
	/// </summary>
	/// <param name="_color">color to set</param>
	inline void SetColor(SColor _color)
	{
		// set color and load text
		m_color = _color;
		Load();
	}

	/// <summary>
	/// set font
	/// </summary>
	/// <param name="_pFont">font reference to set</param>
	inline void SetFont(CFont* _pFont)
	{
		// set font and load text
		m_pFont = _pFont;
		Load();
	}
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