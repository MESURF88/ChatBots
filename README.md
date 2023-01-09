# Intro
## NOTE: tested on Windows with Docker Desktop (Docker Engine v20+ and docker-compose v1.29.2, build 5becea4c)
## NOTE: add the mounted paths server_container/work and client_container/work to Docker Compose Resources
## Requires WSL2 for windows
## Testing isolated build environments that communicate between each other over TCP
## automated with docker-compose
## built with cmake, linux g++ compiler
## cross-platform c++ api using Qt
# 1.) Create network first
```powershell
docker network create --subnet=172.15.1.0/24 qt-net
```
# verify with:
```powershell
docker network ls 
```
# 2.) Build docker images
```powershell
docker-compose build
```

# 3.) Run X11 server using xlaunch.exe in C:\Program Files\VcXsrv and check disable access

# 4. ) Finally run the containers
## First the server is built and run, then client is built and run automatically
```powershell
startsim.bat
```
# The sim will only run once

# 5. ) close the containers
```powershell
shutdownsim.bat
```
## Have fun!