// exec.cpp : 定义应用程序的入口点。
//

#include "../framework.h"

#pragma comment(linker,"/ENTRY:entry")

void entry()
{
    LPWSTR lpCmdLine = GetCommandLineW();
    bool in = false;
    UINT i = 0, j = 0;
    wchar_t pathfn[260],pathdir[260];
    while (*lpCmdLine)
    {
        if (*lpCmdLine == L'\"')
        {
            in = !in;
        }
        else if (*lpCmdLine == L' ' && !in)
        {
            lpCmdLine++;
            break;
        }
        lpCmdLine++;
    }
    if (!lpCmdLine[0])
    {
        MessageBoxW(0,L"需要指定运行的程序",L"未运行",MB_ICONINFORMATION);
        ExitProcess(0);
    }
    while (lpCmdLine[i])
    {
        if (lpCmdLine[i] == L'\"')
        {
            in = !in;
        }
        else if (lpCmdLine[i] == L' ' && !in)
        {
            break;
        }
        else
        {
            pathfn[j++] = lpCmdLine[i];
        }
        i++;
    }
    pathfn[j] = 0;
    while (pathfn[j]!=L'\\'&&j)
    {
        j--;
    }
    lstrcpynW(pathdir, pathfn, j + 2);
    _STARTUPINFOW si = {};
    _PROCESS_INFORMATION pi;
    if (!CreateProcessW(pathfn, lpCmdLine, 0, 0, 0, 0, 0, pathdir, &si, &pi))
    {
        HANDLE hp = GetProcessHeap();
        LPWSTR info = (LPWSTR)HeapAlloc(hp, HEAP_GENERATE_EXCEPTIONS, sizeof(wchar_t) * ((size_t)lstrlenW(pathfn) + lstrlenW(lpCmdLine) + lstrlenW(pathdir) + 19));
        lstrcpyW(info, L"程序：");
        lstrcatW(info, pathfn);
        lstrcatW(info, L"\n命令行：");
        lstrcatW(info, lpCmdLine);
        lstrcatW(info, L"\n工作目录：");
        lstrcatW(info, pathdir);
        MessageBoxW(0, info, L"运行失败", MB_ICONERROR);
        HeapFree(hp,0,info);
    }
    ExitProcess(0);
} 
