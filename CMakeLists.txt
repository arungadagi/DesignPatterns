cmake_minimum_required(VERSION 3.14)
project(Designpatterns C CXX)
# Enable testing at the repository root so top-level `ctest` picks up
# tests registered by subprojects.
enable_testing()

# Configure the examples subproject. The example's CMakeLists is written to
# work as a subtree, so we add it here to make `cmake -S . -B build` work from
# the repository root.
add_subdirectory(creational/factory/example)
