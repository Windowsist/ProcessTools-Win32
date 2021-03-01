
#include "main.h"

int
    WINAPI
    wWinMain(_In_ HINSTANCE hInstance,
             _In_opt_ HINSTANCE hPrevInstance,
             _In_ LPWSTR lpCmdLine,
             _In_ int nShowCmd)
{
    StringTableInit(hInstance);
    if (!*lpCmdLine)
    {
        MessageBoxW(nullptr, szNeedArg, szNotStarted, MB_ICONINFORMATION);
        return 0;
    }
    int argc;
    LPWSTR * argv = CommandLineToArgvW(lpCmdLine,&argc);
    wchar_t pathdir[260];
    _wsplitpath_s(argv[0],pathdir,3,pathdir+2,258,nullptr,0,nullptr,0);
    if (!CreateProcessW(argv[0], lpCmdLine, nullptr, nullptr, FALSE, 0, nullptr, pathdir, &_STARTUPINFOW(), &_PROCESS_INFORMATION()))
    {
        LPWSTR info = new wchar_t[(size_t)lstrlenW(szProgram) + lstrlenW(argv[0]) + lstrlenW(szCmdLine) + lstrlenW(lpCmdLine) + lstrlenW(szDirectory) + lstrlenW(pathdir) + 1];
        lstrcpyW(info, szProgram);
        lstrcatW(info, argv[0]);
        lstrcatW(info, szCmdLine);
        lstrcatW(info, lpCmdLine);
        lstrcatW(info, szDirectory);
        lstrcatW(info, pathdir);
        MessageBoxW(nullptr, info, szStartFailed, MB_ICONERROR);
        delete[] info;
    }
    return 0;
}
