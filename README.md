## xalwart.core

[![gcc](https://github.com/YuriyLisovskiy/xalwart.core/actions/workflows/tests-gcc.yml/badge.svg)](https://github.com/YuriyLisovskiy/xalwart.core/actions/workflows/tests-gcc.yml)
[![clang](https://github.com/YuriyLisovskiy/xalwart.core/actions/workflows/tests-clang.yml/badge.svg)](https://github.com/YuriyLisovskiy/xalwart.core/actions/workflows/tests-clang.yml)

### Requirements

- C++ compiler:
    - `g++`: v10 or later.
    - `clang++`: v10 or later.
- CMake: `3.12` or later.

### Build and Install
```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make && sudo make install
```

### Testing

Use valgrind to check for memory leaks:
```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug .. && make
valgrind --leak-check=full ./tests/unittests-all
```
