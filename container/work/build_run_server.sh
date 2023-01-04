#!/bin/bash
if [ -d build ]
then
	rm -rf build
fi
SECONDS=0
# do some work
mkdir build
cd build
cmake ..
make
cd ..
duration=$SECONDS
echo "$(($duration / 60)) minutes and $(($duration % 60)) seconds elapsed."
exec ./target/bin/ChatBots;
