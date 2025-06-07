@echo off
:: Batch file to build the Game.sln solution

:: Step 1: Define paths
set SOLUTION_PATH=Game.sln
set MSBUILD_PATH="C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\MSBuild\Current\Bin\MSBuild.exe"
set CONFIGURATION=Debug
set PLATFORM=x64

:: Step 2: Check if MSBuild exists
if not exist %MSBUILD_PATH% (
	echo MSBuild not found at %MSBUILD_PATH%. Please check your installation.
	pause
	exit /b 1
)

:: Step 3: Build the solution 
echo Building solution: %SOLUTION_PATH%
echo Configuration: %CONFIGURATION%

%MSBUILD_PATH% %SOLUTION_PATH% ^
	/p:Configuration=%CONFIGURATION% ^
	/p:Platform=%PLATFORM% ^
	/t:Engine;Rogalique

:: Step 4: Check the build result
if %ERRORLEVEL% neq 0 (
	echo Build failed with errors.
	pause
	exit /b %ERRORLEVEL%
)

:: Step 5: Copy required DLL files
if exist "%CD%\SFML\SFML-2.5.1\bin\" (
	mkdir "%CD%\bin\%CONFIGURATION%\x64" 2>nul
	copy "%CD%\SFML\SFML-2.5.1\bin\*.dll" "%CD%\Rogalique\x64\%CONFIGURATION%\" >nul
	echo Copied SFML DLL files to output directory.
)

:: Step 6: Copy resource files
if exist "%CD%\Rogalique\Resources\" (
	mkdir "%CD%\bin\%CONFIGURATION%\x64\Resources" 2>nul
	xcopy /E /I /Y "%CD%\Rogalique\Resources\*" "%CD%\Rogalique\x64\%CONFIGURATION%\Resources\" >nul
	echo Copied resources files to output directory.
)

echo Build completed successfully.
pause