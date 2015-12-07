@echo off
cls
g++ -Wall Launcher.cpp Bio.cpp System.cpp Sim.cpp -o Sapa.exe -L. -std=c++11
@if errorlevel 1 goto err
@echo Compile success
@goto cnt
:err
@echo Compile failed
:cnt
@pause