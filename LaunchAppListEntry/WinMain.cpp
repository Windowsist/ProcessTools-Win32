#include "pch.h"

using namespace winrt;
using namespace Windows::Foundation::Collections;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;

int
#if defined(_M_CEE_PURE)
__clrcall
#else
WINAPI
#endif
wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE,
	_In_ LPWSTR,
	_In_ int
)
{
	init_apartment(apartment_type::single_threaded);
	wchar_t pathmdfn[260], id[116];
	::GetModuleFileNameW(hInstance, pathmdfn, 260);
	::lstrcpyW(pathmdfn + ::lstrlenW(pathmdfn) - 3, L"ini");
	::GetPrivateProfileStringW(L"LaunchAppListEntry", L"Id", nullptr, id, 116, pathmdfn);
	auto hid = hstring(id);
	auto entries = Package::Current().GetAppListEntries();
	bool found = false;
	auto info = std::wstring(L"ConfigFile:\r\n");
	info.append(pathmdfn);
	info.append(L"\r\n\r\nAppListEntries in current Package:\r\n");
	for (uint32_t i = 0U, size = entries.Size(); i < size; i++)
	{
		auto entry = entries.GetAt(i);
		auto curhid = entry.AppUserModelId();
		if (curhid == hid)
		{
			entry.LaunchAsync().get();
			found = true;
			break;
		}
		info.append(curhid);
		info.append(L";\r\n");
	}
	if (!found)
	{
		info.append(L"\r\nAppListEntry required:\r\n");
		info.append(hid);
		::MessageBoxW(::GetDesktopWindow(), info.c_str(), L"StartFailed", MB_ICONERROR);
	}
	return 0;
}
