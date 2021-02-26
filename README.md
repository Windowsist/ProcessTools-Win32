# 进程工具
## 最后归档时间
2021/2/26
## 生成环境
1. Visual Studio Code
2. Cmake 3.19.4
3. MSVC v140 (19.00) (删除CRT)[防止依赖运行时(vcruntime140.dll,msvcp140.dll)]
4. Windows SDK 10.0.19041.0
5. WinDDK 7600.16385.1 (提取CRT,ATL71,MFC42)[可依赖系统自带dll(msvcrt.dll,msvcirt.dll,atl.dll,mfc42.dll)]
## 说明
只考虑64位
## 内容
1. exec
启动指定程序
2. exec_AsInvoker
强制以标准用户（普通权限）启动指定程序
3. exec_lite
启动指定程序（不显示任何信息，不修改工作目录）
4. Launcher
启动配置文件指定的程序
5. Launcher_Env
启动配置文件指定的程序（可指定环境变量）
6. ShellOpener
打开文件对话框（选择只读时可以循环打开）
7. ShowInvokeInfo
显示调用信息（命令行，环境变量）
