md build 1>nul 2>nul

cd build



set QTDIR571=C:\qt-571-static-vs2015-xp
@set PATH=D:\nginxstack\cmake\bin;%PATH%


REM Set up \Microsoft Visual Studio 2015, where <arch> is amd64, x86, etc.  
CALL "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x86
  
REM ********** Update include & lib to support xp win sdk 7.1A **********  
@SET PATH=C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Bin;%PATH%
SET INCLUDE=C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Include;%INCLUDE%
SET LIB=C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Lib;%LIB%
SET CL=/Zc:threadSafeInit- /D_USING_V110_SDK71_;%CL%

cmake -G "Visual Studio 14 2015" -T v140_xp ..



cd /d "%~dp0"
