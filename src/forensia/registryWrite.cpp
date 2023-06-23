//TAKEN FROM https://github.com/GiovanniDicanio/WinReg


#include "common.h"
#include "regedit.h"
#include "strsafe.h"


using std::wstring;

using std::vector;

using winreg::RegKey;




BOOL RegDelnodeRecurse(HKEY hKeyRoot, LPTSTR lpSubKey)
{
    LPTSTR lpEnd;
    LONG lResult;
    DWORD dwSize;
    TCHAR szName[MAX_PATH];
    HKEY hKey;
    FILETIME ftWrite;

    // First, see if we can delete the key without having
    // to recurse.

    lResult = RegDeleteKey(hKeyRoot, lpSubKey);

    if (lResult == ERROR_SUCCESS)
        return TRUE;

    lResult = RegOpenKeyEx(hKeyRoot, lpSubKey, 0, KEY_READ, &hKey);

    if (lResult != ERROR_SUCCESS)
    {
        if (lResult == ERROR_FILE_NOT_FOUND) {
            printf("Key not found.\n");
            return TRUE;
        }
        else {
            printf("Error opening key.\n");
            return FALSE;
        }
    }

    // Check for an ending slash and add one if it is missing.

    lpEnd = lpSubKey + lstrlen(lpSubKey);

    if (*(lpEnd - 1) != TEXT('\\'))
    {
        *lpEnd = TEXT('\\');
        lpEnd++;
        *lpEnd = TEXT('\0');
    }

    // Enumerate the keys

    dwSize = MAX_PATH;
    lResult = RegEnumKeyEx(hKey, 0, szName, &dwSize, NULL,
        NULL, NULL, &ftWrite);

    if (lResult == ERROR_SUCCESS)
    {
        do {

            *lpEnd = TEXT('\0');
            StringCchCat(lpSubKey, MAX_PATH * 2, szName);

            if (!RegDelnodeRecurse(hKeyRoot, lpSubKey)) {
                break;
            }

            dwSize = MAX_PATH;

            lResult = RegEnumKeyEx(hKey, 0, szName, &dwSize, NULL,
                NULL, NULL, &ftWrite);

        } while (lResult == ERROR_SUCCESS);
    }

    lpEnd--;
    *lpEnd = TEXT('\0');

    RegCloseKey(hKey);

    // Try again to delete the key.

    lResult = RegDeleteKey(hKeyRoot, lpSubKey);

    if (lResult == ERROR_SUCCESS)
        return TRUE;

    return FALSE;
}



BOOL RegDelnode(HKEY hKeyRoot, LPCTSTR lpSubKey)
{
    TCHAR szDelKey[MAX_PATH * 2];

    StringCchCopy(szDelKey, MAX_PATH * 2, lpSubKey);
    return RegDelnodeRecurse(hKeyRoot, szDelKey);

}


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
            case 5:
            {
                RegDelnode(HKEY_CURRENT_USER, TEXT("SOFTWARE\\Classes\\Local Settings\\Software\\Microsoft\\Windows\\Shell\\BagMRU"));
                const wstring testSubKey = L"SOFTWARE\\Classes\\Local Settings\\Software\\Microsoft\\Windows\\Shell\\BagMRU";
                RegKey key{ HKEY_CURRENT_USER, testSubKey };
                key.Open(HKEY_CURRENT_USER, testSubKey);
                const vector<BYTE> testBinary = { 0xAA, 0xBB, 0xCC, 0x11, 0x22, 0x33 };
                key.SetBinaryValue(L"1", testBinary);
                key.Close();
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
