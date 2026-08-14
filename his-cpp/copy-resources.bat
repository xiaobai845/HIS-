@rem Turn off command line output
@echo off
chcp 65001 > nul
setlocal enabledelayedexpansion

@rem Define color code
for /f %%a in ('echo prompt $E ^| cmd') do set "ESC=%%a"
set "RED=%ESC%[91m"
set "GREEN=%ESC%[3;92m"
set "YELLOW=%ESC%[4;93m"
set "BLUE=%ESC%[94m"
set "MAGENTA=%ESC%[95m"
set "CYAN=%ESC%[96m"
set "WHITE=%ESC%[97m"
set "RESET=%ESC%[0m"

@rem ===================Customized Parameters===================
echo --------------------------------
echo This tool is used to copy the necessary resources in the skeleton to the new module.
echo You need to enter the name of the new module (ie: the folder path where the new module is located)
set /p "newm=Enter the module name (eg: sample):"
echo --------------------------------
@rem ================================================

@rem Execute replication logic
md !newm!
xcopy .skeleton !newm! /S /Y
@rem Build some empty directories to ensure structural integrity
md !newm!\dao !newm!\service !newm!\domain\vo !newm!\domain\query !newm!\domain\dto
type nul > !newm!\zh-dict.yaml
type nul > !newm!\dao\.keep
type nul > !newm!\service\.keep
type nul > !newm!\domain\vo\.keep
type nul > !newm!\domain\query\.keep
type nul > !newm!\domain\dto\.keep
echo %GREEN%File copy completed.%RESET%

@rem Call powerShell check
call :CheckPowerShell
if %ps_available% equ 1 (
    echo PowerShell is available.
    @rem Replace CMakeLists.txt appName
    powershell -Command ^
        "$content = [System.IO.File]::ReadAllText('%newm%\CMakeLists.txt', [System.Text.Encoding]::UTF8);" ^
        "$newContent = $content -replace 'arch-skeleton', '%newm%';" ^
        "[System.IO.File]::WriteAllText('%newm%\CMakeLists.txt', $newContent, [System.Text.Encoding]::UTF8);"
    echo %GREEN%Replace CMakeLists.txt appName finish.%RESET%
    @rem Replace README.md root dir
    powershell -Command ^
        "$content = [System.IO.File]::ReadAllText('%newm%\README.md', [System.Text.Encoding]::UTF8);" ^
        "$newContent = $content -replace 'arch-skeleton', '%newm%';" ^
        "[System.IO.File]::WriteAllText('%newm%\README.md', $newContent, [System.Text.Encoding]::UTF8);"
    echo %GREEN%Replace README.md root dir finish.%RESET%
) else (
    echo %YELLOW%PowerShell is not available.%RESET%
    echo %YELLOW%Please Replace CMakeLists.txt appName by txt editor.%RESET%
)
pause
endlocal
exit /b

@rem Check powershell is available
:CheckPowerShell
set "ps_available=0"
where powershell >nul 2>&1
if %errorlevel% equ 0 set "ps_available=1"
if %ps_available% equ 1 (
    powershell -Command "exit 0" >nul 2>&1
    if not %errorlevel% equ 0 set "ps_available=0"
)
exit /b