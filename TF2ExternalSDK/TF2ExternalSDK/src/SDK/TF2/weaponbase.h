#pragma once
#include "basecombatweapon.h"

class CTFWeaponBase : public CBaseCombatWeapon
{
public:
	NETVAR(m_bLowered, bool, "CTFWeaponBase", "m_bLowered");
	NETVAR(m_iReloadMode, int, "CTFWeaponBase", "m_iReloadMode");
	NETVAR(m_bResetParity, bool, "CTFWeaponBase", "m_bResetParity");
	NETVAR(m_bReloadedThroughAnimEvent, bool, "CTFWeaponBase", "m_bReloadedThroughAnimEvent");
	NETVAR(m_bDisguiseWeapon, bool, "CTFWeaponBase", "m_bDisguiseWeapon");
	NETVAR(m_flLastCritCheckTime, float, "CTFWeaponBase", "m_flLastCritCheckTime");
	NETVAR(m_flReloadPriorNextFire, float, "CTFWeaponBase", "m_flReloadPriorNextFire");
	NETVAR(m_flLastFireTime, float, "CTFWeaponBase", "m_flLastFireTime");
	NETVAR(m_flEffectBarRegenTime, float, "CTFWeaponBase", "m_flEffectBarRegenTime");
	NETVAR(m_flObservedCritChance, float, "CTFWeaponBase", "m_flObservedCritChance");
	NETVAR(m_flEnergy, float, "CTFWeaponBase", "m_flEnergy");
	NETVAR(m_hExtraWearable, EHANDLE, "CTFWeaponBase", "m_hExtraWearable");
	NETVAR(m_hExtraWearableViewModel, EHANDLE, "CTFWeaponBase", "m_hExtraWearableViewModel");
	NETVAR(m_bBeingRepurposedForTaunt, bool, "CTFWeaponBase", "m_bBeingRepurposedForTaunt");
	NETVAR(m_nKillComboClass, int, "CTFWeaponBase", "m_nKillComboClass");
	NETVAR(m_nKillComboCount, int, "CTFWeaponBase", "m_nKillComboCount");
	NETVAR(m_flInspectAnimEndTime, float, "CTFWeaponBase", "m_flInspectAnimEndTime");
	NETVAR(m_nInspectStage, int, "CTFWeaponBase", "m_nInspectStage");
	NETVAR(m_iConsecutiveShots, int, "CTFWeaponBase", "m_iConsecutiveShots");
	NETVAR(m_iItemDefinitionIndex, int, "CEconEntity", "m_iItemDefinitionIndex");
};

class CTFKnife : public CTFWeaponBase
{
public:
	NETVAR(m_bReadyToBackstab, bool, "CTFKnife", "m_bReadyToBackstab");
	NETVAR(m_bKnifeExists, bool, "CTFKnife", "m_bKnifeExists");
	NETVAR(m_flKnifeRegenerateDuration, float, "CTFKnife", "m_flKnifeRegenerateDuration");
	NETVAR(m_flKnifeMeltTimestamp, float, "CTFKnife", "m_flKnifeMeltTimestamp");
};

class CTFMinigun : public CTFWeaponBase
{
public:
	NETVAR(m_iWeaponState, int, "CTFMinigun", "m_iWeaponState");
	NETVAR(m_bCritShot, bool, "CTFMinigun", "m_bCritShot");
};

class CWeaponMedigun : public CTFWeaponBase
{
public:
	NETVAR(m_hHealingTarget, EHANDLE, "CWeaponMedigun", "m_hHealingTarget");
	NETVAR(m_bHealing, bool, "CWeaponMedigun", "m_bHealing");
	NETVAR(m_bAttacking, bool, "CWeaponMedigun", "m_bAttacking");
	NETVAR(m_bChargeRelease, bool, "CWeaponMedigun", "m_bChargeRelease");
	NETVAR(m_bHolstered, bool, "CWeaponMedigun", "m_bHolstered");
	NETVAR(m_nChargeResistType, int, "CWeaponMedigun", "m_nChargeResistType");
	NETVAR(m_hLastHealingTarget, EHANDLE, "CWeaponMedigun", "m_hLastHealingTarget");
	NETVAR(m_flChargeLevel, float, "CWeaponMedigun", "m_flChargeLevel");
};

class CTFPipebombLauncher : public CTFWeaponBase
{
public:
	NETVAR(m_iPipebombCount, int, "CTFPipebombLauncher", "m_iPipebombCount");
	NETVAR(m_flChargeBeginTime, float, "CTFPipebombLauncher", "m_flChargeBeginTime");
};

class CTFSniperRifle : public CTFWeaponBase
{
public:
	NETVAR(m_flChargedDamage, float, "CTFSniperRifle", "m_flChargedDamage");
};

class CTFGrenadeLauncher : public CTFWeaponBase
{
public:
	NETVAR(m_flDetonateTime, float, "CTFGrenadeLauncher", "m_flDetonateTime");
	NETVAR(m_iCurrentTube, int, "CTFGrenadeLauncher", "m_iCurrentTube");
	NETVAR(m_iGoalTube, int, "CTFGrenadeLauncher", "m_iGoalTube");
};