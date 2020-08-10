#pragma once
#include "Scene.h"

class GEndScene : public CScene
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	GEndScene() : CScene() {}
#pragma endregion


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
};


