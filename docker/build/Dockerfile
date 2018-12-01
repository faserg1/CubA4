FROM debian:latest

RUN apt-get update
RUN apt-get install -y python3 gcc g++ make xorg-dev libx11-dev

RUN mkdir -p /tmp/build/
ADD https://dl.bintray.com/boostorg/release/1.68.0/source/boost_1_68_0.tar.gz /tmp/build/
ADD https://github.com/Kitware/CMake/releases/download/v3.13.1/cmake-3.13.1.tar.gz /tmp/build/
ADD https://www.libsdl.org/release/SDL2-2.0.9.tar.gz /tmp/build/
ADD https://sdk.lunarg.com/sdk/download/1.1.92.1/linux/vulkansdk-linux-x86_64-1.1.92.1.tar.gz /opt/vulkansdk

WORKDIR /tmp/build/boost_1_68_0
RUN ./bootstrap.sh
RUN ./bjam -j4 cxxflags=-fPIC cflags=-fPIC -a install

WORKDIR /tmp/build/cmake-3.13.0
RUN ./bootstrap
RUN make -j 4
RUN make install

WORKDIR /tmp/build/SDL2-2.0.9
RUN mkdir build
WORKDIR /tmp/build/SDL2-2.0.9/build
RUN ../configure
RUN make -j 4
RUN make install

ENV VULKAN_SDK="/opt/vulkansdk/1.1.92.0/"

WORKDIR /
 
RUN rm -rf /tmp/build
