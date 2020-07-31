#pragma once

#pragma region engine include
#include "Scene.h"
#include "Music.h"
#pragma endregion

/// <summary>
/// main game scene class
/// </summary>
class GMainScene : public CScene
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	GMainScene() : CScene() {}
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
	CMusic* p_Music = nullptr;
};