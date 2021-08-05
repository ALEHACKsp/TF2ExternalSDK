#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>
#include <string>

#define INRANGE(x,a,b) (x >= a && x <= b) 
#define GetBits(x) (INRANGE((x & (~0x20)),'A','F') ? ((x & (~0x20)) - 'A' + 0xA) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define GetBytes(x) (GetBits(x[0]) << 4 | GetBits(x[1]))

class CMemory
{
private:
	DWORD m_dwProcessId = 0x0;
	HANDLE m_hProcess = 0;

public:
	DWORD FindProcessId(const char *pszProcessName)
	{
		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0x0);

		PROCESSENTRY32 ProcEntry = {};
		ProcEntry.dwSize = sizeof(PROCESSENTRY32);

		for (Process32First(hSnapshot, &ProcEntry); Process32Next(hSnapshot, &ProcEntry);)
		{
			if (!strcmp(ProcEntry.szExeFile, pszProcessName))
			{
				CloseHandle(hSnapshot);
				return ProcEntry.th32ProcessID;
			}
		}

		CloseHandle(hSnapshot);
		return 0x0;
	}

	MODULEENTRY32 FindModule(const char *pszModuleName)
	{
		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, m_dwProcessId);

		MODULEENTRY32 ModEntry = {};
		ModEntry.dwSize = sizeof(MODULEENTRY32);

		for (Module32First(hSnapshot, &ModEntry); Module32Next(hSnapshot, &ModEntry);)
		{
			if (!strcmp(ModEntry.szModule, pszModuleName))
			{
				CloseHandle(hSnapshot);
				return ModEntry;
			}
		}

		CloseHandle(hSnapshot);
		return {};
	}

	//written by a pleb in 2019
	DWORD FindPattern(const char *pszModuleName, const char *pszPattern)
	{
		auto Module = FindModule(pszModuleName);

		if (!Module.hModule)
			return 0x0;

		const size_t nSignatureSize = strlen(pszPattern);
		const size_t nReadSize = Module.modBaseSize;

		std::vector<unsigned char> vecChunk = {};
		vecChunk.resize(nReadSize);

		for (size_t i = DWORD(Module.modBaseAddr); i < DWORD(Module.modBaseAddr) + Module.modBaseSize; i += nReadSize - nSignatureSize)
		{
			ReadProcessMemory(m_hProcess, LPCVOID(i), vecChunk.data(), nReadSize, nullptr);

			const char *pszPat = pszPattern;
			DWORD dwFirstMatch = 0x0;

			for (size_t a = 0; a < nReadSize; a++)
			{
				if (*(PBYTE)pszPat == '\?' || *(PBYTE)(vecChunk.data() + a) == GetBytes(pszPat))
				{
					if (!dwFirstMatch)
						dwFirstMatch = i + a;

					if (!pszPat[2])
						return dwFirstMatch;

					if (*(PWORD)pszPat == '\?\?' || *(PBYTE)pszPat != '\?')
						pszPat += 3;

					else pszPat += 2;
				}

				else
				{
					pszPat = pszPattern;
					dwFirstMatch = 0;
				}
			}
		}

		return 0x0;
	}

	template <typename T> T RPM(const DWORD &dwAddress)
	{
		T Out = {};
		ReadProcessMemory(m_hProcess, reinterpret_cast<PVOID>(dwAddress), &Out, sizeof(T), nullptr);
		return Out;
	}

	template <typename T> void WPM(const DWORD &dwAddress, const T &Buffer)
	{
		WriteProcessMemory(m_hProcess, reinterpret_cast<PVOID>(dwAddress), &Buffer, sizeof(T), nullptr);
	}

	void RPMString(const DWORD &dwAddress, char Buffer[], size_t nLength)
	{
		ReadProcessMemory(m_hProcess, reinterpret_cast<PVOID>(dwAddress), Buffer, nLength, nullptr);
	}

public:
	void Initialize(const char *pszProcessName)
	{
		while (!m_hProcess)
		{
			if (m_dwProcessId = FindProcessId(pszProcessName))
				m_hProcess = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE, FALSE, m_dwProcessId);
		}
	}

	void Free()
	{
		m_dwProcessId = 0x0;
		CloseHandle(m_hProcess);
	}

	~CMemory()
	{
		m_dwProcessId = 0x0;
		CloseHandle(m_hProcess);
	}
};

inline CMemory g_Memory;