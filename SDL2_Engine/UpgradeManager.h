#include "EUpgrades.h"
#include <map>

using namespace std;

#pragma once
class GUpgradeManager // by Jonas
{
public:
	GUpgradeManager() { Init(); }

	~GUpgradeManager() {}

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

	inline void SetUpgradePointCount(int _upgradepoint)
	{
		m_UpgradePointCount = _upgradepoint;
	}


	void BuyUpgrade(EUpgrades _upgrade);
#pragma endregion

#pragma region private variables
private:
	map<EUpgrades, float> m_PlayerStats;
	map<EUpgrades, int> m_UpgradePrice;
	map<EUpgrades, int> m_UpgradeLevel;
	map<EUpgrades, int> m_UpgradeMaxLevel;

	int m_UpgradePointCount = 50;
#pragma endregion

};

