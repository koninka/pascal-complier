@echo off
del *.comp
del *.out
for %%I in (*.asm) do (ml /c /coff %%I) && (link %%~nI.obj) && (del %%~nI.comp) && (type NUL > %%~nI.comp) && (%%~nI.exe > %%~nI.comp)
for %%I in (*.in) do (fpc -S2 %%I) && (%%~nI.exe > %%~nI.out)
for %%I in (*.comp) do fc %%~nI.out %%I > log.txt || if errorlevel 0 (
   echo %%I FAIL
) else echo %%I OK
del *.exe
del *.obj
del *.o
del log.txt