
#include "main.h"


#define heapalloc(dwBytes) HeapAlloc(hHeap, 0, dwBytes)
#define heaprealloc(lpMem, dwBytes) HeapReAlloc(hHeap, 0, lpMem, dwBytes)
#define heapfree(lpMem) HeapFree(hHeap, 0, lpMem)

DWORD Startup()
{
	hHeap = GetProcessHeap();
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
	LPWSTR buffer = heapalloc(16);
	while (GetPrivateProfileStringW(L"LaunchApp", L"AppPath", NULL, buffer, length, file) == length - 1)
	{
		buffer = heaprealloc(buffer, (length *= 2) * sizeof(wchar_t));
	}
	LPWSTR AppPath = GetLastError() == ERROR_FILE_NOT_FOUND ? NULL : expandEnvString(buffer);
	while (GetPrivateProfileStringW(L"LaunchApp", L"WorkingDirectory", NULL, buffer, length, file) == length - 1)
	{
		buffer = heaprealloc(buffer, (length *= 2) * sizeof(wchar_t));
	}
	LPWSTR WorkingDirectory = GetLastError() == ERROR_FILE_NOT_FOUND ? NULL : expandEnvString(buffer);
	while (GetPrivateProfileStringW(L"LaunchApp", L"CommandLine", NULL, buffer, length, file) == length - 1)
	{
		buffer = heaprealloc(buffer, (length *= 2) * sizeof(wchar_t));
	}
	LPWSTR CommandLine = GetLastError() == ERROR_FILE_NOT_FOUND ? NULL : expandEnvString(buffer);
	while (GetPrivateProfileSectionW(L"EnvironmentVariables", buffer, length, file) == length - 2)
	{
		buffer = heaprealloc(buffer, (length *= 2) * sizeof(wchar_t));
	}
	if (GetLastError() != ERROR_FILE_NOT_FOUND)
	{
		for (LPWSTR env = buffer; lstrlenW(env); env += lstrlenW(env) + 1)
		{
			putenv(expandEnvString(env));
		}
	}
	heapfree(buffer);
	SetEnvironmentVariableW(L"LauncherDir", NULL);
	STARTUPINFOW si = { sizeof(STARTUPINFOW) };
	PROCESS_INFORMATION pi;
	if (!CreateProcessW(AppPath, CommandLine, NULL, NULL, FALSE, 0, NULL, WorkingDirectory, &si, &pi))
	{
		if (AppPath)heapfree(AppPath);
		if (WorkingDirectory)heapfree(WorkingDirectory);
		if (CommandLine)heapfree(CommandLine);
		ExitProcess(GetLastError());
	}
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	if (AppPath)heapfree(AppPath);
	if (WorkingDirectory)heapfree(WorkingDirectory);
	if (CommandLine)heapfree(CommandLine);
	ExitProcess(0);
	return 0UL;
}

LPWSTR expandEnvString(LPWSTR raw)
{
	DWORD len = ExpandEnvironmentStringsW(raw, NULL, 0);
	LPWSTR value = heapalloc(len * sizeof(wchar_t));
	ExpandEnvironmentStringsW(raw, value, len);
	return value;
}

void putenv(LPWSTR env)
{
	int loc = 0, length = lstrlenW(env);
	for (int i = 0; i < length; i++)
	{
		if (env[i] == L'=')
		{
			loc = i;
			break;
		}
	}
	if (!loc)
	{
		return;
	}
	if (loc == length)
	{
		return;
	}
	env[loc] = L'\0';
	SetEnvironmentVariableW(env, env + loc + 1);
	heapfree(env);
}

HANDLE hHeap;