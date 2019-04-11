REM CALL "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\Tools\VsDevCmd.bat"
CALL "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\Tools\VsDevCmd.bat"
CALL "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" AMD64
link /LARGEADDRESSAWARE /MACHINE:X64 /SUBSYSTEM:WINDOWS  /ENTRY:start rep.obj "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.17134.0\um\x64\User32.Lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.17134.0\um\x64\Kernel32.Lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.17134.0\um\x64\Gdi32.lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.17134.0\um\x64\Ws2_32.lib"  /OUT:rep.exe
xcopy /Y /E rep.obj ..\..\..\lib