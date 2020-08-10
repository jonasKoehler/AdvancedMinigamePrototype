#include "PlayerStats.h"

#pragma once
class GUpgradeManager
{
	GUpgradeManager() { Init(); }

	~GUpgradeManager(){}

#pragma region static singleton reference
	inline static GUpgradeManager* GetInstance() 
	{
		static GUpgradeManager* pUpgradeManager = new GUpgradeManager();
		return pUpgradeManager;
	}
#pragma endregion

private:
	void Init();

#pragma region public functions
public:

#pragma endregion

private:
	GPlayerStats m_PlayerStats = GPlayerStats();
};

