[English]
Warning: Only Support RJ45, not support WIFI/GPRS/4G, if you want to read tag actively, you must use ReaderSoft to set interface to RJ45, and set WorkMode in ActiveMode. The IP and port is Reader's localIP and Port.
If you want  execute C++ Version,  you need setup Microsoft Visual C++ 2008 Redistributable X86 or X64.

After you use Open function to connect Reader, do not need check disconnect status, SDK will Auto connect if RJ45 broken or disconnect.

[Chinese]
提示：该代码仅适用于网口，不适用于WIFI/GPRS/4G。如果想要主动读卡，请用读卡器软件设置上传接口为RJ45，同时设置工作模式为 主动模式。代码中的IP 及 Port 是读卡器的本地IP及端口号。
如果要打开C++版本的程序，请先安装Microsoft Visual C++ 2008 Redistributable X86 或者 X64 版本.

调用Open函数打开后，不需要检测网络状态，当网络断开或者重连时，SDK会自动重连网络。

