#pragma once
#include "../../Utils/Utils.h"
#include "../Offsets/Offsets.h"
#include "globalvars_base.h"

#undef GetProp

class RecvTable;

class RecvProp
{
public:
	std::string GetVarName() {
		char out[128] = { '\0' };
		g_Memory.RPMString(g_Memory.RPM<DWORD>(reinterpret_cast<DWORD>(this)), out, 128);
		return std::string(out);
	}

	int GetOffset() {
		return g_Memory.RPM<int>(reinterpret_cast<DWORD>(this) + 0x2C);
	}

	RecvTable *GetDataTable() {
		return g_Memory.RPM<RecvTable *>(reinterpret_cast<DWORD>(this) + 0x28);
	}
};

class RecvTable
{
public:
	std::string GetTableName() {
		char out[128] = { '\0' };
		g_Memory.RPMString(g_Memory.RPM<DWORD>(reinterpret_cast<DWORD>(this) + 0xC), out, 128);
		return std::string(out);
	}

	RecvProp *GetProp(int i) {
		return reinterpret_cast<RecvProp *>((g_Memory.RPM<DWORD>(reinterpret_cast<DWORD>(this)) + 0x3C * i));
	}

	int GetNumProps() {
		return g_Memory.RPM<int>(reinterpret_cast<DWORD>(this) + 0x4);
	}
};

class ClientClass
{
public:
	std::string GetNetworkName() {
		char out[128] = { '\0' };
		g_Memory.RPMString(g_Memory.RPM<DWORD>(reinterpret_cast<DWORD>(this) + 0x8), out, 128);
		return std::string(out);
	}

	RecvTable *GetTable() {
		return g_Memory.RPM<RecvTable *>(reinterpret_cast<DWORD>(this) + 0xC);
	}

	ClientClass *GetNextClass() {
		return g_Memory.RPM<ClientClass *>(reinterpret_cast<DWORD>(this) + 0x10);
	}
};

class CUserCmd
{
public:
	void *vtable;
	int	command_number;
	int	tick_count;
	Vec3 viewangles;
	float forwardmove;
	float sidemove;
	float upmove;
	int buttons;
	byte impulse;
	int weaponselect;
	int weaponsubtype;
	int random_seed;
	short mousedx;
	short mousedy;
	bool hasbeenpredicted;
};

class CClient
{
public:
	void SetAttack(int nState) {
		g_Memory.WPM<int>(Offsets::dwClient + Offsets::dwAttack, nState);
	}

	void SetJump(int nState) {
		g_Memory.WPM<int>(Offsets::dwClient + Offsets::dwJump, nState);
	}
};

namespace I { inline CClient Client; }

class CEngine
{
public:
	Vec3 GetViewAngles() {
		return g_Memory.RPM<Vec3>(Offsets::dwEngine + Offsets::dwViewAngles);
	}

	void SetViewAngles(const Vec3 &vAngles) {
		g_Memory.WPM<Vec3>(Offsets::dwEngine + Offsets::dwViewAngles, vAngles);
	}

	CGlobalVarsBase GetGlobalVars() {
		return g_Memory.RPM<CGlobalVarsBase>(Offsets::dwGlobalVars);
	}
};

namespace I { inline CEngine Engine; }