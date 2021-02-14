// Launcher_Env.cpp : 定义应用程序的入口点。
//

#include <windows.h>

#pragma comment(linker,"/ENTRY:entry")

void entry()
{
    HANDLE hp = GetProcessHeap();
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
    lstrcpynW(cmdl+1, pathmdfn, baselen + 1);
    lstrcpynW(pathdir,pathmdfn, baselen + 1);
    lstrcpyW(pathmdfn + lstrlenW(pathmdfn) - 3, L"ini");
    GetPrivateProfileStringW(L"LaunchApp",L"AppPath",0,pathfn + baselen,260 - baselen,pathmdfn);
    GetPrivateProfileStringW(L"LaunchApp", L"WorkingDirectory", 0, pathdir + baselen, 260 - baselen, pathmdfn);
    GetPrivateProfileStringW(L"LaunchApp", L"CommandLine", 0, cmdl + baselen + 1, 260 - baselen - 1, pathmdfn);
    UINT envsize = GetPrivateProfileIntW(L"LaunchApp", L"EnvironmentSize", 1, pathmdfn);
    const LPWSTR env = (LPWSTR)HeapAlloc(hp, HEAP_GENERATE_EXCEPTIONS, sizeof(wchar_t) * envsize);
    GetPrivateProfileSectionW(L"Environment", env, envsize, pathmdfn);
    for (LPWSTR i = env; lstrlenW(i); i += lstrlenW(i) + 1)
    {
        int j = 0;
        while (i[j]&&i[j]!=L'=')
        {
            j++;
        }
        i[j] = 0;
        BOOL rst = SetEnvironmentVariableW(i,i+j+1);
        i[j] = L'=';
        if (!rst)
        {
            MessageBoxW(0, i, L"设置环境变量失败", MB_ICONERROR);
        }
    }
    _STARTUPINFOW si = {};
    _PROCESS_INFORMATION pi;
    if (!CreateProcessW(pathfn, cmdl, 0, 0, 0, 0, 0, pathdir, &si, &pi))
    {
        LPWSTR info = (LPWSTR)HeapAlloc(hp, HEAP_GENERATE_EXCEPTIONS, sizeof(wchar_t) * ((size_t)lstrlenW(pathmdfn) + lstrlenW(pathfn) + lstrlenW(cmdl) + lstrlenW(pathdir) + envsize + 26));
        lstrcpyW(info, L"配置文件：");
        lstrcatW(info, pathmdfn);
        lstrcatW(info, L"\n程序：");
        lstrcatW(info, pathfn);
        lstrcatW(info, L"\n命令行：");
        lstrcatW(info, cmdl);
        lstrcatW(info, L"\n工作目录：");
        lstrcatW(info, pathdir);
        lstrcatW(info, L"\n环境变量：");
        for (LPWSTR i = env; lstrlenW(i); i += lstrlenW(i) + 1)
        {
            lstrcatW(info, L"\n");
            lstrcatW(info, i);
        }
        MessageBoxW(0, info, L"运行失败", MB_ICONERROR);
        HeapFree(hp, 0, info);
    }
    HeapFree(hp, 0, env);
    ExitProcess(0);
} 
