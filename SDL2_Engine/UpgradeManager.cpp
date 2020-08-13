#include "UpgradeManager.h"

void GUpgradeManager::Init()
{
	for (int i = 0; i < (int)EUpgrades::MAX; i++)
	{
		m_UpgradeLevel[(EUpgrades)i] = 0;

		switch ((EUpgrades)i)
		{
		case EUpgrades::AttackSpeed:
			m_UpgradePrice[(EUpgrades)i] = 1;
			m_UpgradeMaxLevel[(EUpgrades)i] = 4;
			m_PlayerStats[(EUpgrades)i] = 1.5f; // attacks per sec
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
			m_PlayerStats[(EUpgrades)i] = 30.0f; // range in pixel
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
}

void GUpgradeManager::BuyUpgrade(EUpgrades _upgrade)
{
	// check if upgrade can be bought: must not have reached max level and must have sufficient upgrade points
	if (m_UpgradePrice[_upgrade] > m_UpgradePointCount || m_UpgradeLevel[_upgrade] == m_UpgradeMaxLevel[_upgrade])
		return;

	m_UpgradePointCount -= m_UpgradePrice[_upgrade]; // subtract price from count
	m_UpgradeLevel[_upgrade]++; // increase level of upgrade

	// changes per individual upgrade
	switch (_upgrade)
	{
	case EUpgrades::AttackSpeed:
		m_UpgradePrice[_upgrade] = m_UpgradeLevel[_upgrade] + 1;
		m_PlayerStats[_upgrade] *= 1.25f;
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
}
