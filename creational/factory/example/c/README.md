# C example — GoogleTest integration

This example builds GoogleTest-driven tests for the minimal C `factory` implementation.

Build (top-level example CMake provides googletest):

```bash
cd creational/factory/example
cmake -S . -B build
cmake --build build --target test_factory_c
ctest --test-dir build --output-on-failure
```

If you prefer to build the C example standalone, see its local CMake and either vendor googletest or allow FetchContent to download it.
