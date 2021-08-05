#include "SDK/SDK.h"

int main()
{
	SetConsoleTitleA("TF2ExternalSDK");

	g_Memory.Initialize("hl2.exe");

	Offsets::Initialize();

	while (!(GetAsyncKeyState(VK_END) & 0x8000))
	{
		G::GlobalVars = I::Engine.GetGlobalVars();

		g_EntityCache.Fill();

		//some examples:

		//bhop
		if (auto pLocal = g_EntityCache.GetLocal())
		{
			if (GetAsyncKeyState(VK_SPACE) & 0x8000)
				g_Memory.WPM<int>(Offsets::dwClient + Offsets::dwJump, pLocal->m_fFlags() & 1 | 4);
		}

		//glow
		for (auto pEntity : g_EntityCache.GetGroup(EEntGroup::PLAYERS_ENEMIES))
		{
			if (pEntity) //"nullptrs" filltered by cache (dormants too) but still gotta check!
				g_Memory.WPM<std::pair<bool, bool>>(reinterpret_cast<DWORD>(pEntity) + 0xDBD, { true, false });
		}

		//aiming
		if (auto pLocal = g_EntityCache.GetLocal())
		{
			if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
				I::Engine.SetViewAngles(Math::CalcAngle(pLocal->GetShootPos(), { 0.0f, 0.0f, 0.0f }));
		}

		//thirdperson
		if (auto pLocal = g_EntityCache.GetLocal())
		{
			static int nOffset = g_NetVars.GetNetVar("CTFPlayer", "m_nForceTauntCam");

			if (nOffset)
			{
				static bool bToggle = false;

				if (GetAsyncKeyState(static_cast<int>('R')) & 1)
					g_Memory.WPM<int>(reinterpret_cast<DWORD>(pLocal) + nOffset, bToggle = !bToggle ? 1 : 0);
			}
		}

		g_EntityCache.Clear();

		Sleep(0x1);
	}

	g_Memory.Free();

	return 0;
}