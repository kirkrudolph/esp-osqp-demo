# ESP OSQP
Still work to do here. They don't have a good example for embedded. Still can't compile esp32 example.

REMEMBER TO CLONE RECURSIVE `git clone --recurse-submodules <repo>`

## OSQP Example (on Mac)
[Build From Source](https://osqp.org/docs/get_started/sources.html)

Following code generates build files and `osqp/include/osqp_configure.h`
- need to add `set(EMBEDDED 2)` in CMakeLists.txt to enable `#define EMBEDDED`

```
cd osqp
mkdir build
cd build
cmake -G "Unix Makefiles" ..
```

Following code builds native libraries and runs demo executable:

```
cmake --build .
./out/osqp_demo
```

## Embedded
`osqp.h` functions that don't work with `#define EMBEDDED`.
- osqp_setup
- osqp_cleanup
- osqp_update_polish
- osqp_update_polish_refine_iter
- osqp_update_verbose

`osqp.h` functions that don't work with `#define EMBEDDED 1`.
- osqp_update_P
- osqp_update_A
- osqp_update_P_A
- osqp_update_rho
- osqp_update_delta

Therefore, default example doesn't work on embedded. Need to write custom code for `setup` and `cleanup` then make call to `osqp_solve`.

## Troubleshooting ([Issue submitted](https://github.com/osqp/osqp/issues/422))
Trying to use `idf.py build` (with or without `set(EMBEDDED 2)`) results in:

```
CMake Warning (dev) at osqp/lin_sys/direct/qdldl/qdldl_sources/CMakeLists.txt:132 (add_library):
  ADD_LIBRARY called with SHARED option but the target platform does not
  support dynamic linking.  Building a STATIC library instead.  This may lead
  to problems.

ninja: error: build.ninja:17849: multiple rules generate osqp/lin_sys/direct/qdldl/qdldl_sources/out/libqdldl.a [-w dupbuild=err]
```