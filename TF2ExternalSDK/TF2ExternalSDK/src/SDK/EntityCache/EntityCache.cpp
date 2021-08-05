#include "EntityCache.h"

void CEntityCache::Fill()
{
	if (m_pLocal = I::EntityList.GetClientEntity(LOCAL_ADDRESS)->As<CTFPlayer>())
	{
		int nLocalTeam = 0;

		if (!m_pLocal->IsInValidTeam(&nLocalTeam))
			return;

		m_pWeapon = m_pLocal->m_hActiveWeapon().Get()->As<CTFWeaponBase>();

		for (int n = 1; n < I::EntityList.GetHighestEntityIndex(); n++)
		{
			if (auto pEntity = I::EntityList.GetClientEntity(n))
			{
				if (pEntity->IsDormant() || pEntity == m_pLocal)
					continue;

				switch (pEntity->GetClassId())
				{
					case EClassIds::CTFPlayer:
					{
						int nTeam = 0;

						if (!pEntity->IsInValidTeam(&nTeam))
							continue;

						m_mapGroups[EEntGroup::PLAYERS_ALL].push_back(pEntity);
						m_mapGroups[nTeam != nLocalTeam ? EEntGroup::PLAYERS_ENEMIES : EEntGroup::PLAYERS_TEAMMATES].push_back(pEntity);

						break;
					}

					case EClassIds::CObjectSentrygun:
					case EClassIds::CObjectDispenser:
					case EClassIds::CObjectTeleporter:
					{
						int nTeam = 0;

						if (!pEntity->IsInValidTeam(&nTeam))
							continue;

						m_mapGroups[EEntGroup::BUILDINGS_ALL].push_back(pEntity);
						m_mapGroups[nTeam != nLocalTeam ? EEntGroup::BUILDINGS_ENEMIES : EEntGroup::BUILDINGS_TEAMMATES].push_back(pEntity);

						break;
					}

					default: continue;
				}
			}
		}
	}
}

void CEntityCache::Clear()
{
	m_pLocal = nullptr;
	m_pWeapon = nullptr;

	for (auto &Group : m_mapGroups)
		Group.second.clear();
}

const std::vector<CBaseEntity *> &CEntityCache::GetGroup(EEntGroup Group) {
	return m_mapGroups[Group];
}

CTFPlayer *CEntityCache::GetLocal() {
	return m_pLocal;
}

CTFWeaponBase *CEntityCache::GetWeapon() {
	return m_pWeapon;
}