cmake_minimum_required(VERSION 3.14)
project(FactoryCpp CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Production library
add_library(factory_lib STATIC FactoryExample.cpp)
target_include_directories(factory_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Test executable (links googletest provided by top-level)
add_executable(test_factory
    tests/test_factory.cpp
)
target_include_directories(test_factory PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(test_factory
    PRIVATE
    factory_lib
    gtest
    gtest_main
)

# Optional example app
add_executable(FactoryExampleApp FactoryExampleMain.cpp)
target_link_libraries(FactoryExampleApp PRIVATE factory_lib)

enable_testing()
add_test(NAME FactoryCppTests COMMAND test_factory)
