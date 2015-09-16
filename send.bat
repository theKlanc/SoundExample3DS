@echo off
for %%* in (.) do set ProjectName=%%~n*
3dslink %ProjectName%.3dsx