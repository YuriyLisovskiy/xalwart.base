## xalwart.core

![Continuous Integration](https://github.com/YuriyLisovskiy/xalwart.core/workflows/Continuous%20Integration/badge.svg)

### Requirements

C++ compiler minimum version:
* Ubuntu: g++ v7.5.0
* Microsoft C/C++: Visual Studio 2019 v16.6

### Testing

Use valgrind to check for memory leaks:
```
$ valgrind --leak-check=full ./your-executable
```
