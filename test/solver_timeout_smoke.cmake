file(REMOVE "${OUTPUT}")

execute_process(
    COMMAND "${ROUTES_BIN}" "${FIXTURE}" "${OUTPUT}" --t_max_ms 1 --log_level none
    RESULT_VARIABLE routes_exit_code
    OUTPUT_VARIABLE routes_stdout
    ERROR_VARIABLE routes_stderr
)

if(NOT routes_exit_code EQUAL 0)
    message(FATAL_ERROR
        "routes exited with code ${routes_exit_code}\n"
        "stdout:\n${routes_stdout}\n"
        "stderr:\n${routes_stderr}\n")
endif()

if(NOT EXISTS "${OUTPUT}")
    message(FATAL_ERROR "routes did not create solution file '${OUTPUT}'")
endif()

file(SIZE "${OUTPUT}" output_size)
if(output_size LESS 1)
    message(FATAL_ERROR "routes created an empty solution file '${OUTPUT}'")
endif()
