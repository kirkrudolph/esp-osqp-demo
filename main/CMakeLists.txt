idf_component_register(SRCS "esp-osqp.c"
                    INCLUDE_DIRS "." "../osqp/include")

# Import the library, specifying a target name and the library path.
add_prebuilt_library(osqp "../build/osqp/out/libosqp.a")

# `main` calls a function from the library, so link it to `main`
target_link_libraries(${COMPONENT_LIB} PRIVATE osqp)