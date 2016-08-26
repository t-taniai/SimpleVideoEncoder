@echo off

set encoder="%~dp0\x64\Release\encoder.exe"

%encoder% -inputDir "%1" -fps 2.5 -fourcc H264

pause;