#pragma once
#include "../TF2/tf_player.h"

enum struct EEntGroup
{
	PLAYERS_ALL, PLAYERS_ENEMIES, PLAYERS_TEAMMATES,
	BUILDINGS_ALL, BUILDINGS_ENEMIES, BUILDINGS_TEAMMATES
};

class CEntityCache
{
private:
	std::map<EEntGroup, std::vector<CBaseEntity *>> m_mapGroups = {};

private:
	CTFPlayer *m_pLocal = nullptr;
	CTFWeaponBase *m_pWeapon = nullptr;

public:
	void Fill();
	void Clear();

	const std::vector<CBaseEntity *> &GetGroup(EEntGroup Group);

	CTFPlayer *GetLocal();
	CTFWeaponBase *GetWeapon();
};

inline CEntityCache g_EntityCache;