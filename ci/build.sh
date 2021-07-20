#!/usr/bin/env bash

SYSTEM_NAME=$1
CC_NAME=$2

if [[ "${CC_NAME}" == "gcc" ]]; then
  CXX_NAME="g++"
elif [[ "${CC_NAME}" == "clang" ]]; then
  CXX_NAME="clang++"
else
  echo "Compiler is not supported: ${CC_NAME}" && exit 1
fi

mkdir -p /app/build
cd /app/build || exit 1

# Build the library.
if [[ "${SYSTEM_NAME}" == "alpine"* ]]; then
  cmake -DCMAKE_C_COMPILER="${CC_NAME}" \
          -DCMAKE_CXX_COMPILER="${CXX_NAME}" \
          -DCMAKE_BUILD_TYPE=Release \
          -DBUILD_SHARED_LIBS=ON \
          ..
elif [[ "${SYSTEM_NAME}" == "ubuntu"* ]]; then
  cmake -DCMAKE_BUILD_TYPE=Release \
        -DBUILD_SHARED_LIBS=ON \
        ..
else
  echo "System is not supported: ${SYSTEM_NAME}" && exit 1
fi
make xalwart.base && make install

# Copy installed library to the result directory.
BUILD_PATH=/app/xalwart.base-"${SYSTEM_NAME}"
cd /usr/local || exit 1
mkdir -p "${BUILD_PATH}"/include
mkdir -p "${BUILD_PATH}"/lib
cd include/ || exit 1
cp -r xalwart.base "${BUILD_PATH}"/include
cd ../lib/ || exit 1
cp libxalwart.base* "${BUILD_PATH}"/lib
