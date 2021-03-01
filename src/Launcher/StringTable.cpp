#include "StringTable.h"

#define LOADS(x) LoadStringW(hInstance, IDS_##x, (LPWSTR)&sz##x, 0)

void StringTableInit(HINSTANCE hInstance)
{
    LOADS();
}

#undef LOADS

LPWSTR szClassName;