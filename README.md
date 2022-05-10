# ESP OSQP
Still work to do here. They don't have a good example for embedded. Still can't compile esp32 example.

## OSQP Example (on Mac)
[From Source](https://osqp.org/docs/get_started/sources.html)

Following code generates build files and `osqp/include/osqp_configure.h`
- defaults to `#define IS_MAC`
- need to add `set(EMBEDDED 2)` in CMakeLists.txt to enable `#define EMBEDDED`

```
cd osqp
mkdir build
cd build
cmake -G "Unix Makefiles" ..
``

Following code builds mac libraries and runds demo executable

```
cmake --build .
./out/osqp_demo
```

## Embedded
`osqp.h` functions that don't work with embedded.
- osqp_setup
- osqp_cleanup
- osqp_update_polish
- osqp_update_polish_refine_iter
- osqp_update_verbose

`osqp.h` functions that don't work with embedded==1.
- osqp_update_P
- osqp_update_A
- osqp_update_P_A
- osqp_update_rho
- osqp_update_delta

The default example doesn't work. Need to write custom code for `setup` and `cleanup` then make  call to `osqp_solve`.

## Troubleshooting

Trying to use `idf.py build` with `#define IS_MAC` results in:

```
esp-osqp/osqp/include/util.h:112:13: fatal error: mach/mach_time.h: No such file or directory
 #   include <mach/mach_time.h>
```

Trying to use `idf.py build` with `#define EMBEDDED` results in:
