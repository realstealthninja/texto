FROM gitpod/workspace-full-vnc

RUN sudo apt-get update \
    && sudo apt-get install ninja-build \
    && sudo apt-get install libopencv-dev \
    && sudo apt-get install cmake
