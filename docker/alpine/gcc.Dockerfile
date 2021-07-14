ARG alpine_version=3.13
ARG build_shared_lib=off

FROM alpine:$alpine_version

RUN echo "ipv6" >> /etc/modules

RUN apk update && apk upgrade

RUN apk add --update --no-cache \
    gcc \
    alpine-sdk \
    dpkg \
    cmake \
    ccache \
    git \
    valgrind

RUN git clone -q https://github.com/google/googletest.git /googletest && \
    mkdir -p /googletest/build && \
    cd /googletest/build && \
    cmake -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc .. && \
    make && make install && \
    cd / && rm -rf /googletest

RUN ldconfig /etc/ld.so.conf.d

COPY . .

RUN mkdir build && \
    cd build && \
    cmake -DCMAKE_CXX_COMPILER=g++ \
          -DCMAKE_C_COMPILER=gcc \
          -DCMAKE_BUILD_TYPE=Debug \
          -DBUILD_SHARED_LIB=$build_shared_lib \
          .. && \
    make unittests-all

CMD valgrind --leak-check=full $APP_HOME/build/tests/unittests-all
