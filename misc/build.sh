#!/usr/bin/env bash

SYSTEM_NAME=$1
LIB_TYPE=$2
CC_NAME=$3

if [[ "${CC_NAME}" == "gcc" ]]; then
  CXX_NAME="g++"
elif [[ "${CC_NAME}" == "clang" ]]; then
  CXX_NAME="clang++"
else
  echo "Compiler is not supported: ${CC_NAME}" && exit 1
fi

if [[ "${LIB_TYPE}" == "shared" ]]; then
  BUILD_SHARED_LIB="on"
else
  BUILD_SHARED_LIB="off"
fi

mkdir -p /app/build
cd /app/build || exit 1

# Build the library.
if [[ "${SYSTEM_NAME}" == "alpine"* ]]; then
  cmake -DCMAKE_C_COMPILER="${CC_NAME}" \
          -DCMAKE_CXX_COMPILER="${CXX_NAME}" \
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
BUILD_PATH=/app/xalwart.base-"${LIB_TYPE}"-"${SYSTEM_NAME}"
cd /usr/local || exit 1
mkdir -p "${BUILD_PATH}"/include
mkdir -p "${BUILD_PATH}"/lib
cd include/ || exit 1
cp -r xalwart.base "${BUILD_PATH}"/include
cd ../lib/ || exit 1
cp libxalwart.base* "${BUILD_PATH}"/lib
