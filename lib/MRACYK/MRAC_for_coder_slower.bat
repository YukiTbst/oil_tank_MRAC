

call  "\\YkPC\D$\program files\matlab\bin\win64\checkMATLABRootForDriveMap.exe" "\\YkPC\D$\program files\matlab"  > mlEnv.txt
for /f %%a in (mlEnv.txt) do set "%%a"\n
cd .

if "%1"=="" ("D:\program files\matlab\bin\win64\gmake" MATLAB_ROOT=%MATLAB_ROOT% ALT_MATLAB_ROOT=%ALT_MATLAB_ROOT% MATLAB_BIN=%MATLAB_BIN% ALT_MATLAB_BIN=%ALT_MATLAB_BIN%  -f wrapper.mk all) else ("D:\program files\matlab\bin\win64\gmake" MATLAB_ROOT=%MATLAB_ROOT% ALT_MATLAB_ROOT=%ALT_MATLAB_ROOT% MATLAB_BIN=%MATLAB_BIN% ALT_MATLAB_BIN=%ALT_MATLAB_BIN%  -f wrapper.mk %1)
@if errorlevel 1 goto error_exit

exit /B 0

:error_exit
echo The make command returned an error of %errorlevel%
exit /B 1