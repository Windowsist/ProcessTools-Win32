#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(linker,"/ENTRY:entry")

#include <windows.h>

void entry()
{
    HANDLE hp = GetProcessHeap();
    wchar_t pathmdfn[260],pathfn[260], cmdl[260],pathdir[260];
    GetModuleFileNameW(nullptr, pathmdfn, 260);
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
    GetPrivateProfileStringW(L"LaunchApp",L"AppPath",nullptr,pathfn + baselen,260 - baselen,pathmdfn);
    GetPrivateProfileStringW(L"LaunchApp", L"WorkingDirectory", nullptr, pathdir + baselen, 260 - baselen, pathmdfn);
    GetPrivateProfileStringW(L"LaunchApp", L"CommandLine", nullptr, cmdl + baselen + 1, 260 - baselen - 1, pathmdfn);
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
            MessageBoxW(nullptr, i, L"设置环境变量失败", MB_ICONERROR);
        }
    }
    _STARTUPINFOW si = {};
    _PROCESS_INFORMATION pi;
    if (!CreateProcessW(pathfn, cmdl, nullptr, nullptr, FALSE, 0, nullptr, pathdir, &si, &pi))
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
        MessageBoxW(nullptr, info, L"运行失败", MB_ICONERROR);
        HeapFree(hp, 0, info);
    }
    HeapFree(hp, 0, env);
    ExitProcess(0);
} 
