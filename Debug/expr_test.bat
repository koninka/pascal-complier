@echo off
echo Buffer > test.res
SET k = 1
for %%i in (simple_expressions_test\*.in) do %1 -s %%i
del test.res