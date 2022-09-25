# ESP OSQP
Still work to do here. They don't have a good example for embedded. Also, default build in OSQP dependancies creates a shared lib and example executable which has to be changed manually.

1. Clone: `git clone --recurse-submodules <repo>`
2. Remove lines `132-148` from `osqp/lin_sys/direct/qdldl/qdldl_sources/CMakeLists.txt`
3. `idf.py build`

## Building OSQP Example (on Mac)
[Build From Source](https://osqp.org/docs/get_started/sources.html#build-the-binaries)

or

```
rm -dr osqp/build
cmake -S osqp -B osqp/build
make -C osqp/build
./osqp/build/out/osqp_demo
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
### [fix](https://osqp.discourse.group/t/cross-compiling-osqp-for-arm-stm32f405/221/2):  


Trying to use `idf.py build` (with or without `set(EMBEDDED 2)`) results in:

```
CMake Warning (dev) at osqp/lin_sys/direct/qdldl/qdldl_sources/CMakeLists.txt:132 (add_library):
  ADD_LIBRARY called with SHARED option but the target platform does not
  support dynamic linking.  Building a STATIC library instead.  This may lead
  to problems.

ninja: error: build.ninja:17849: multiple rules generate osqp/lin_sys/direct/qdldl/qdldl_sources/out/libqdldl.a [-w dupbuild=err]
```