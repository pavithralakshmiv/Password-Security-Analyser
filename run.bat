@echo off
setlocal

if not exist build mkdir build

echo Building Password Security Analyzer...
g++ cpp\main.cpp cpp\PasswordAnalyzer.cpp -std=c++17 -o build\password_analyzer.exe

if errorlevel 1 (
    echo.
    echo C++ build failed.
    pause
    exit /b 1
)

echo.
echo Starting analyzer...
build\password_analyzer.exe

if errorlevel 1 (
    echo.
    echo Analyzer stopped.
    pause
    exit /b 1
)

echo.
echo Running Python analysis...
python python\analyzer.py

echo.
echo Creating visual report...
python python\report.py

echo.
echo ========================================
echo Project completed successfully.
echo Check the output folder for reports.
echo ========================================
pause
