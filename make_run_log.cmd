@echo off
PATH="%CD%\mingw64;%CD%\mingw64\bin;%CD%\mingw64\lib\gcc\x86_64-w64-mingw32\10.1.0;%CD%\mingw64\include\c++\10.1.0;%CD%\mingw64\include;"
if not exist "objects" mkdir objects
%systemroot%\System32\xcopy.exe source objects /t /e
if exist "3dcollaborativegame.exe" del "3dcollaborativegame.exe"
"mingw64\bin\make"
if not exist "3dcollaborativegame.exe" goto compileError
if exist "3dcollaborativegame.exe" echo [32mCompilation Successful.[0m You may now close this window.
start /wait 3dcollaborativegame.exe
echo Program returned %errorlevel%
start C:\Windows\System32\notepad.exe /A program_log.txt
goto end

:compileError
echo [31mCompilation Failed.[0m Unsuccessful build. Check your code.
goto end


:end
pause