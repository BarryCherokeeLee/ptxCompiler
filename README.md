# CUDAptxCompiler

## Introduction
a compiler supporting ptx converting to riscv vector extension

## Install

### Prerequisites

-Ubuntu 22.04
-LLVM 17.0.0rc
-CUDA 12.2

### Installation

1. Clone from git
    git clone git://10.75.136.169/CUDAptxCompiler.git 
    cd CUDAptxCompiler

2. Build ptxCompiler
    mkdir build && cd build
    cmake ..
    make

### Test case running
1. vector multiply add ptx kernel test.....
    ./bin/ptx_compiler ../test/vector_mul_add.ptx vector_mul_add.ll

