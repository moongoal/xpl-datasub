get_filename_component(PROJ_DIR ${CMAKE_CURRENT_LIST_DIR} DIRECTORY)

execute_process(
    COMMAND ${CMAKE_COMMAND}
        -S ${PROJ_DIR}
        -B build
        -D CMAKE_EXPORT_COMPILE_COMMANDS=1
        -G Ninja
)
