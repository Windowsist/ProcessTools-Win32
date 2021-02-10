cmake_minimum_required(VERSION 3.0.0)
project(exectools VERSION 0.1.0)

set(CMAKE_C_FLAGS_DEBUG "/MD /Zi /Ob0 /Od")
set(CMAKE_CXX_FLAGS_DEBUG "/MD /Zi /Ob0 /Od")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /GS-")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} /GS-")

add_executable(exec WIN32 exec/exec.rc exec/exec.cpp)
add_executable(exec_AsInvoker WIN32 exec_AsInvoker/exec_AsInvoker.rc exec_AsInvoker/exec_AsInvoker.cpp)
add_executable(Launcher WIN32 Launcher/Launcher.rc Launcher/Launcher.cpp)
add_executable(Launcher_Env WIN32 Launcher_Env/Launcher_Env.rc Launcher_Env/Launcher_Env.cpp)
add_executable(ShellOpener WIN32 ShellOpener/Resource.rc ShellOpener/main.cpp)
add_executable(ShowCommandLine WIN32 ShowCommandLine/ShowCommandLine.rc ShowCommandLine/main.cpp)
