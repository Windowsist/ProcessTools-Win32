#include "StringTable.h"

#define LOADS(x) LoadStringW(hInstance, IDS_##x, (LPWSTR)&sz##x, 0)

void StringTableInit(HINSTANCE hInstance)
{
    LOADS(NeedArg);
    LOADS(NotStarted);
    LOADS(Program);
    LOADS(CmdLine);
    LOADS(Directory);
    LOADS(StartFailed);
    LOADS(SetEnvFailed);
    LOADS(Warning);
    LOADS(EnvName);
    LOADS(EnvValue);
}

#undef LOADS

LPWSTR szNeedArg;
LPWSTR szNotStarted;
LPWSTR szProgram;
LPWSTR szCmdLine;
LPWSTR szDirectory;
LPWSTR szStartFailed;
LPWSTR szSetEnvFailed;
LPWSTR szWarning;
LPWSTR szEnvName;
LPWSTR szEnvValue;