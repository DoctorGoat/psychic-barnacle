#include "hazldll.h"
#include "detours/detours.h"
#include <map>
#include <ranges>

using namespace std;
HMODULE tempHandler = nullptr;
ofstream of("test.txt", ios::app);

//this is garbage i copied from stackoverflow or something
std::string WStringToString(const std::wstring& s)
{
    std::string temp(s.length(), ' ');
    std::copy(s.begin(), s.end(), temp.begin());
    return temp;
}

//this gets us a map in the form of DLL_NAME, 0x08008135
std::map<string, PVOID> locations;

HMODULE(__stdcall* Real_LoadLibraryA)(LPCSTR a0) = LoadLibraryA;
HMODULE(__stdcall* Real_LoadLibraryW)(LPCWSTR a0) = LoadLibraryW;

HMODULE __stdcall hazl_LoadLibraryA(LPCSTR a0)
{
    //    of << "\nLPCSTR LoadLibraryA: " << a0 << endl;
    //    const char* tempstring = a0;
    HMODULE tempHandler = Real_LoadLibraryA(a0);
    locations[a0] = DetourGetEntryPoint(tempHandler);

//    if (!_stricmp(tempstring, why))
//    {
        //      logic for patching might go here...?
//    }

    //    of << "Entry Point: " << DetourGetEntryPoint(tempHandler) << endl;

    return tempHandler;
}

HMODULE __stdcall hazl_LoadLibraryW(LPCWSTR a0)
{
    HMODULE tempHandler = Real_LoadLibraryW(a0);
    locations[WStringToString(a0)] = DetourGetEntryPoint(tempHandler);
    of << "\nLPCWSTR LoadLibraryW: " << WStringToString(a0) << endl;
    return Real_LoadLibraryW(a0);
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    if (DetourIsHelperProcess()) {
        return TRUE;
    }

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DetourRestoreAfterWith();
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach((PVOID*)&Real_LoadLibraryA, hazl_LoadLibraryA);
        DetourAttach((PVOID*)&Real_LoadLibraryW, hazl_LoadLibraryW);
        DetourTransactionCommit();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourTransactionCommit();
        break;
    }

/*    map<string, PVOID>::iterator it = locations.begin();
    of << "DUMPING ALL THAT SHIT\n\n\n" << endl;
    while (it != locations.end()) {
        of << "Key: " << it->first
            << ", Value: " << it->second << endl;
        ++it;
    }
    of << "OKAY IT'S DONE.";
*/
    return TRUE;
}

