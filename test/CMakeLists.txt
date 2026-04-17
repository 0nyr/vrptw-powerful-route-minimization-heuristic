#enable_tnt_compile_flags()

add_compile_flags("C;CXX"
    "-Wno-unused-parameter")

# WARNING: This change affects current cmake variable scope and so
#          a user should care to don't use it in a top level scope.
# The dynamic libraries will be loaded from tarantool executable
# and will use symbols from it. So it is completely okay to have
# unresolved symbols at build time.
string(REPLACE "-Wl,--no-undefined" ""
    CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}")

if(POLICY CMP0037)
    if(CMAKE_VERSION VERSION_LESS 3.11)
        # cmake below 3.11 reserves name test. Use old policy.
        # https://cmake.org/cmake/help/v3.11/release/3.11.html#other-changes
        cmake_policy(SET CMP0037 OLD)
    else()
        # Starting from cmake 3.11 name test reserved in special
        # cases and can be used as target name.
        cmake_policy(SET CMP0037 NEW)
    endif()
endif(POLICY CMP0037)

add_subdirectory(unit)

set(SOLVER_TIMEOUT_FIXTURE
    ${CMAKE_CURRENT_SOURCE_DIR}/fixtures/c101_n25.txt)
set(SOLVER_TIMEOUT_OUTPUT
    ${CMAKE_CURRENT_BINARY_DIR}/solver_timeout.solution)
add_test(
    NAME solver_timeout_smoke
    COMMAND ${CMAKE_COMMAND}
            -DROUTES_BIN=$<TARGET_FILE:routes>
            -DFIXTURE=${SOLVER_TIMEOUT_FIXTURE}
            -DOUTPUT=${SOLVER_TIMEOUT_OUTPUT}
            -P ${CMAKE_CURRENT_SOURCE_DIR}/solver_timeout_smoke.cmake
)
set_tests_properties(solver_timeout_smoke PROPERTIES TIMEOUT 3)
