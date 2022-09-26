# ESP OSQP
[OSQP](https://osqp.org/) is an open-source, efficient, and robust numerical optimization package for solving convex quadratic programs. 

This repository is an example of how to implement OSQP on an embedded controller for model predictive control (MPC).

## Workflow
1. MPC problem is designed in a high level language (MATLAB or Python). For example, see [kirkrudolph/osqp-python](https://github.com/kirkrudolph/osqp-python) which uses an example from OSQP to simulate a 12 state model of a quadcopter. The python interface is capable of generating a solver in c code for the specific problem.
2. Take the generated c code and compile for an embedded microcontroller. This repo uses an ESP32 microcontroller.

## OSQP Generated Code on Embedded Microcontroller

The image below shows the microcontroller's output from building this repository and flashing it to an ESP32.

![esp_output](image/esp32_output.png)

After measuring performance, it's much worse than I was hoping:

```
10 iterations took 2 seconds (235 ms per invocation)
```

## OSQP Generated Code on MacOS

The image below shows the macbook output from building the python generated code into a native executable.

![mac_output](image/mac_output.png)

## Other Resources
- [Converter MPC to QP Form](https://robotology.github.io/osqp-eigen/md_pages_mpc.html)

OSQP C Interface (instead of python)
- [Build From Source](https://osqp.org/docs/get_started/sources.html#build-the-binaries)

```
rm -dr osqp/build
cmake -S osqp -B osqp/build
make -C osqp/build
./osqp/build/out/osqp_demo
```