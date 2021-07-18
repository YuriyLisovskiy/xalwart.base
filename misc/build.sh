#!/usr/bin/env bash

SYSTEM_NAME=$1
LIB_VERSION=$2
BUILD_SHARED_LIB=$3

mkdir -p /app/build
cd /app/build || exit 1
if [[ "${SYSTEM_NAME}" == "alpine"* ]]; then
  cmake -DCMAKE_C_COMPILER=cc \
          -DCMAKE_CXX_COMPILER=c++ \
          -DCMAKE_BUILD_TYPE=Release \
          -DBUILD_SHARED_LIB="${BUILD_SHARED_LIB}" \
          ..
elif [[ "${SYSTEM_NAME}" == "ubuntu"* ]]; then
  cmake -DCMAKE_BUILD_TYPE=Release \
        -DBUILD_SHARED_LIB="${BUILD_SHARED_LIB}" \
        ..
else
  echo "System is not supported: ${SYSTEM_NAME}" && exit 1
fi
make xalwart.base && make install
cd /usr/local || exit 1
tar -cvzf /app/xalwart.base-linux-"${LIB_VERSION}".tar.gz lib/libxalwart.base* include/xalwart.base
