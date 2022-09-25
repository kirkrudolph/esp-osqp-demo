idf_component_register(SRCS "esp-osqp.c"
                    INCLUDE_DIRS "." "../components/osqp_gen/include")

# `main` calls a function from the library, so link it to `main`
target_link_libraries(${COMPONENT_LIB} PRIVATE emosqpstatic)