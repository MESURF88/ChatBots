# # Create network first
# docker network create --subnet=172.15.1.0/24 qt-net
# # Build it
# docker build -t qsocket/server:qservertag .
# # Run it (server first) (NOTE: this needs WSL2 for windows)
# docker run -it --rm --privileged -e DISPLAY=host.docker.internal:0.0 -e LIBGL_ALWAYS_INDIRECT=0 -v /c/Users/hillk/Documents/ChatBattle/container/work:/mnt --workdir /mnt --name servercon qsocket/server:qservertag
# Pull base image.
FROM ubuntu:20.04

ENV DEBIAN_FRONTEND noninteractive
# Install.
RUN  apt-get update && \
	 apt-get install -y qt5-default && \
	 apt-get install -y build-essential && \
	 apt-get install -y qtdeclarative5-dev && \
	 apt-get install -y qml-module-qtquick-dialogs && \
	 apt-get install -y qml-module-qtquick-controls && \
	 apt-get install -y qml-module-qtquick-controls2 && \
	 apt-get install -y qml-module-qtquick-layouts && \
	 apt-get install -y qml-module-qtquick-window2 && \
	 apt-get install -y cmake && \
     apt-get install -y '^libxcb.*-dev' libx11-xcb-dev libglu1-mesa-dev libxrender-dev libxi-dev libxkbcommon-dev libxkbcommon-x11-dev && \
     apt-get install -y x11-apps

# Define default command.
CMD /bin/bash run_client.sh ${ipaddr}