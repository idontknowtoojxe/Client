#include "pch.h"
#include <windows.h>
#define _CRT_SECURE_NO_WARNINGS
#define UNINITIALIZED 0xFFFFFFFF
#include <iostream>
#include <TlHelp32.h>
using namespace std;

void Change() {
    std::wstring myProcess = L"client.exe";  // เปลี่ยนเป็น std::wstring
    while (1) {
        Sleep(50);
        HANDLE hProcessSnap;
        PROCESSENTRY32 pe32;

        hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        pe32.dwSize = sizeof(PROCESSENTRY32);
        try
        {
            if (SetCurrentDirectory(L"C:\\isreal")) {
                if (Process32First(hProcessSnap, &pe32)) {
                    do {
                        std::wstring processName = pe32.szExeFile;  // เปลี่ยนเป็น std::wstring
                    } while (Process32Next(hProcessSnap, &pe32));
                }
            }
            else {
                MessageBox(NULL, L"Not Found Client", L"Error ( X01 )", MB_OK | MB_ICONERROR);
                exit(-1);
            }
        }
        catch (const std::exception&)
        {
            exit(-1);
        }

        CloseHandle(hProcessSnap);
        system(("start \"\" " + std::string(myProcess.begin(), myProcess.end())).c_str());  // เพิ่มการแปลงเป็น std::string

        Sleep(30 * 1000);
    }
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
        ShowWindow(GetConsoleWindow(), SW_HIDE);
        Change();
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}