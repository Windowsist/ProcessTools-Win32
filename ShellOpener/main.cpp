
#include "../framework.h"

int
WINAPI
wWinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR lpCmdLine,
    int nShowCmd
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
        0, //nullptr                                                                            //HWND hwndOwner;
        hInstance,                                                                          //HINSTANCE hInstance;
        0, //nullptr                                                                            //LPCWSTR lpstrFilter;
        0, //nullptr                                                                            //LPWSTR lpstrCustomFilter;
        0,                                                                                  //DWORD nMaxCustFilter;
        0,                                                                                  //DWORD nFilterIndex;
        new wchar_t[260],                                                                    //LPWSTR lpstrFile;
        260,                                                                                //DWORD nMaxFile;
        0, //nullptr                                                                            //LPWSTR lpstrFileTitle;
        0,                                                                                  //DWORD nMaxFileTitle;
        lpCmdLine,                                                                          //LPCWSTR lpstrInitialDir;
        0, //nullptr                                                                            //L"title(can be null)",//LPCWSTR lpstrTitle;
        //OFN_HIDEREADONLY | 
        OFN_ALLOWMULTISELECT | OFN_EXPLORER | OFN_FORCESHOWHIDDEN | OFN_DONTADDTORECENT,    //DWORD Flags;
        0,                                                                                  //WORD nFileOffset;---------------------------------?
        0,                                                                                  //WORD nFileExtension;
        0, //nullptr                                                                            //LPCWSTR lpstrDefExt;
        0,                                                                                  //LPARAM lCustData;
        0, //nullptr                                                                            //LPOFNHOOKPROC lpfnHook;
        0, //nullptr                                                                            //LPCWSTR lpTemplateName;
        0, //nullptr                                                                            //void *pvReserved;
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
