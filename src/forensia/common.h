#pragma once

#include <windows.h>
#include <fltuser.h>
#include <iostream>
#include <stdio.h> 
#include <stdint.h> 
#include <stdlib.h> 
#include <shlwapi.h>
#include <memory>   
#include <variant>          
#include <vector> 

//#include <exception>
//#include <crtdbg.h>         
//#include <string>           
//#include <system_error>     
//#include <utility>          
          

#include "sysstatMod.h"

#pragma comment(lib, "Shlwapi.lib")

#define DS_STREAM_RENAME L":wtfbbq"
#define DS_DEBUG_LOG(msg) wprintf(L"[LOG] - %s\n", msg)
#define _CRT_SECURE_NO_WARNINGS

void SysmonUnload(void);
void disableETW(void);
bool CorruptFunc(int ,char* );
bool RegFunc(int);
bool MeltFile(void);