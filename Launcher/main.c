
#include "main.h"

LPWSTR expenv(LPWSTR raw)
{
	DWORD len = ExpandEnvironmentStringsW(raw, NULL, 0);
	LPWSTR value = calloc(len , sizeof(wchar_t));
	ExpandEnvironmentStringsW(raw, value, len);
	return value;
}

UINT _Startup()
{
	wchar_t file[260];
	wchar_t launcherdir[260];
	GetModuleFileNameW(NULL, file, 260);
	{
		int len = lstrlenW(file);
		lstrcpyW(file + len - 3, L"ini");
		{
			int i = len;
			while (i && file[i] != L'\\')
			{
				i--;
			}
			lstrcpynW(launcherdir, file, i + 1);
		}
	}
	SetEnvironmentVariableW(L"LauncherDir", launcherdir);
	DWORD length = 8;
	LPWSTR buffer = calloc(16 , sizeof(wchar_t));
	while (GetPrivateProfileStringW(L"LaunchApp", L"AppPath", NULL, buffer, length, file) == length - 1)
	{
		buffer = _recalloc(buffer, (length *= 2) , sizeof(wchar_t));
	}
	LPWSTR AppPath = GetLastError() == ERROR_FILE_NOT_FOUND ? NULL : expenv(buffer);
	while (GetPrivateProfileStringW(L"LaunchApp", L"WorkingDirectory", NULL, buffer, length, file) == length - 1)
	{
		buffer = _recalloc(buffer, (length *= 2) , sizeof(wchar_t));
	}
	LPWSTR WorkingDirectory = GetLastError() == ERROR_FILE_NOT_FOUND ? NULL : expenv(buffer);
	while (GetPrivateProfileStringW(L"LaunchApp", L"CommandLine", NULL, buffer, length, file) == length - 1)
	{
		buffer = _recalloc(buffer, (length *= 2) , sizeof(wchar_t));
	}
	LPWSTR CommandLine = GetLastError() == ERROR_FILE_NOT_FOUND ? NULL : expenv(buffer);
	while (GetPrivateProfileSectionW(L"EnvironmentVariables", buffer, length, file) == length - 2)
	{
		buffer = _recalloc(buffer, (length *= 2) , sizeof(wchar_t));
	}
	if (GetLastError() != ERROR_FILE_NOT_FOUND)
	{
		for (LPWSTR env = buffer; lstrlenW(env); env += lstrlenW(env) + 1)
		{
			LPWSTR enve = expenv(env);
			_wputenv(enve);
			free(enve);
		}
	}
	free(buffer);
	SetEnvironmentVariableW(L"LauncherDir", NULL);
	STARTUPINFOW si = { sizeof(STARTUPINFOW) };
	PROCESS_INFORMATION pi;
	if (!CreateProcessW(AppPath, CommandLine, NULL, NULL, FALSE, 0, NULL, WorkingDirectory, &si, &pi))
	{
		if (AppPath)free(AppPath);
		if (WorkingDirectory)free(WorkingDirectory);
		if (CommandLine)free(CommandLine);
		return GetLastError();
	}
	else
	{
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		if (AppPath)free(AppPath);
		if (WorkingDirectory)free(WorkingDirectory);
		if (CommandLine)free(CommandLine);
		return 0U;
	}
}

DWORD Startup()
{
	ExitProcess(_Startup());
	return 0UL;
}