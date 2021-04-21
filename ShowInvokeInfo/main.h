#pragma once

#include <windows.h>
#include <windowsx.h>
#include "resource.h"

#include "../comctl6.h"

DWORD Startup();
INT_PTR DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
