## xalwart.base
[![c++](https://img.shields.io/badge/c%2B%2B-20-6c85cf)](https://isocpp.org/)
[![cmake](https://img.shields.io/badge/cmake-%3E=3.12-success)](https://cmake.org/)
[![alpine](https://img.shields.io/badge/Alpine_Linux-0D597F?style=flat&logo=alpine-linux&logoColor=white)](https://alpinelinux.org/)
[![ubuntu](https://img.shields.io/badge/Ubuntu-E95420?style=flat&logo=ubuntu&logoColor=white)](https://ubuntu.com/)
[![macOS](https://img.shields.io/badge/macOS-343D46?style=flat&logo=apple&logoColor=F0F0F0)](https://www.apple.com/macos)

## Build Status
| @ | Build |
|---|---|
| Dev branch: | [![CI](https://github.com/YuriyLisovskiy/xalwart.base/actions/workflows/ci.yml/badge.svg?branch=dev)](https://github.com/YuriyLisovskiy/xalwart.base/actions/workflows/ci.yml?query=branch%3Adev) |
| Master branch: | [![CI](https://github.com/YuriyLisovskiy/xalwart.base/actions/workflows/ci.yml/badge.svg?branch=master)](https://github.com/YuriyLisovskiy/xalwart.base/actions/workflows/ci.yml?query=branch%3Amaster) |

## Requirements
The following compilers are tested with the CI system, and are known to work on:

Alpine Linux and Ubuntu:
* g++ 10 or later
* clang++ 10 or later

macOS:
* clang++ 12 or later

To build the library from source CMake 3.12 or later is required.

## Compile from Source
* `BUILD_SHARED_LIBS` means to build a shared or static library (`ON` by default).
```bash
git clone https://github.com/YuriyLisovskiy/xalwart.base.git
cd xalwart.base
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=Release ..
make
sudo make install
```
> Temporary it is necessary to build a shared library instead of static because
> the last one is not working properly causing undefined reference errors when
> using [xalwart](https://github.com/YuriyLisovskiy/xalwart) library.

## Testing
```bash
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=Debug \
      -D XW_BUILD_TESTS=ON \
      ..
make unittests-all
valgrind --leak-check=full ./tests/unittests-all
```
