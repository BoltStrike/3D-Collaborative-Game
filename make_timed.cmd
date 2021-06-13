@echo off
set start=%time%
PATH="%CD%\mingw64;%CD%\mingw64\bin;%CD%\mingw64\lib\gcc\x86_64-w64-mingw32\10.1.0;%CD%\mingw64\include\c++\10.1.0;%CD%\mingw64\include;"
if not exist "objects" mkdir objects
%systemroot%\System32\xcopy.exe source objects /t /e
if exist "3dcollaborativegame.exe" del "3dcollaborativegame.exe"
"mingw64\bin\make"
if not exist "3dcollaborativegame.exe" echo [31mCompilation Failed.[0m Unsuccessful build. Check your code. 
if exist "3dcollaborativegame.exe" echo [32mCompilation Successful.[0m You may now close this window.
set end=%time%
set /a deltaT=(360000*(%end:~0,2%-%start:~0,2%))+(6000*(%end:~3,2%-%start:~3,2%))+(100*(%end:~6,2%-%start:~6,2%))+%end:~9,2%-%start:~9,2%
echo Time taken:
set /a hrs=%deltaT%/360000
echo hrs: %hrs%
set /a deltaT-=%hrs%*360000
set /a min=%deltaT%/6000
echo min: %min%
set /a deltaT-=%min%*6000
set /a sec=%deltaT%/100
echo sec: %sec%
set /a deltaT-=%sec%*100
echo cs: %deltaT%
pause
