# ESP OSQP Benchmarking
[OSQP](https://osqp.org/) is an open-source, efficient, and robust numerical optimization package for solving convex quadratic programs. 

This repository is an example of how to implement OSQP on an embedded controller for model predictive control (MPC). Four sets of hardware were benchmarked:
1. ESP32 (microcontroller)
2. Raspberry Pi 3B (soc)
3. Intel i5 (desktop)
4. Intel i7 (laptop)

## Generating New MPC Code
1. MPC problem is designed in a high level language (MATLAB or Python). For multiple MPC examples, see [kirkrudolph/osqp-python](https://github.com/kirkrudolph/osqp-python). The python interface is capable of running a closed-loop simulation with the MPC controller as well as generating a solver in c code for the specific problem.
2. Replace the `components/Configure`, `components/include`, and `components/src` python generated files with updated MPC problem (don't replace the `CMakeLists.txt` file).
3. Build the c code ESP-IDF project with `idf.py build` for the embedded microcontroller.

## OSQP Benchmarking on ESP32 Embedded Microcontroller

1. The embedded results were verified to be acurate. The [ESP32 Consol Output](image/esp32_output.png) shows the microcontroller's output from building this repository and flashing it to an ESP32. It was verified to be the same result as the [MacOS Consol Output](image/mac_output.png). I've also included an image of the [compiled static library's size requirements](image/esp32_size.png)

2. Multiple systems were evaluated on an `ESP32` microcontroller. The time / solve was averaged over 10 solves. The optimizer (usually) took 25 iterations / solve. The variables tested and resulting performance statistics are summarized in the following table.

| CPU Freq (MHz) | Precision  | Compiler Optimization | States / Actuators (#) | Horizon (#) | Variables (n) | Constraints (m) | nnz(P) + nnz(A) | Time / solve (ms) | OSQP Size (Byes) |
|:--------------:|:----------:|:---------------------:|:----------------------:|:-----------:|:-------------:|:---------------:|:---------------:|:-----------------:|:-----------------:|
|       160      |   DOUBLE   |      -O2 (Perf)       |         12 / 4         |     10      |      172      |       304       |       1161      |      235.0        |       173,908     |
|       240      |   DOUBLE   |      -Og (Debug)      |         12 / 4         |     10      |      172      |       304       |       1161      |      172.8        |       173,372     |
|       240      |   DOUBLE   |      -O2 (Perf)       |         12 / 4         |     10      |      172      |       304       |       1161      |      156.7        |       173,908     |
|       240      |   FLOAT    |      -Og (Debug)      |         12 / 4         |     10      |      172      |       304       |       1161      |      29.84        |       112,231     |
|       240      |   FLOAT    |      -O2 (Perf)       |         12 / 4         |     10      |      172      |       304       |       1161      |      13.26        |       112,567     |
|       240      |   FLOAT    |      -O2 (Perf)       |          9 / 4         |     10      |      139      |       238       |        842      |      9.699        |        86,147     |
|       240      |   FLOAT    |      -O2 (Perf)       |          2 / 3         |     10      |       52      |        74       |        258      |      2.770        |        22,801     |
|       240      |   FLOAT    |      -O2 (Perf)       |          2 / 3         |     50      |      252      |       354       |       1258      |      17.60        |        72,724     |

## Discusion

The order of impactful variables on the computational performance for the `ESP32` microcontroller appears to be:
1. Using `Single Precision` instead of `Double Precision`
2. CPU Frequncy
3. Compiler Optimization
4. "Size" of the problem (number of states, actuators, horizon, constraints, etc.) appears to fairly linearly increase execution speed.

Notable results:
1. In particular, a sub 3ms MPC requiring ~22kB of flash for a small dynamic system is very encouraging. I could see this running at a 5ms to 10ms rate (100Hz to 200Hz) on this microcontroller.
2. A sub 15ms MPC requiring ~112kB of flash for a higher order system is also impressive. I could see this running at a 20ms to 40ms rate (25 to 50 Hz) on this microcontroller.
3. The ease of implementing OSQP and updating generated code in the EPS-IDF framework is impressively practical.

## OSQP Benchmarking on Raspberry Pi 3 Model B Rev 1.2 ( BCM2835 rev a02082 ARM Cortex A53 @ 1.2Ghz )

```
rm -dr osqp_gen/build
cmake -S osqp_gen -B osqp_gen/build
make -C osqp_gen/build
time ./osqp_gen/build/out/example
```

| CPU Freq (MHz) | States / Actuators (#) | Horizon (#) | Variables (n) | Constraints (m) | nnz(P) + nnz(A) | Time / solve (ms) |
|:--------------:|:----------------------:|:-----------:|:-------------:|:---------------:|:---------------:|:-----------------:|
|      1200      |          2 / 3         |     50      |     252       |       354       |      1258       |         2.46      |
|      1200      |         12 / 4         |     10      |     172       |       304       |      1161       |         3.55      |
|      1200      |         12 / 4         |     30      |     492       |       864       |      3421       |        14.2       |
|      1200      |         12 / 4         |   1000      |   16012       |     28024       |    113031       |       523.7       |

## OSQP Benchmarking on Linux ( Intel(R) Core(TM) i5-2400 CPU @ 3.10GHz )

```
rm -dr osqp_gen/build
cmake -S osqp_gen -B osqp_gen/build
make -C osqp_gen/build
time ./osqp_gen/build/out/example
```

| CPU Freq (MHz) | States / Actuators (#) | Horizon (#) | Variables (n) | Constraints (m) | nnz(P) + nnz(A) | Time / solve (ms) |
|:--------------:|:----------------------:|:-----------:|:-------------:|:---------------:|:---------------:|:-----------------:|
|      3100      |          2 / 3         |     50      |     252       |       354       |      1258       |      0.192        |
|      3100      |         12 / 4         |     10      |     172       |       304       |      1161       |      0.238        |
|      3100      |         12 / 4         |     30      |     492       |       864       |      3421       |      0.835        |
|      3100      |         12 / 4         |   1000      |   16012       |     28024       |    113031       |       33.8        |

## OSQP Benchmarking on MacOS ( Intel(R) Core(TM) i7-4850HQ @ 2.30GHz )

```
rm -dr osqp/build
cmake -S osqp -B osqp/build
make -C osqp/build
./osqp/build/out/osqp_demo
```

1. [Macbook Consol Output](image/mac_output.png) from building the python generated code into a native executable.

2. The variables tested and resulting performance statistics are summarized in the following table.

| CPU Freq (MHz) | States / Actuators (#) | Horizon (#) | Variables (n) | Constraints (m) | nnz(P) + nnz(A) | Time / solve (ms) |
|:--------------:|:----------------------:|:-----------:|:-------------:|:---------------:|:---------------:|:-----------------:|
|      2300      |          9 / 3         |      2      |      33       |        60       |       164       |      -----        |
|      2300      |          9 / 4         |      2      |      35       |        62       |       186       |      0.028        |
|      2300      |         12 / 4         |      2      |      44       |        80       |       257       |      0.035        |
|      2300      |          9 / 3         |      5      |      69       |       123       |       377       |      -----        |
|      2300      |          9 / 4         |      5      |      74       |       128       |       432       |      0.060        |
|      2300      |         12 / 4         |      5      |      92       |       164       |       596       |      0.085        |
|      2300      |          9 / 3         |     10      |     129       |       228       |       732       |      -----        |
|      2300      |          9 / 4         |     10      |     139       |       238       |       842       |      0.125        |
|      2300      |         12 / 4         |     10      |     172       |       304       |      1161       |      0.180        |
|      2300      |          9 / 3         |     30      |     369       |       648       |      2152       |      -----        |
|      2300      |          9 / 4         |     30      |     399       |       678       |      2482       |      -----        |
|      2300      |         12 / 4         |     30      |     492       |       864       |      3421       |      -----        |

## Other Resources
- [Fast MPC](https://web.stanford.edu/~boyd/papers/pdf/fast_mpc.pdf)
- [Converting MPC to QP Form](https://robotology.github.io/osqp-eigen/md_pages_mpc.html)
- [OSQP Dev Docs](https://osqp.org/docs/)

## Misc. Notes
- NNZ = Number of Non-Zero elements
- Big O Complexity = O(T(n+m)^3)