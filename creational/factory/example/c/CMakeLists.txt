cmake_minimum_required(VERSION 3.14)
project(FactoryC C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Build the C library (production code)
add_library(factory_c_lib STATIC factory.c)
target_include_directories(factory_c_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Test executable (GoogleTest is provided by the top-level CMake)
add_executable(test_factory_c
    test/test_factory_gtest.cpp
)
target_include_directories(test_factory_c PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(test_factory_c
    PRIVATE
    factory_c_lib
    gtest
    gtest_main
)

enable_testing()
add_test(NAME FactoryCTests COMMAND test_factory_c)
