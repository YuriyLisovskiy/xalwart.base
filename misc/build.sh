#!/usr/bin/env bash

SYSTEM_NAME=$1
LIB_VERSION=$2
LIB_TYPE=$3

if [[ "${LIB_TYPE}" == "shared" ]]; then
  BUILD_SHARED_LIB="on"
else
  BUILD_SHARED_LIB="off"
fi

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

BUILD_PATH=/app/xalwart.base-linux-"${LIB_VERSION}"-"${LIB_TYPE}"

cd /usr/local || exit 1
mkdir -p "${BUILD_PATH}"/include
mkdir -p "${BUILD_PATH}"/lib
cd include/ || exit 1
cp xalwart.base "${BUILD_PATH}"/include
cd ../lib/ || exit 1
cp libxalwart.base* "${BUILD_PATH}"/lib
