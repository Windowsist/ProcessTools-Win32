
#include "main.h"

int
    WINAPI
    wWinMain(_In_ HINSTANCE hInstance,
             _In_opt_ HINSTANCE hPrevInstance,
             _In_ LPWSTR lpCmdLine,
             _In_ int nShowCmd)
{
    DialogBoxW(hInstance, MAKEINTRESOURCEW(IDD_DIALOG1), nullptr, DlgProc);
    return 0;
}

INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:{
        LPWCH env = GetEnvironmentStringsW();
        int envlen = 0;
        for (LPWSTR i = env; lstrlenW(i); i += lstrlenW(i) + 1)
        {
            envlen += lstrlenW(i) + 2;
        }
        LPWSTR envString = new wchar_t[envlen + 1];
        envString[0] = 0;
        for (LPWSTR i = env; lstrlenW(i); i += lstrlenW(i) + 1)
        {
            lstrcatW(envString, i);
            lstrcatW(envString, L"\r\n");
        }
        Edit_SetText(GetDlgItem(hDlg, IDC_EDIT1), GetCommandLineW());
        Edit_SetText(GetDlgItem(hDlg, IDC_EDIT2), envString);
        delete[] envString;}
        return (INT_PTR)TRUE;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
