#!/usr/bin/env bash

LIB_TYPE=$1
SYSTEM_NAME=$(grep -Po '(?<=^ID=)\w*$' /etc/os-release)

if [[ "${LIB_TYPE}" == "shared" ]]; then
  BUILD_SHARED_LIB="on"
else
  BUILD_SHARED_LIB="off"
fi

mkdir -p /app/build
cd /app/build || exit 1

# Build the library.
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

# Copy installed library to the result directory.
BUILD_PATH=/app/xalwart.base-"${LIB_TYPE}"-linux
cd /usr/local || exit 1
mkdir -p "${BUILD_PATH}"/include
mkdir -p "${BUILD_PATH}"/lib
cd include/ || exit 1
cp -r xalwart.base "${BUILD_PATH}"/include
cd ../lib/ || exit 1
cp libxalwart.base* "${BUILD_PATH}"/lib
