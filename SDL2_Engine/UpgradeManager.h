#include "EUpgrades.h"
#include "Sound.h"
#include <map>

using namespace std;

#pragma once
class GUpgradeManager // by Jonas
{
public:
	GUpgradeManager() { Init(); }

	~GUpgradeManager() 
	{
		delete m_pBuySound;
	}

#pragma region static singleton reference
public:
	inline static GUpgradeManager* GetInstance()
	{
		static GUpgradeManager* pUpgradeManager = new GUpgradeManager();
		return pUpgradeManager;
	}
#pragma endregion

private:
	// initialices the Upgrademanager and sets up the maps
	void Init();

#pragma region public functions
public:
	// returns the map containing the player stats
	inline map<EUpgrades, float> GetPlayerStats() { return m_PlayerStats; }

	// returns the price in Upgrade points for a given upgrade
	inline int GetUpgradePrice(EUpgrades _upgrade) { return m_UpgradePrice[_upgrade]; }

	// returns the level of a given upgrade type
	inline int GetUpgradeLevel(EUpgrades _upgrade) { return m_UpgradeLevel[_upgrade]; }

	// returns the max level of a given upgrade type
	inline int GetUpgradeMaxLevel(EUpgrades _upgrade) { return m_UpgradeMaxLevel[_upgrade]; }

	// return the number of collected upgrade points
	inline int GetUpgradePointCount() { return m_UpgradePointCount; }

	// add one upgradepoint to the UP count
	inline void AddUpgradePoint() { m_UpgradePointCount++; }

	// resets the UGM
	inline void Reset() { Init(); }

	/// <summary>
	/// attempts the purchase of the specified upgrade type
	/// </summary>
	/// <param name="_upgrade">Upgrade Type</param>
	void BuyUpgrade(EUpgrades _upgrade);
#pragma endregion

#pragma region private variables
private:
	map<EUpgrades, float> m_PlayerStats;
	map<EUpgrades, int> m_UpgradePrice;
	map<EUpgrades, int> m_UpgradeLevel;
	map<EUpgrades, int> m_UpgradeMaxLevel;

	int m_UpgradePointCount = 0;
	CSound* m_pBuySound = nullptr;
#pragma endregion

};

