#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files

#pragma once 
#include "cstdio"
#include "Windows.h"
#include "detours/detours.h"
#include "D2Unicode.h"
#include "D2CommonDefinitions/D2BasicTypes.h"
#include <string>

#include <iostream>
#include <fstream>

#include <windows.h>
#include <iostream>
#include <fstream>

struct hazlpatch {
	std::string targetdll;
	DWORD offset;
	PVOID newFunc;

	hazlpatch(const std::string& targetdll, const DWORD& offset, const PVOID& newFunc)
		: targetdll(targetdll), offset(offset), newFunc(newFunc)
	{
	}
};