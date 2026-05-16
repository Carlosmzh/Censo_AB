@echo off
echo ===============================================
echo COMPILANDO PROYECTO CENSO 2024
echo ===============================================
echo.

set CXX=g++
set CXXFLAGS=-std=c++17 -Wall -Wextra -I include
set SRC=src\*.cpp
set OUTPUT=build\app.exe

echo Compilando...
%CXX% %CXXFLAGS% -o %OUTPUT% %SRC%

if %errorlevel% equ 0 (
    echo.
    echo ===============================================
    echo COMPILACION EXITOSA!
    echo ===============================================
    echo Ejecutable: %OUTPUT%
    echo.
    echo Presione cualquier tecla para ejecutar...
    pause >nul
    %OUTPUT%
) else (
    echo.
    echo ===============================================
    echo ERROR EN LA COMPILACION
    echo ===============================================
    echo Por favor, revise los errores anteriores.
    echo.
    pause
)
