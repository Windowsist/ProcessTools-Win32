#include <windows.h>

int
    WINAPI
    wWinMain(_In_ HINSTANCE hInstance,
             _In_opt_ HINSTANCE hPrevInstance,
             _In_ LPWSTR lpCmdLine,
             _In_ int nShowCmd)
{
    return !CreateProcessW(nullptr, lpCmdLine, nullptr, nullptr, FALSE, 0, nullptr, nullptr, &_STARTUPINFOW(), &_PROCESS_INFORMATION());
}