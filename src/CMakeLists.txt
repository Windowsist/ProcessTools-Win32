cmake_minimum_required(VERSION 3.0.0)
project(exectools VERSION 0.1.0)

string(APPEND CMAKE_EXE_LINKER_FLAGS " /MANIFEST:NO")

add_executable(exec WIN32 exec/Resource.rc exec/main.cpp)
add_executable(exec_AsInvoker WIN32 exec_AsInvoker/Resource.rc exec_AsInvoker/main.cpp)
add_executable(exec_lite WIN32 exec_lite/main.cpp)
add_executable(Launcher WIN32 Launcher/Resource.rc Launcher/main.cpp)
add_executable(Launcher_Env WIN32 Launcher_Env/Resource.rc Launcher_Env/main.cpp)
add_executable(ShellOpener WIN32 ShellOpener/Resource.rc ShellOpener/main.cpp)
add_executable(ShowInvokeInfo WIN32 ShowInvokeInfo/Resource.rc ShowInvokeInfo/main.cpp)
