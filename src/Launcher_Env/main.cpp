
#include "main.h"

int
    WINAPI
    wWinMain(_In_ HINSTANCE hInstance,
             _In_opt_ HINSTANCE hPrevInstance,
             _In_ LPWSTR lpCmdLine,
             _In_ int nShowCmd)
{
    StringTableInit(hInstance);
    wchar_t pathmdfn[260], pathfn[260], cmdl[260], pathdir[260];
    GetModuleFileNameW(hInstance, pathmdfn, 260);
    {
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
    }
    UINT envnum = 0, envsize = GetPrivateProfileIntW(L"LaunchApp", L"EnvironmentSize", 1, pathmdfn);
    LPWSTR env = new wchar_t[envsize];
    GetPrivateProfileSectionW(L"Environment", env, envsize, pathmdfn);
    for (LPWSTR i = env; lstrlenW(i); i += lstrlenW(i) + 1)
    {
        envnum++; // "\0" --> "\r\n", every env expands size 1
        if (_wputenv(i))
        {
            MessageBoxW(nullptr, i, szSetEnvFailed, MB_ICONWARNING);
        }
    }
    if (!CreateProcessW(pathfn, cmdl, nullptr, nullptr, FALSE, 0, nullptr, pathdir, &_STARTUPINFOW(), &_PROCESS_INFORMATION()))
    {
        LPWSTR info = new wchar_t[(size_t)lstrlenW(szCfgFile) + lstrlenW(pathmdfn) + lstrlenW(szProgram) + lstrlenW(pathfn) + lstrlenW(szCmdLine) + lstrlenW(cmdl) + lstrlenW(szDirectory) + lstrlenW(pathdir) + lstrlenW(szEnv) + envsize + envnum];
        lstrcpyW(info, szCfgFile);
        lstrcatW(info, pathmdfn);
        lstrcatW(info, szProgram);
        lstrcatW(info, pathfn);
        lstrcatW(info, szCmdLine);
        lstrcatW(info, cmdl);
        lstrcatW(info, szDirectory);
        lstrcatW(info, pathdir);
        lstrcatW(info, szEnv);
        for (LPWSTR i = env; lstrlenW(i); i += lstrlenW(i) + 1)
        {
            lstrcatW(info, L"\r\n");
            lstrcatW(info, i);
        }
        MessageBoxW(nullptr, info, szStartFailed, MB_ICONERROR);
        delete[] info;
    }
    delete[] env;
    return 0;
}
