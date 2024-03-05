#include "hazldll.h"
#include "detours/detours.h"
#include <map>

using namespace std;
HMODULE tempHandler = nullptr;
ofstream of("test.txt", ios::app);

//this gets us a map in the form of DLL_NAME, loaded_address
//might be worthwhile to get the actual base address of the 
//module or just throw in a define file that ensures that
//0x6FC113000 - Base = 0x00011300, rather than the DLLMain
//entry.
std::map<string, PVOID> locations;

//This gets us everything we need. We can call Real_LoadLibraryA
//for the real thing and we can point its reference at Detours
//for use in redirection. Consider this the most basic example.
//The logic for patching will ideally check if a loaded module is
//desired for patching (like, ah! D2GaMe.DlL! I should patch that)
//Then we'd use BinaryOpen on the HMODULE right after it's loaded
//but before the LoadLibrary command has returned.
HMODULE(__stdcall* Real_LoadLibraryA)(LPCSTR a0) = LoadLibraryA;
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
    //A very professional logging block.
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

