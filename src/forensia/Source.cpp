#include "common.h"


LPWSTR g_pwszExecutionMode = nullptr;

VOID PrintUsage()
{

	wprintf(
		L"\n    ______                           _      \n"
		"   / ____/___  ________  ____  _____(_)___ _\n"
		"  / /_  / __ \\/ ___/ _ \\/ __ \\/ ___/ / __ \\`/\n"
		" / __/ / /_/ / /  /  __/ / / (__  ) / /_/ / \n"
		"/_/    \\____/_/   \\___/_/ /_/____/_/\\__,_/  \n"
		"                                            \n"
		">>>>>> Anti Forensics Tool For Red Teamers\n"
		"\n   Usage: \n"
		"     Forensia.exe <option>\n"
		"  \t-S : Sysmon Unloader\n"
		"  \t-D : Gutmann Method File Shredder\n"
		"  \t-U : USNJrnl Disabler\n"
		"  \t-P : Prefetch Disabler\n"
		"  \t-L : Windows Log Eraser And Disabler\n"
		"  \t-T : Timestamps-User Assist Disabler\n"
		"  \t-A : Access Time Disabler\n"
		"  \t-E : Event Tracing Disabler -> EXPERIMENTAL, AVOID IT!\n"
		"  \t-M : Melt Me!\n"
		"  \n\n\t Example: Forensia.exe -A\n"
		"  \t Example: Forensia.exe -D File.txt\n"
		"\n"
	);
}

BOOL ParseArguments(int argc, wchar_t* argv[])
{

	g_pwszExecutionMode = argv[1];

	switch (g_pwszExecutionMode[1])
	{
	case 'S':
		{
		wprintf(L"Switching To Sysmon Unloader...\n");
		SysmonUnload();
		break;
		}
	case 'D':
		{
			size_t origsize = wcslen(argv[2]) + 1;
			size_t convertedChars = 0;
			const size_t newsize = origsize * 2;
			char* nstring = new char[newsize];
			wcstombs_s(&convertedChars, nstring, newsize, argv[2], _TRUNCATE);
			wprintf(L"Switching To Shredding Module...\n");
			CorruptFunc(argc, nstring);
			wprintf(L"Done Shredding The Given File.\n");
			break;
		}
	case 'U':
	{
		wprintf(L"Switching To USNJrnl Disabling Module...\n");
		system("fsutil.exe usn deletejournal /D C:" );
		break;
	}
	case 'E':
	{
		wprintf(L"Switching To Event Tracing Disabler Module...\n");
		disableETW();
		break;
	}
	case 'P':
	{
		wprintf(L"Switching To Prefetch Disabler...\n");
		RegFunc(1);
		wprintf(L"\nDone?\n");
		break;
	}
	case 'A':
	{
		wprintf(L"Switching To NTFS Last Access Time Disabler...\n");
		RegFunc(2);
		break;
	}
	case 'T':
	{
		wprintf(L"Switching To NTFS Last Access Time Disabler...\n");
		RegFunc(3);
		break;
	}
	case 'L':
	{
		wprintf(L"Switching To Windows Event Log Disabler...\n");
		RegFunc(4);
		break;
	}
	case 'M':
	{
		wprintf(L"Melting The Executable...Goodbye!\n");
		MeltFile();
		break;
	}
	default:
		PrintUsage();
		break;
	}

	return false;
}


int wmain(int argc, wchar_t* argv[])
{
	if (argc > 1)
	if (!ParseArguments(argc, argv))
		return 1;
	PrintUsage();
}