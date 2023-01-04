# Intro
## NOTE: tested on Windows with Docker Desktop (Docker Engine v20+ and docker-compose v1.29.2, build 5becea4c)
## NOTE: add the mounted paths server_container/work and client_container/work to Docker Compose Resources
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
# 3. ) Finally run the containers
## First the server is built and run, then client is built and run automatically
```powershell
docker-compose up
```
```powershell
docker-compose down
```
## Review log folder in server_container directory after the containers exit