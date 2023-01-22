@chcp 1251 >nul
@cls
@echo off
FOR /D %%a in (./projects/*) do call ./scripts/man %%a