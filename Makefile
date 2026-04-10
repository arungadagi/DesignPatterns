# Top-level Makefile wrapper — delegates to the example Makefile
# Run `make` at repository root to build the examples in their folder.

.PHONY: all test clean cmake

all:
	$(MAKE) -C creational/factory/example all

test:
	$(MAKE) -C creational/factory/example test

clean:
	$(MAKE) -C creational/factory/example clean
	-@rm -rf build

cmake:
	cmake -S . -B build
