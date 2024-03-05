// HazlLaunch.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <codecvt>
#include <iostream>
#include "c:\dev\nop\external\D2.Detours\source\include\DetoursHelpers.h"
#include "c:\dev\nop\external\D2.Detours\external\Detours\include\detours.h"
#include "HazlLaunch.h"

using namespace std;

// typedef const wchar_t* LPCWSTR; 
// lpcstr:  typedef char* PSTR, *LPSTR; 
// typedef const wchar_t* LPCWSTR; 
// typedef wchar_t* LPWSTR, *PWSTR;

int main()
{
    //Welcome to Hazel's launcher
    //I got frustrated with the last version, because there are one hundred types of strings.
    //So I read up on it and here's another attempt.
    
    const wchar_t* appName = hazl::strings::returnwchar_t("C:\Games\d2exe\Diablo II.exe");
    const wchar_t* test = hazl::strings::returnwchar_t("what");

    STARTUPINFOW si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);

    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));

    if (DetourCreateProcessWithDllExW(appName, NULL,
        NULL, NULL,
        TRUE, CREATE_DEFAULT_ERROR_MODE | CREATE_SUSPENDED,
        NULL, NULL,
        &si, &pi, "Diablo II.exe", NULL
        ))
            {
                ResumeWaitAndCleanChildProcess(pi);
    //            return 0;
            }
}

//Lectem wrote this, along with many other bits gleaned from D2Moo, D2.Detours.
static void ResumeWaitAndCleanChildProcess(const PROCESS_INFORMATION& pi)
{
    ResumeThread(pi.hThread);
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
