# Zybo NEON Algorithms

This repository contains implementations of algorithms using NEON (Advanced SIMD) on the Zybo board. The project explores the efficiency of NEON intrinsics for various computational tasks.

## Table of Contents

- [Introduction](#introduction)
- [Operations](#operations)
- [Directory Structure](#directory-structure)
- [Getting Started](#getting-started)
- [Results and Analysis](#results-and-analysis)
- [Issues and Challenges](#issues-and-challenges)
- [Contributing](#contributing)
- [License](#license)

## Introduction

In this project, we leverage the NEON SIMD architecture extension to enhance the performance of algorithms on the Zybo board. The operations explored include timing analysis, array summation, matrix multiplication, and potentially edge detection.

## Operations

1. **Timing Analysis:** Measure the execution time of algorithms using the Xilinx library and XTime functions.

2. **Summation of an Array (NEON vs C):** Compare the efficiency of summing large arrays using traditional C and NEON intrinsics.

3. **Matrix Multiplication (NEON vs C):** Assess performance gains in matrix multiplication through NEON intrinsics.

## Directory Structure

- `sum_c.c`: C implementation for array summation.
- `neon.c`: NEON implementation for array summation.
- `main.c`: Main program to execute and measure the performance of implemented algorithms.
- `Makefile`: Makefile for building the project.
- `include/`: Directory for header files.
- `lib/`: Directory for libraries.
- `results/`: Directory to store result files.

## Getting Started

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/your-username/zybo-neon-algorithms.git
   cd zybo-neon-algorithms
   ```
