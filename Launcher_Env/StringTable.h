#pragma once

#include "pch.h"

#define STCONTENT         \
    CONTENT(CfgFile);     \
    CONTENT(Program);     \
    CONTENT(CmdLine);     \
    CONTENT(Directory);   \
    CONTENT(StartFailed); \
    CONTENT(Env);         \
    CONTENT(SetEnvFailed);

void StringTableInit(HINSTANCE hInstance);

#define CONTENT(x) extern LPWSTR sz##x

STCONTENT

#undef CONTENT
