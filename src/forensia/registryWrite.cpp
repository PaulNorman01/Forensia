


#include "common.h"
#include "regedit.h"



using std::wstring;

using winreg::RegKey;



bool RegFunc(int option)
{
    try {
        switch(option) {
            case 1:
            {
                const wstring testSubKey = L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Memory Management\\PrefetchParameters";     
                const DWORD testDw = 0x0000000;
                RegKey key{ HKEY_LOCAL_MACHINE, testSubKey };
                key.Open(HKEY_LOCAL_MACHINE, testSubKey);
                key.SetDwordValue(L"EnableSuperfetch", testDw);
                key.SetDwordValue(L"EnablePrefetcher", testDw);
                key.Close();
                break;
            }
            case 2:
            { //80000002
                const wstring testSubKey = L"SYSTEM\\CurrentControlSet\\Control\\FileSystem";
                const DWORD testDw = 0x0000001;
                RegKey key{ HKEY_LOCAL_MACHINE, testSubKey };
                key.Open(HKEY_LOCAL_MACHINE, testSubKey);
                key.SetDwordValue(L"NtfsDisableLastAccessUpdate", testDw);
                key.Close();
                break;
            }
            case 3:
            {
                const wstring testSubKey = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced";
                const DWORD testDw = 0x0000000;
                RegKey key{ HKEY_CURRENT_USER, testSubKey };
                key.Open(HKEY_CURRENT_USER, testSubKey);
                key.SetDwordValue(L"Start_TrackDocs", testDw);
                key.SetDwordValue(L"Start_TrackProgs", testDw);
                key.SetDwordValue(L"Start_TrackEnabled", testDw);
                key.Close();
                break;
            }
            case 4:
            {
                const wstring testSubKey = L"SYSTEM\\CurrentControlSet\\Services\\EventLog";
                const DWORD testDw = 0x0000004;
                RegKey key{ HKEY_LOCAL_MACHINE, testSubKey };
                key.Open(HKEY_LOCAL_MACHINE, testSubKey);
                key.SetDwordValue(L"Start", testDw);
                key.Close();
                system("for /F \"tokens=*\" %1 in (\'wevtutil.exe el\') DO wevtutil.exe cl \"%1\"");
                break;
            }
        }
    }

    catch (const std::exception&) 
    {
        wprintf(L"\nAn Error Occured.");
        return false;
    }

    return true;
}
