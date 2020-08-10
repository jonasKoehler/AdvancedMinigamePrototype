#pragma once
class GUpgradeManager
{
	GUpgradeManager(){}

	~GUpgradeManager(){}

#pragma region static singleton reference
	inline static GUpgradeManager* GetInstance() 
	{
		static GUpgradeManager* pUpgradeManager = new GUpgradeManager();
		return pUpgradeManager;
	}
#pragma endregion


#pragma region public functions

#pragma endregion

};

