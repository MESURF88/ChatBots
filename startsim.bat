@echo off

set source=%CD%\container\work\
set destination=%CD%\container\work_client\

xcopy %source% %destination% /E /H /C /R /Q /Y
docker-compose up