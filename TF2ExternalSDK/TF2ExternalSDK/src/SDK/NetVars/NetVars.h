#pragma once
#include "../TF2/cdll_int.h"

class CNetVars
{
private:
	int GetOffset(RecvTable *pTable, const char *pszNetVar);

public:
	int GetNetVar(const char *pszClass, const char *pszNetVar);
};

inline CNetVars g_NetVars;

#define NETVAR(_name, type, table, name) type _name() \
{ \
	static int nOffset = g_NetVars.GetNetVar(table, name); \
	return g_Memory.RPM<type>(reinterpret_cast<DWORD>(this) + nOffset); \
}