@echo off

if /i "%1" equ "clean" (
	del *.obj *.exe *.pdb>nul
	exit /b 0
)

where /q cl || (
	echo ERROR: MSVC could not be found
	exit /b 1
)

set msvc_flags=/nologo /W3 /Fe:neuclid.exe /Zi /D NEUCLID_SYSTEM_WINDOWS
set link_flags=/incremental:no /opt:icf,ref
set lib_files=user32.lib
call cl neuclid.cpp %msvc_flags% /link %link_flags% %lib_files%
