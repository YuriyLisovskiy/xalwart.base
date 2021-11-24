## xalwart.base
[![c++](https://img.shields.io/badge/c%2B%2B-20-6c85cf)](https://isocpp.org/)
[![cmake](https://img.shields.io/badge/cmake-%3E=3.12-success)](https://cmake.org/)
[![alpine](https://img.shields.io/badge/Alpine_Linux-0D597F?style=flat&logo=alpine-linux&logoColor=white)](https://alpinelinux.org/)
[![ubuntu](https://img.shields.io/badge/Ubuntu-E95420?style=flat&logo=ubuntu&logoColor=white)](https://ubuntu.com/)
[![macOS](https://img.shields.io/badge/macOS-343D46?style=flat&logo=apple&logoColor=F0F0F0)](https://www.apple.com/macos)

| @ | Status |
|---|---|
| Dev branch: | [![Tests](https://github.com/YuriyLisovskiy/xalwart.base/actions/workflows/build_and_test.yml/badge.svg?branch=dev)](https://github.com/YuriyLisovskiy/xalwart.base/actions/workflows/build_and_test.yml?query=branch%3Adev) |
| Master branch: | [![Tests](https://github.com/YuriyLisovskiy/xalwart.base/actions/workflows/build_and_test.yml/badge.svg?branch=master)](https://github.com/YuriyLisovskiy/xalwart.base/actions/workflows/build_and_test.yml?query=branch%3Amaster) |

> ATTENTION: this project still has [issues](https://github.com/YuriyLisovskiy/xalwart.base/issues),
> requires testing, documentation, and is not stable.

## Requirements
The following compilers are tested with the CI system, and are known to work on:

Alpine Linux and Ubuntu:
* g++ 10 or later
* clang++ 10 or later

macOS:
* clang++ 12 or later

To build the library from source CMake 3.12 or later is required.

## Compile from Source
* `BUILD_SHARED_LIBS`: build shared or static library (`ON` by default).
* `LIBRARY_ROOT`: installation directory root (`/usr/local` by default).
* `LIBRARY_INCLUDE_DIR`: include installation directory (`${LIBRARY_ROOT}/include` by default).
* `LIBRARY_LINK_DIR`: library installation directory (`${LIBRARY_ROOT}/lib` by default).
```bash
git clone https://github.com/YuriyLisovskiy/xalwart.base.git
cd xalwart.base
mkdir build && cd build
cmake -D CMAKE_BUILD_TYPE=Release ..
make && make install
```
> Temporary it is necessary to build a shared library instead of static because
> the last one is not working properly causing undefined reference errors when
> using [xalwart](https://github.com/YuriyLisovskiy/xalwart) library.

## Testing
```bash
mkdir build && cd build
cmake -D CMAKE_BUILD_TYPE=Debug \
      -D XW_CONFIGURE_TESTS=ON \
      ..
make unittests-all
valgrind --leak-check=full ./tests/unittests-all
```
