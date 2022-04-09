cmake_minimum_required(VERSION 3.21)

set(This stack_hash)


project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_FLAGS "-g -Wall")

enable_testing()

add_subdirectory(googletest)


set(Headers
    Kerr.h
    SmallHashT.h
    prime_checks.h
)

set(Sources
    SmallHashT.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(test)
