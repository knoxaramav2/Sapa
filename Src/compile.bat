g++ -Wall Bio.cpp Launcher.cpp System.cpp -o Sapa.exe -L. -std=c++11
if errorlevel 1 goto err
exit
:err
echo Compile failed
pause