@echo off
docker-compose build
docker network create --subnet=172.15.1.0/24 qt-net