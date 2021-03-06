#pragma once

#pragma region engine include
#include "Scene.h"
#include "Music.h"
#pragma endregion

class GUpgradeFrame;
class GPlayer;

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

#pragma region private variables
private:
	CMusic* m_pMusic = nullptr;
	CCanvas m_UpgradeMenu = CCanvas();
	bool m_UpgradeMenuVisibility = false;

	// pointers that are in CTM
	GPlayer* m_pPlayer = nullptr;
	GUpgradeFrame* m_pAttackSpeedUpgrade = nullptr;
	GUpgradeFrame* m_pDamageUpgrade = nullptr;
	GUpgradeFrame* m_pSpeedUpgrade = nullptr;
	GUpgradeFrame* m_pLaserUpgrade = nullptr;
	GUpgradeFrame* m_pRangeUpgrade = nullptr;
#pragma endregion
};