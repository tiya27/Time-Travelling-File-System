@echo off
:: Compile the Time Travelling File System project (Windows)
g++ -std=c++17 -Wall -O2 main.cpp -o ttfs.exe

if %errorlevel% neq 0 (
    echo Compilation failed!
    exit /b %errorlevel%
)

echo Compilation successful. Run ttfs.exe to start.