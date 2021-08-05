#pragma once
#include "baseflex.h"

class CTFWeaponBase;

class CBaseCombatCharacter : public CBaseFlex
{
public:
	NETVAR(m_flNextAttack, float, "CBaseCombatCharacter", "m_flNextAttack");
	NETVAR(m_hActiveWeapon, EHANDLE, "CBaseCombatCharacter", "m_hActiveWeapon");
	//NETVAR(m_hMyWeapons, EHANDLE, "CBaseCombatCharacter", "m_hMyWeapons");
	NETVAR(m_bGlowEnabled, bool, "CBaseCombatCharacter", "m_bGlowEnabled");

	/*std::array<CHandle<CTFWeaponBase>, 48> &m_hMyWeapons() {
		static int nOffset = GetNetVar("CBaseCombatCharacter", "m_hMyWeapons");
		return *reinterpret_cast<std::array<CHandle<CTFWeaponBase>, 48>*>(reinterpret_cast<DWORD>(this) + nOffset);
	}*/
};