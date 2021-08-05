#include "NetVars.h"

int CNetVars::GetOffset(RecvTable *pTable, const char *pszNetVar)
{
	for (int n = 0; n < pTable->GetNumProps(); n++)
	{
		RecvProp *pProp = pTable->GetProp(n);

		if (!pProp)
			continue;

		if (std::string_view(pProp->GetVarName().c_str()).compare(pszNetVar) == 0)
			return pProp->GetOffset();

		if (auto pDataTable = pProp->GetDataTable())
		{
			if (auto nOffset = GetOffset(pDataTable, pszNetVar))
				return nOffset + pProp->GetOffset();
		}
	}

	return 0;
}

int CNetVars::GetNetVar(const char *pszClass, const char *pszNetVar)
{
	if (auto pClasses = reinterpret_cast<ClientClass *>(Offsets::dwGetAllClasses))
	{
		for (auto pCurrNode = pClasses; pCurrNode; pCurrNode = pCurrNode->GetNextClass())
		{
			if (std::string_view(pszClass).compare(pCurrNode->GetNetworkName().c_str()) == 0)
				return GetOffset(pCurrNode->GetTable(), pszNetVar);
		}
	}

	return 0;
}