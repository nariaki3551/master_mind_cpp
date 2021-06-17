FROM ubuntu:20.04

ENV HOME /master_mind_cpp
WORKDIR ${HOME}

# install packages via apt  # aptを使って色々install
RUN apt update -y
RUN apt install -y tzdata
RUN apt install -y build-essential cmake vim git libpthread-stubs0-dev libgtest-dev

# copy local files into image
COPY . .

# build
RUN rm -rf build && mkdir build
RUN cd build && cmake .. && make
