#pragma once
#pragma region engine include
#include "Scene.h"
#include "Canvas.h"
#include "Music.h"
#pragma endregion

class CTexturedObject;
/// <summary>
/// menu class
/// </summary>
class GMenuScene : public CScene
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	GMenuScene() : CScene() {}
#pragma endregion

#pragma region pulic override function
	/// <summary>
	/// initialize scene
	/// </summary>
	virtual void Init() override;

	/// <summary>
	/// update every frame
	/// </summary>
	/// <param name="_deltaSeconds">time since last frame</param>
	virtual void Update(float _deltaSeconds) override;

	/// <summary>
	/// render every frame
	/// </summary>
	virtual void Render() override;

	/// <summary>
	/// clean up scene
	/// </summary>
	virtual void Clean() override;
#pragma endregion

#pragma region private member variables
	CTexturedObject* m_pTutorialImage = nullptr;
	CMusic* m_pMenuTheme = nullptr;
	CCanvas m_ButtonCanvas;
#pragma endregion

};