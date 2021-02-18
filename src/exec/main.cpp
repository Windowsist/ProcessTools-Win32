#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <windows.h>

int
    WINAPI
    wWinMain(_In_ HINSTANCE hInstance,
             _In_opt_ HINSTANCE hPrevInstance,
             _In_ LPWSTR lpCmdLine,
             _In_ int nShowCmd)
{
    if (!lpCmdLine[0])
    {
        MessageBoxW(nullptr, L"需要指定运行的程序", L"未运行", MB_ICONINFORMATION);
        return 0;
    }
    bool in = false;
    UINT i = 0, j = 0;
    wchar_t pathfn[260], pathdir[260];
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
    while (pathfn[j] != L'\\' && j)
    {
        j--;
    }
    lstrcpynW(pathdir, pathfn, j + 2);
    if (!CreateProcessW(pathfn, lpCmdLine, nullptr, nullptr, FALSE, 0, nullptr, pathdir, &_STARTUPINFOW(), &_PROCESS_INFORMATION()))
    {
        LPWSTR info = new wchar_t[(size_t)lstrlenW(pathfn) + lstrlenW(lpCmdLine) + lstrlenW(pathdir) + 19];
        lstrcpyW(info, L"程序：");
        lstrcatW(info, pathfn);
        lstrcatW(info, L"\n命令行：");
        lstrcatW(info, lpCmdLine);
        lstrcatW(info, L"\n工作目录：");
        lstrcatW(info, pathdir);
        MessageBoxW(nullptr, info, L"运行失败", MB_ICONERROR);
        delete[] info;
    }
    return 0;
}
