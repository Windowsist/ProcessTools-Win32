
#include <windows.h>

#include "../comctl6.h"

extern "C" DWORD Startup(LPVOID)
{
	{
		OPENFILENAMEW ofn
		{
			sizeof(OPENFILENAMEW), //DWORD lStructSize;
			nullptr,               //HWND hwndOwner;
			nullptr,               //HINSTANCE hInstance;
			nullptr,               //LPCWSTR lpstrFilter;
			nullptr,               //LPWSTR lpstrCustomFilter;
			0UL,                   //DWORD nMaxCustFilter;
			0UL,                   //DWORD nFilterIndex;
			nullptr,               //LPWSTR lpstrFile;
			1UL,                   //DWORD nMaxFile;
			nullptr,               //LPWSTR lpstrFileTitle;
			0UL,                   //DWORD nMaxFileTitle;
			nullptr,               //LPCWSTR lpstrInitialDir;
			nullptr,               //L"title(can be null)",//LPCWSTR lpstrTitle;
			OFN_HIDEREADONLY |
				OFN_ALLOWMULTISELECT |
				OFN_EXPLORER |
				OFN_FORCESHOWHIDDEN |
				OFN_DONTADDTORECENT, //DWORD Flags;
			0,                       //WORD nFileOffset;---------------------------------?
			0,                       //WORD nFileExtension;
			nullptr,                 //LPCWSTR lpstrDefExt;
			0LL,                     //LPARAM lCustData;
			nullptr,                 //LPOFNHOOKPROC lpfnHook;
			nullptr,                 //LPCWSTR lpTemplateName;
			nullptr,                 //void *pvReserved;
			0UL,                     //DWORD dwReserved;
			0UL                      //OFN_EX_NOPLACESBAR//DWORD FlagsEx;
		};
		while (GetOpenFileNameW(&ofn))
			;
	}
	ExitProcess(0U);
	return 0UL;
}
