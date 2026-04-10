# Factory examples (C and C++)

This repository contains example implementations of the Factory pattern (C and C++).
The example code and tests live under `creational/factory/example`.

Two build flows are provided:

- Simple Make-based flow (convenient, no CMake required): use the root `Makefile`,
  which delegates to the example `Makefile`.
- Full CMake flow (uses GoogleTest for the richer test suite).

Quick Start — Make (simple)
```bash
cd <repo-root>
make        # builds the example app and simple tests via creational/factory/example/Makefile
make test   # runs the simple tests
make clean  # remove build artifacts
```

Quick Start — CMake (full, GoogleTest)
```bash
cd <repo-root>
cmake -S . -B build
cmake --build build --config Debug --target FactoryExampleApp
cmake --build build --config Debug --target test_factory
cmake --build build --config Debug --target test_factory_c
ctest --test-dir build --output-on-failure
```

Notes
- A vendored copy of GoogleTest is available at `third_party/googletest`. The example
  CMake prefers a repo-root vendored copy if present; otherwise it falls back to
  `FetchContent` to download GoogleTest during configure.
- The simple Makefile-based tests are implemented without GoogleTest and are found in
  `creational/factory/example/c/test` and `creational/factory/example/cpp/tests`.
- If you prefer to run the example Makefile directly:
  `cd creational/factory/example && make`

See `creational/factory/example/README.md` (moved here) for more details.
