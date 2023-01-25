@chcp 1251 >nul
@REM cls

echo off

FOR /D %%a in (./projects/*) do call ./scripts/cleantemp %%a