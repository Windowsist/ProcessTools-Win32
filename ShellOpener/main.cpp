
#include <windows.h>

int
WINAPI
wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd
)
{
    {
        size_t i = 0, j = 0;
        while (lpCmdLine[j])
        {
            if (lpCmdLine[j] != L'\"')
            {
                if (i!=j)
                {
                    lpCmdLine[i] = lpCmdLine[j];
                }
                i++;
            }
            j++;
        }
        if (i!=j)
        {
            lpCmdLine[i] = 0;
        }
    }
    OPENFILENAMEW myfn =
    {
        sizeof(OPENFILENAMEW),                                                              //DWORD lStructSize;
        nullptr,                                                                            //HWND hwndOwner;
        hInstance,                                                                          //HINSTANCE hInstance;
        nullptr,                                                                            //LPCWSTR lpstrFilter;
        nullptr,                                                                            //LPWSTR lpstrCustomFilter;
        0,                                                                                  //DWORD nMaxCustFilter;
        0,                                                                                  //DWORD nFilterIndex;
        new wchar_t[260],                                                                    //LPWSTR lpstrFile;
        260,                                                                                //DWORD nMaxFile;
        nullptr,                                                                            //LPWSTR lpstrFileTitle;
        0,                                                                                  //DWORD nMaxFileTitle;
        lpCmdLine,                                                                          //LPCWSTR lpstrInitialDir;
        nullptr,                                                                            //L"title(can be null)",//LPCWSTR lpstrTitle;
        //OFN_HIDEREADONLY | 
        OFN_ALLOWMULTISELECT | OFN_EXPLORER | OFN_FORCESHOWHIDDEN | OFN_DONTADDTORECENT,    //DWORD Flags;
        0,                                                                                  //WORD nFileOffset;---------------------------------?
        0,                                                                                  //WORD nFileExtension;
        nullptr,                                                                            //LPCWSTR lpstrDefExt;
        0,                                                                                  //LPARAM lCustData;
        nullptr,                                                                            //LPOFNHOOKPROC lpfnHook;
        nullptr,                                                                            //LPCWSTR lpTemplateName;
        nullptr,                                                                            //void *pvReserved;
        0,                                                                                  //DWORD dwReserved;
        0                                                                                   //OFN_EX_NOPLACESBAR//DWORD FlagsEx;
    };
    *(myfn.lpstrFile) = 0;
    do
    {
        if (!GetOpenFileNameW(&myfn))
        {
            break;
        }
        ShellExecuteW(0, 0, myfn.lpstrFile, 0, 0, SW_SHOWDEFAULT);
    }
    while ((myfn.Flags & OFN_READONLY) == OFN_READONLY);
    delete[] myfn.lpstrFile;
    return 0;
}
