# ptxKompilierer

## Introduction
a compiler supporting ptx converting to riscv vector extension

## Install

### Prerequisites

-Ubuntu 22.04
-LLVM 17.0.0rc
-CUDA 12.2

### Installation

1. Clone from git
    clone project
    cd ptxKompilierer

2. Build ptxKompilierer
    mkdir build && cd build
    cmake ..
    make

### Test case running
1. vector multiply add ptx kernel test.....
    ./bin/ptx_compiler ../test/vector_mul_add.ptx vector_mul_add.ll

