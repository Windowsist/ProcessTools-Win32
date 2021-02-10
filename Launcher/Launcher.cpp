// Launcher.cpp : 定义应用程序的入口点。
//

#include "../framework.h"

#pragma comment(linker,"/ENTRY:entry")

void entry()
{
    wchar_t pathmdfn[260],pathfn[260], cmdl[260],pathdir[260];
    GetModuleFileNameW(0, pathmdfn, 260);
    UINT baselen = lstrlenW(pathmdfn) - 1;
    while (pathmdfn[baselen] != L'\\' && baselen)
    {
        baselen--;
    }
    baselen++;
    cmdl[0] = L'\"';
    lstrcpynW(pathfn, pathmdfn, baselen + 1);
    lstrcpynW(cmdl + 1, pathmdfn, baselen + 1);
    lstrcpynW(pathdir, pathmdfn, baselen + 1);
    lstrcpyW(pathmdfn + lstrlenW(pathmdfn) - 3, L"ini");
    GetPrivateProfileStringW(L"LaunchApp",L"AppPath",0, pathfn + baselen,260 - baselen,pathmdfn);
    GetPrivateProfileStringW(L"LaunchApp", L"WorkingDirectory", 0, pathdir + baselen, 260 - baselen, pathmdfn);
    GetPrivateProfileStringW(L"LaunchApp", L"CommandLine", 0, cmdl + baselen + 1, 260 - baselen - 1, pathmdfn);
    _STARTUPINFOW si = {};
    _PROCESS_INFORMATION pi;
    if (!CreateProcessW(pathfn, cmdl, 0, 0, 0, 0, 0, pathdir, &si, &pi))
    {
        HANDLE hp = GetProcessHeap();
        LPWSTR info = (LPWSTR)HeapAlloc(hp, HEAP_GENERATE_EXCEPTIONS, sizeof(wchar_t) * ((size_t)lstrlenW(pathmdfn) + lstrlenW(pathfn) + lstrlenW(cmdl) + lstrlenW(pathdir) + 21));
        lstrcpyW(info, L"配置文件：");
        lstrcatW(info, pathmdfn);
        lstrcatW(info, L"\n程序：");
        lstrcatW(info, pathfn);
        lstrcatW(info, L"\n命令行：");
        lstrcatW(info, cmdl);
        lstrcatW(info, L"\n工作目录：");
        lstrcatW(info, pathdir);
        MessageBoxW(0, info, L"运行失败", MB_ICONERROR);
        HeapFree(hp, 0, info);
    }
    ExitProcess(0);
} 
