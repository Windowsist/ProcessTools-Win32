#pragma once

#include "pch.h"

#define STCONTENT          \
    CONTENT(NeedArg);      \
    CONTENT(NotStarted);   \
    CONTENT(Program);      \
    CONTENT(CmdLine);      \
    CONTENT(Directory);    \
    CONTENT(StartFailed);  \
    CONTENT(SetEnvFailed); \
    CONTENT(Warning);      \
    CONTENT(EnvName);      \
    CONTENT(EnvValue);

void StringTableInit(HINSTANCE hInstance);

#define CONTENT(x) extern LPWSTR sz##x

STCONTENT

#undef CONTENT
