
#include <windows.h>

DWORD Startup()
{
	{
		OPENFILENAMEW ofn =
		{
			sizeof(OPENFILENAMEW), //DWORD lStructSize;
			NULL,               //HWND hwndOwner;
			NULL,               //HINSTANCE hInstance;
			NULL,               //LPCWSTR lpstrFilter;
			NULL,               //LPWSTR lpstrCustomFilter;
			0UL,                   //DWORD nMaxCustFilter;
			0UL,                   //DWORD nFilterIndex;
			NULL,               //LPWSTR lpstrFile;
			1UL,                   //DWORD nMaxFile;
			NULL,               //LPWSTR lpstrFileTitle;
			0UL,                   //DWORD nMaxFileTitle;
			NULL,               //LPCWSTR lpstrInitialDir;
			NULL,               //L"title(can be null)",//LPCWSTR lpstrTitle;
			OFN_HIDEREADONLY |
				OFN_ALLOWMULTISELECT |
				OFN_EXPLORER |
				OFN_FORCESHOWHIDDEN |
				OFN_DONTADDTORECENT, //DWORD Flags;
			0,                       //WORD nFileOffset;---------------------------------?
			0,                       //WORD nFileExtension;
			NULL,                 //LPCWSTR lpstrDefExt;
			0LL,                     //LPARAM lCustData;
			NULL,                 //LPOFNHOOKPROC lpfnHook;
			NULL,                 //LPCWSTR lpTemplateName;
			NULL,                 //void *pvReserved;
			0UL,                     //DWORD dwReserved;
			0UL                      //OFN_EX_NOPLACESBAR//DWORD FlagsEx;
		};
		while (GetOpenFileNameW(&ofn))
			;
	}
	ExitProcess(0U);
	return 0UL;
}
