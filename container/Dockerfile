# # Create network first
# docker network create --subnet=172.15.1.0/24 qt-net
# # Build it
# docker build -t hill/server .
# # Run it (server first)
# docker run -t -v /c/Users/hillk/Desktop/Tutorials/Docker_socket_test/server_container/work:/mnt --workdir /mnt --network=qt-net --ip 172.15.1.20 --name servercon --rm hill/server
#
# docker run -t -v /tmp/.X11-unix:/tmp/.X11-unix -v /c/Users/hillk/Documents/ChatBattle/container/work:/mnt --workdir /mnt -e DISPLAY -e WAYLAND_DISPLAY -e XDG_RUNTIME_DIR -e PULSE_SERVER --network=qt-net --ip 172.15.1.20 --name servercon --rm hill/server
#
# Pull base image.
FROM ubuntu:20.04

# Install.
RUN  apt-get update && \
	 apt-get install -y qt5-default && \
	 apt-get install -y build-essential && \
	 apt-get install -y qtdeclarative5-dev && \
	 apt-get install -y cmake && \
	 apt-get install -y firefox

# Define default command.
CMD ["firefox"] #["/bin/bash"] #,"build_run_server.sh"]