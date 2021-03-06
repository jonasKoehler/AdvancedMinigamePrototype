#pragma once

/// <summary>
/// base scene class
/// </summary>
class CScene
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	CScene() {}
#pragma endregion

#pragma region public function
	/// <summary>
	/// initialize scene
	/// </summary>
	virtual void Init() = 0;

	/// <summary>
	/// update every frame
	/// </summary>
	/// <param name="_deltaSeconds">time since last frame</param>
	virtual void Update(float _deltaSeconds) = 0;

	/// <summary>
	/// render every frame
	/// </summary>
	virtual void Render() = 0;

	/// <summary>
	/// clean up scene
	/// </summary>
	virtual void Clean() = 0;
#pragma endregion
};