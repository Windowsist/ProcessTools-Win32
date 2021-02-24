
#include <windows.h>

int
    WINAPI
    wWinMain(_In_ HINSTANCE hInstance,
             _In_opt_ HINSTANCE hPrevInstance,
             _In_ LPWSTR lpCmdLine,
             _In_ int nShowCmd)
{
    if (!*lpCmdLine)
    {
        MessageBoxW(nullptr, L"需要指定运行的程序", L"未运行", MB_ICONINFORMATION);
        return 0;
    }
    int argc;
    LPWSTR * argv = CommandLineToArgvW(lpCmdLine,&argc);
    wchar_t pathdir[260];
    _wsplitpath_s(argv[0],pathdir,3,pathdir+2,258,nullptr,0,nullptr,0);
    if (!CreateProcessW(argv[0], lpCmdLine, nullptr, nullptr, FALSE, 0, nullptr, pathdir, &_STARTUPINFOW(), &_PROCESS_INFORMATION()))
    {
        LPWSTR info = new wchar_t[(size_t)lstrlenW(argv[0]) + lstrlenW(lpCmdLine) + lstrlenW(pathdir) + 17];
        lstrcpyW(info, L"程序：");
        lstrcatW(info, argv[0]);
        lstrcatW(info, L"\r\n命令行：");
        lstrcatW(info, lpCmdLine);
        lstrcatW(info, L"\r\n工作目录：");
        lstrcatW(info, pathdir);
        MessageBoxW(nullptr, info, L"运行失败", MB_ICONERROR);
        delete[] info;
    }
    return 0;
}
