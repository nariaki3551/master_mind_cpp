# master_mind_cpp
A solver of master_mind coded by c++.

<br>

## Install

```sh
git clone https://github.com/nariaki3551/master_mind_cpp.git
```

<br>

## Setting

### Docker

run

```
docker build -t master_mind .
```

, then

```
docker run -v $(pwd):/mnt -it master_mind
```

### By yourself

```
mkdir source
cd source
git clone https://github.com/p-ranav/argparse
git clone https://github.com/prakhar1989/progress-cpp.git
```

and, install packages, for example, in the case on ubuntu,

```
apt update -y && apt-get update -y
apt-get install -y tzdata
apt-get install -y build-essential cmake vim git valgrind screen \
                   libpthread-stubs0-dev libgtest-dev libomp-dev \
                   libopenmpi-dev
```

<br>

## Build

### CMake

```bash
mkdir build
cd build
cmake ..
make
```
The binary will be created as `bin/mastermind`.

If you use MPI parallelization, then
```
cmake .. USE_MPI=ON
```

<br>

## Usage

```bash
$ ./bin/mastermind
Usage: master mind [options] num_colors num_pins 

Positional arguments:
num_colors     	number of colors
num_pins       	number of pins

Optional arguments:
-h --help      	shows help message and exits
-v --version   	prints version information and exits
--policy       	type of policy: random, minmax, exp_minmax, entropy [default: "random"]
--no_duplicate 	secret codes donot have color duplication [default: false]
--test         	run test mode [default: false]
```

