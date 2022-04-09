cmake_minimum_required(VERSION 3.21)
set(This TestLittleHashTables)

set(Sources

    Tests.cpp
    TestSmallHashT.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
    gtest_main
    stack_hash
)

add_test(
    NAME ${This}
    COMMAND ${This}
)