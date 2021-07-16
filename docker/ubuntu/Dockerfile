FROM xalwart/gtest:1.11.0-{{ cc }}-{{ compiler_version }}-ubuntu-{{ os_version }}

ARG build_shared_lib=off

COPY . .

RUN mkdir build && \
    cd build && \
    cmake -DCMAKE_BUILD_TYPE=Debug \
          -DBUILD_SHARED_LIB=$build_shared_lib \
          .. && \
    make unittests-all

CMD valgrind --leak-check=full $APP_HOME/build/tests/unittests-all
