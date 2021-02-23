#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <windows.h>

int
    WINAPI
    wWinMain(_In_ HINSTANCE hInstance,
             _In_opt_ HINSTANCE hPrevInstance,
             _In_ LPWSTR lpCmdLine,
             _In_ int nShowCmd)
{
    wchar_t pathmdfn[260], pathfn[260], cmdl[260], pathdir[260];
    GetModuleFileNameW(hInstance, pathmdfn, 260);
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
    GetPrivateProfileStringW(L"LaunchApp", L"AppPath", nullptr, pathfn + baselen, 260 - baselen, pathmdfn);
    GetPrivateProfileStringW(L"LaunchApp", L"WorkingDirectory", nullptr, pathdir + baselen, 260 - baselen, pathmdfn);
    GetPrivateProfileStringW(L"LaunchApp", L"CommandLine", nullptr, cmdl + baselen + 1, 259 - baselen, pathmdfn);
    UINT envsize = GetPrivateProfileIntW(L"LaunchApp", L"EnvironmentSize", 1, pathmdfn), envnum = 0;
    LPWSTR env = new wchar_t[envsize];
    GetPrivateProfileSectionW(L"Environment", env, envsize, pathmdfn);
    for (LPWSTR i = env; lstrlenW(i); i += lstrlenW(i) + 1)
    {
        envnum++; // "\0" --> "\r\n", every env expands size 1
        if (_wputenv(i))
        {
            MessageBoxW(nullptr, i, L"设置环境变量失败", MB_ICONWARNING);
        }
    }
    if (!CreateProcessW(pathfn, cmdl, nullptr, nullptr, FALSE, 0, nullptr, pathdir, &_STARTUPINFOW(), &_PROCESS_INFORMATION()))
    {
        LPWSTR info = new wchar_t[(size_t)lstrlenW(pathmdfn) + lstrlenW(pathfn) + lstrlenW(cmdl) + lstrlenW(pathdir) + envsize + envnum + 30];
        lstrcpyW(info, L"配置文件：");
        lstrcatW(info, pathmdfn);
        lstrcatW(info, L"\r\n程序：");
        lstrcatW(info, pathfn);
        lstrcatW(info, L"\r\n命令行：");
        lstrcatW(info, cmdl);
        lstrcatW(info, L"\r\n工作目录：");
        lstrcatW(info, pathdir);
        lstrcatW(info, L"\r\n环境变量：");
        for (LPWSTR i = env; lstrlenW(i); i += lstrlenW(i) + 1)
        {
            lstrcatW(info, L"\r\n");
            lstrcatW(info, i);
        }
        MessageBoxW(nullptr, info, L"运行失败", MB_ICONERROR);
        delete[] info;
    }
    delete[] env;
    return 0;
}
