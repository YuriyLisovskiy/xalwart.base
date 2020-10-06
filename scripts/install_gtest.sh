#!/bin/bash

UBUNTU_VERSION=$(lsb_release -r -s)

sudo apt-get install libgtest-dev

if [ "$UBUNTU_VERSION" = "16.04" ]; then
  cd /usr/src/googletest/googletest || exit
else
  cd /usr/src/gtest || exit
fi

sudo mkdir gtest-build
cd gtest-build || exit
sudo cmake ..
sudo make
sudo cp libgtest* /usr/lib/
cd ..
sudo mkdir /usr/local/lib/googletest
sudo ln -s /usr/lib/libgtest.a /usr/local/lib/googletest/libgtest.a
sudo ln -s /usr/lib/libgtest_main.a /usr/local/lib/googletest/libgtest_main.a
