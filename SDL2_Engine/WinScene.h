#pragma once

#pragma region engine include
#include "Scene.h"
#pragma endregion

	/// <summary>
	/// menu class
	/// </summary>
	class GWinScene : public CScene
	{
	public:
#pragma region constructor
		/// <summary>
		/// constructor
		/// </summary>
		GWinScene() : CScene() {}
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

