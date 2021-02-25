
#include <windows.h>

int
    WINAPI
    wWinMain(_In_ HINSTANCE hInstance,
             _In_opt_ HINSTANCE hPrevInstance,
             _In_ LPWSTR lpCmdLine,
             _In_ int nShowCmd)
{
    wchar_t lpstrFile[260];
    OPENFILENAMEW ofn =
        {
            sizeof(OPENFILENAMEW), //DWORD lStructSize;
            nullptr,               //HWND hwndOwner;
            hInstance,             //HINSTANCE hInstance;
            nullptr,               //LPCWSTR lpstrFilter;
            nullptr,               //LPWSTR lpstrCustomFilter;
            0,                     //DWORD nMaxCustFilter;
            0,                     //DWORD nFilterIndex;
            lpstrFile,      //LPWSTR lpstrFile;
            260,                   //DWORD nMaxFile;
            nullptr,               //LPWSTR lpstrFileTitle;
            0,                     //DWORD nMaxFileTitle;
            nullptr,               //LPCWSTR lpstrInitialDir;
            nullptr,               //L"title(can be null)",//LPCWSTR lpstrTitle;
            //OFN_HIDEREADONLY |
            OFN_ALLOWMULTISELECT |
                OFN_EXPLORER |
                OFN_FORCESHOWHIDDEN |
                OFN_DONTADDTORECENT, //DWORD Flags;
            0,                       //WORD nFileOffset;---------------------------------?
            0,                       //WORD nFileExtension;
            nullptr,                 //LPCWSTR lpstrDefExt;
            0,                       //LPARAM lCustData;
            nullptr,                 //LPOFNHOOKPROC lpfnHook;
            nullptr,                 //LPCWSTR lpTemplateName;
            nullptr,                 //void *pvReserved;
            0,                       //DWORD dwReserved;
            0                        //OFN_EX_NOPLACESBAR//DWORD FlagsEx;
        };
    if (*lpCmdLine)
    {
        int argc;
        LPWSTR *argv = CommandLineToArgvW(lpCmdLine, &argc);
        ofn.lpstrInitialDir = argv[0];
    }
    *(ofn.lpstrFile) = 0;
    do
    {
        if (!GetOpenFileNameW(&ofn))
        {
            break;
        }
        ShellExecuteW(nullptr, nullptr, ofn.lpstrFile, nullptr, nullptr, SW_SHOWDEFAULT);
    } while ((ofn.Flags & OFN_READONLY) == OFN_READONLY);
    return 0;
}
