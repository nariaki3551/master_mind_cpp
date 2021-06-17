# master_mind_cpp
A solver of master_mind coded by c++.

<br>

## Install

git clone https://github.com/nariaki3551/master_mind_cpp.git

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
cd source && git clone https://github.com/p-ranav/argparse
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

<br>

## Usage

```bash
./build/src/mastermind nColors nPins [--no-dupulicate]
```

