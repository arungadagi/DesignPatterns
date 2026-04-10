cmake_minimum_required(VERSION 3.14)
project(FactoryExamples C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Prefer a vendored googletest (third_party/googletest) if present to avoid
# FetchContent/network failures in restricted environments. Check both the
# example-local `third_party` and the repository root `third_party` and use
# whichever exists. Fall back to FetchContent otherwise.
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/third_party/googletest/CMakeLists.txt")
    message(STATUS "Using vendored googletest from ${CMAKE_CURRENT_SOURCE_DIR}/third_party/googletest")
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third_party/googletest ${CMAKE_CURRENT_BINARY_DIR}/googletest-build EXCLUDE_FROM_ALL)
elseif(EXISTS "${PROJECT_SOURCE_DIR}/third_party/googletest/CMakeLists.txt")
    message(STATUS "Using vendored googletest from ${PROJECT_SOURCE_DIR}/third_party/googletest")
    add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/googletest ${CMAKE_CURRENT_BINARY_DIR}/googletest-build EXCLUDE_FROM_ALL)
else()
    # Fetch Google Test once for both C and C++ example tests
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
    )

    # For Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    FetchContent_MakeAvailable(googletest)
endif()

# Add example subprojects
add_subdirectory(cpp)
add_subdirectory(c)

enable_testing()
enable_testing()

