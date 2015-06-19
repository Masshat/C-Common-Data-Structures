cmake_minimum_required(VERSION 2.8)
project(C-Common-Data-Structures)


# Build the data structure libraries.
set(DIR_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src")
add_subdirectory(${DIR_SRC})

# Build the corresponding unit tests.
set(DIR_TEST "${CMAKE_CURRENT_SOURCE_DIR}/test")
add_subdirectory(${DIR_TEST})

# Build the corresponding demo programs.
set(DIR_DEMO "${CMAKE_CURRENT_SOURCE_DIR}/demo")
add_subdirectory(${DIR_DEMO})


# Set the "make run" target.
set(TARGET_RUN "run")
set(SCRIPT "./auto.py")
add_custom_target ( ${TARGET_RUN}
    COMMAND ${SCRIPT}
    WORKING_DIRECTORY ${DIR_TEST}
)