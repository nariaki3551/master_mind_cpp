FROM ubuntu:20.04

ENV HOME /master_mind_cpp
WORKDIR ${HOME}

# install packages via apt
RUN apt update -y && apt-get update -y
RUN apt-get install -y tzdata
RUN apt-get install -y build-essential cmake vim git valgrind screen \
                       libpthread-stubs0-dev libgtest-dev libomp-dev \
                       libopenmpi-dev

# copy local files into image
COPY . .

# install and build third-party libraries
RUN mkdir source -p && rm -rf source/*
# argparse
RUN cd source && git clone https://github.com/p-ranav/argparse.git
RUN cd source && git clone https://github.com/prakhar1989/progress-cpp.git

# build
ARG USE_MPI=OFF
ARG j=1
RUN rm -rf build && mkdir build
RUN cd build && cmake .. -DUSE_MPI=${USE_MPI} && make -j ${j}
