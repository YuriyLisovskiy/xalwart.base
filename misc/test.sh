#!/usr/bin/env bash

LIB_TYPE=$1
SYSTEM_NAME=$(grep -Po '(?<=^ID=)\w*$' /etc/os-release)

# Install the library.
cd /app/xalwart.base-"${LIB_TYPE}"-linux/include || exit 1
cp -r xalwart.base /usr/local/include
cd ../lib || exit 1
cp libxalwart.base* /usr/local/lib

# Build tests.
mkdir -p /app/build
cd /app/build || exit 1
if [[ "${SYSTEM_NAME}" == "alpine"* ]]; then
  cmake -DCMAKE_C_COMPILER=cc \
          -DCMAKE_CXX_COMPILER=c++ \
          -DCMAKE_BUILD_TYPE=Release \
          -DBUILD_LIB=off \
          -DBUILD_TESTS=on \
          ..
elif [[ "${SYSTEM_NAME}" == "ubuntu"* ]]; then
  cmake -DCMAKE_BUILD_TYPE=Release \
        -DBUILD_LIB=off \
        -DBUILD_TESTS=on \
        ..
else
  echo "System is not supported: ${SYSTEM_NAME}" && exit 1
fi
make unittests-all

# Run tests using valgrind.
valgrind --leak-check=full ./tests/unittests-all
