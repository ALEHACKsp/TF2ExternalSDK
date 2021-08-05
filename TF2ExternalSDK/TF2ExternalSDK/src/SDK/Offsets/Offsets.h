#pragma once
#include "../../Utils/Memory/Memory.h"

namespace Offsets
{
	inline DWORD dwClient			= 0x0;
	inline DWORD dwEngine			= 0x0;
	inline DWORD dwLocalPlayer		= 0x0;
	inline DWORD dwEntityList		= 0x0;
	inline DWORD dwGetAllClasses	= 0x0;
	inline DWORD dwGlobalVars		= 0x0;
	inline DWORD dwSequenceNumber	= 0x0;
	inline DWORD dwInput			= 0x0;

	//dumped using https://github.com/ActualDragonTears/TF2-Offset-Dumper
	inline DWORD dwJump				= 0xC6C320; //TODO: sig
	inline DWORD dwAttack			= 0xC6C32C; //TODO: sig
	inline DWORD dwAttack2			= 0xC6C338; //TODO: sig
	inline DWORD dwViewAngles		= 0x469494; //TODO: sig

	inline void Initialize()
	{
		while (!dwClient)
			dwClient = reinterpret_cast<DWORD>(g_Memory.FindModule("client.dll").hModule);

		while (!dwEngine)
			dwEngine = reinterpret_cast<DWORD>(g_Memory.FindModule("engine.dll").hModule);

		while (!dwLocalPlayer)
		{
			if (auto dwAddress = g_Memory.FindPattern("client.dll", "8B 3D ? ? ? ? 8B F1 3B FE 75 07 5F 5E E9 ? ? ? ?"))
				dwLocalPlayer = g_Memory.RPM<DWORD>(dwAddress + 0x2);
		}

		while (!dwEntityList)
		{
			if (auto dwAddress = g_Memory.FindPattern("client.dll", "A1 ? ? ? ? A8 01 75 51 83 C8 01 C7 05 ? ? ? ? ? ? ? ? 68 ? ? ? ?"))
				dwEntityList = (g_Memory.RPM<DWORD>(dwAddress + 0x1)) + 0x18;
		}

		while (!dwGetAllClasses)
		{
			if (auto dwAddress = g_Memory.FindPattern("client.dll", "A1 ? ? ? ? A3 ? ? ? ? C7 05 ? ? ? ? ? ? ? ? C3"))
				dwGetAllClasses = g_Memory.RPM<DWORD>(g_Memory.RPM<DWORD>(dwAddress + 0x1));
		}

		while (!dwGlobalVars)
		{
			if (auto dwAddress = g_Memory.FindPattern("engine.dll", "A1 ? ? ? ? 8B 11 68"))
				dwGlobalVars = g_Memory.RPM<DWORD>(dwAddress + 0x8);
		}

		while (!dwSequenceNumber)
		{
			if (auto dwAddress = g_Memory.FindPattern("engine.dll", "A3 ? ? ? ? C7 05 ? ? ? ? ? ? ? ? 0F 85 ? ? ? ? 8B 0D ? ? ? ? 8B 01 8B 40 3C FF D0"))
				dwSequenceNumber = g_Memory.RPM<DWORD>(dwAddress + 0x1);
		}

		while (!dwInput)
		{
			if (auto dwAddress = g_Memory.FindPattern("client.dll", "8B 0D ? ? ? ? 56 8B 01 FF 50 24 8B 45 FC"))
				dwInput = g_Memory.RPM<DWORD>(dwAddress + 0x2);
		}

		printf("dwClient 0x%X\n", dwClient);
		printf("dwEngine 0x%X\n", dwEngine);
		printf("dwLocalPlayer 0x%X\n", dwLocalPlayer);
		printf("dwEntityList 0x%X\n", dwEntityList);
		printf("dwGetAllClasses 0x%X\n", dwGetAllClasses);
		printf("dwGlobalVars 0x%X\n", dwGlobalVars);
		printf("dwSequenceNumber 0x%X\n", dwSequenceNumber);
		printf("dwInput 0x%X\n", dwInput);
	}
}