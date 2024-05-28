@echo off
setlocal

set /p ARCH="Enter architecture (x86/x64): "

if "%ARCH%"=="x86" (
  REM x86 is ok
) else if "%ARCH%"=="x64" (
  REM x64 is ok
) else (
    echo Invalid value. Exiting the script.
    exit /b 1
)

REM Select variant
set /p VARIANT="Enter variant, release or debug (R/d): "

IF "%VARIANT%" == "d" (
  set VARIANT=Debug
  set SUFFIX=-d
  set PYDSUFFIX=_d
) ELSE (
  set VARIANT=Release
  set SUFFIX=
  set PYDSUFFIX=
)

echo Creating %ARCH% %VARIANT% bundle.

REM Cleanup output folder
rmdir /S /Q Windows_%ARCH%
mkdir Windows_%ARCH%

xcopy ..\_build_win_%ARCH%\externals\nih\src\%VARIANT%\_la_networkInterfaceHelper%PYDSUFFIX%.pyd .\Windows_%ARCH%\ /D /Y
xcopy ..\_build_win_%ARCH%\externals\nih\src\%VARIANT%\la_networkInterfaceHelper.py .\Windows_%ARCH%\ /D /Y

xcopy ..\_build_win_%ARCH%\src\%VARIANT%\_la_avdeccEntityModel%PYDSUFFIX%.pyd .\Windows_%ARCH%\ /D /Y
xcopy ..\_build_win_%ARCH%\src\%VARIANT%\avdeccEntityModel.py .\Windows_%ARCH%\ /D /Y
xcopy ..\_build_win_%ARCH%\src\%VARIANT%\_la_avdecc%PYDSUFFIX%.pyd .\Windows_%ARCH%\ /D /Y
xcopy ..\_build_win_%ARCH%\src\%VARIANT%\avdecc.py .\Windows_%ARCH%\ /D /Y
xcopy ..\_build_win_%ARCH%\src\%VARIANT%\la_avdecc_cxx%SUFFIX%.dll .\Windows_%ARCH%\ /D /Y

xcopy .\avdeccTypes.py .\Windows_%ARCH%\ /D /Y

REM Do postprocessing
cd Windows_%ARCH%
python ..\postprocess.py

PAUSE
