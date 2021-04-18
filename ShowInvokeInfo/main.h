#pragma once

#include <windows.h>
#include <windowsx.h>
#include "resource.h"

#include "../comctl6.h"

extern "C" {
	DWORD Startup(LPVOID);
	INT_PTR DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
}
