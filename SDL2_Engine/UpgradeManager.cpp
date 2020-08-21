#include "UpgradeManager.h"

void GUpgradeManager::Init()
{
	m_UpgradePointCount = 0;

	for (int i = 0; i < (int)EUpgrades::MAX; i++)
	{
		m_UpgradeLevel[(EUpgrades)i] = 0;

		switch ((EUpgrades)i)
		{
		case EUpgrades::AttackSpeed:
			m_UpgradePrice[(EUpgrades)i] = 1;
			m_UpgradeMaxLevel[(EUpgrades)i] = 4;
			m_PlayerStats[(EUpgrades)i] = 2.0f; // attacks per sec
			break;
		case EUpgrades::Damage:
			m_UpgradePrice[(EUpgrades)i] = 1;
			m_UpgradeMaxLevel[(EUpgrades)i] = 4;
			m_PlayerStats[(EUpgrades)i] = 25.0f; // attack damage
			break;
		case EUpgrades::MovementSpeed:
			m_UpgradePrice[(EUpgrades)i] = 1;
			m_UpgradeMaxLevel[(EUpgrades)i] = 4;
			m_PlayerStats[(EUpgrades)i] = 200.0f; // speed in pixel per sec
			break;
		case EUpgrades::AttackRange:
			m_UpgradePrice[(EUpgrades)i] = 1;
			m_UpgradeMaxLevel[(EUpgrades)i] = 5;
			m_PlayerStats[(EUpgrades)i] = 50.0f; // range in pixel
			break;
		case EUpgrades::SpecialAttack:
			m_UpgradePrice[(EUpgrades)i] = 5;
			m_UpgradeMaxLevel[(EUpgrades)i] = 1;
			m_PlayerStats[(EUpgrades)i] = 0.0f; // laser locked
			break;
		default:
			break;
		}
	}

	m_pBuySound = new CSound("Sound/Effects/S_Upgrade.wav");
}

void GUpgradeManager::BuyUpgrade(EUpgrades _upgrade)
{
	// check if upgrade can be bought: must have sufficient upgrade points and not reach max level
	if (m_UpgradePrice[_upgrade] > m_UpgradePointCount || m_UpgradeLevel[_upgrade] == m_UpgradeMaxLevel[_upgrade])
		return;

	m_UpgradePointCount -= m_UpgradePrice[_upgrade]; // subtract price from count
	m_UpgradeLevel[_upgrade]++; // increase level of upgrade

	// changes per individual upgrade
	switch (_upgrade)
	{
	case EUpgrades::AttackSpeed:
		m_UpgradePrice[_upgrade] = m_UpgradeLevel[_upgrade] + 1;
		m_PlayerStats[_upgrade] *= 1.2f;
		break;
	case EUpgrades::Damage:
		m_UpgradePrice[_upgrade] = m_UpgradeLevel[_upgrade] + 1;
		m_PlayerStats[_upgrade] += 18.75f;
		break;
	case EUpgrades::MovementSpeed:
		m_PlayerStats[_upgrade] *= 1.05f;
		break;
	case EUpgrades::AttackRange:
		m_PlayerStats[_upgrade] += 4;
		break;
	default:
		break;
	}

	if (m_UpgradeLevel[_upgrade] == m_UpgradeMaxLevel[_upgrade]) // check if max level has been reached
	{
		m_UpgradePrice[_upgrade] = 0; // set price to 0 as additional indicator
	}

	m_pBuySound->Play();
}
