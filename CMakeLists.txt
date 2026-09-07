cmake_minimum_required(VERSION 3.20)
project(cpp_algorithms_problem_solving_level_4)

set(CMAKE_CXX_STANDARD 20)

file(GLOB PROBLEM_FILES "Problems/*.cpp")

foreach(FILE ${PROBLEM_FILES})
    get_filename_component(TARGET_NAME ${FILE} NAME_WE)
    add_executable(${TARGET_NAME} ${FILE})
endforeach()