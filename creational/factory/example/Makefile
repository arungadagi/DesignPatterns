# Simple Makefile for Factory examples (no CMake required)
# Usage:
#   make            # build app and tests
#   make test       # run tests
#   make clean

# Tools
CC := gcc
CXX := g++
AR := ar
RM := rm -rf
MKDIR_P := mkdir -p

# Paths
EXAMPLE_DIR := .
CPP_DIR := $(EXAMPLE_DIR)/cpp
C_DIR := $(EXAMPLE_DIR)/c
BUILD_DIR := $(EXAMPLE_DIR)/build
REPO_ROOT := $(abspath $(CURDIR)/../../..)
REPO_BUILD_DIR := $(abspath $(REPO_ROOT)/build)

# Googletest detection (prefer repo-root third_party, fall back to example-local)
LOCAL_GTEST := $(abspath $(CURDIR)/third_party/googletest/googletest)
ROOT_GTEST := $(abspath $(REPO_ROOT)/third_party/googletest/googletest)
GTEST_ROOT :=
ifeq (,$(wildcard $(ROOT_GTEST)/CMakeLists.txt))
	ifneq (,$(wildcard $(LOCAL_GTEST)/CMakeLists.txt))
		GTEST_ROOT := $(LOCAL_GTEST)
	endif
else
	GTEST_ROOT := $(ROOT_GTEST)
endif
GTEST_LIB_DIR := $(abspath $(REPO_BUILD_DIR)/lib)
OBJ_DIR := $(BUILD_DIR)/obj

# Flags
CFLAGS := -std=c99 -Wall -Wextra -g -I$(C_DIR)
CXXFLAGS := -std=c++17 -Wall -Wextra -g -I$(CPP_DIR)
LDFLAGS := -pthread

# Extra flags used when compiling sources that include googletest headers
GTEST_CXXFLAGS := -D_POSIX_C_SOURCE=200809L -D_GNU_SOURCE

# Sources
CPP_SRCS := $(CPP_DIR)/FactoryExample.cpp $(CPP_DIR)/FactoryExampleMain.cpp
CPP_OBJS := $(patsubst $(CPP_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(filter %.cpp,$(CPP_SRCS)))

CPP_TEST_SRC := $(CPP_DIR)/tests/test_factory_simple.cpp
C_SRCS := $(C_DIR)/factory.c
C_OBJ := $(OBJ_DIR)/factory.c.o
C_TEST_SRC := $(C_DIR)/test/test_factory_simple.c

# Targets
.PHONY: all test clean

# Select test binaries: prefer gtest-based binaries when googletest is present
ifneq ($(GTEST_ROOT),)
	TEST_BINARIES := $(BUILD_DIR)/test_factory_gtest $(BUILD_DIR)/test_factory_c_gtest
else
	TEST_BINARIES := $(BUILD_DIR)/test_factory $(BUILD_DIR)/test_factory_c
endif

all: $(BUILD_DIR)/FactoryExampleApp $(TEST_BINARIES)

# Ensure googletest libs are available (build via CMake at repo root if needed)
.PHONY: ensure_gtest
ensure_gtest:
	@if [ -z "$(GTEST_ROOT)" ]; then echo "googletest not found under $(ROOT_GTEST) or $(LOCAL_GTEST)"; exit 1; fi
	@if [ ! -f "$(GTEST_LIB_DIR)/libgtest.a" ]; then \
		cmake -S $(REPO_ROOT) -B $(REPO_BUILD_DIR) && \
		cmake --build $(REPO_BUILD_DIR) --config Debug --target gtest gtest_main; \
	fi

$(OBJ_DIR)/%.o: $(CPP_DIR)/%.cpp
	@$(MKDIR_P) $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/FactoryExampleApp: $(OBJ_DIR)/FactoryExample.o $(OBJ_DIR)/FactoryExampleMain.o
	@$(MKDIR_P) $(BUILD_DIR)
	$(CXX) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/test_factory: $(OBJ_DIR)/FactoryExample.o $(CPP_TEST_SRC)
	@$(MKDIR_P) $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ_DIR)/FactoryExample.o $(CPP_TEST_SRC) $(LDFLAGS)

$(C_OBJ): $(C_SRCS)
	@$(MKDIR_P) $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/test_factory_c: $(C_OBJ) $(C_TEST_SRC)
	@$(MKDIR_P) $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $(C_OBJ) $(C_TEST_SRC) -lm

# GoogleTest-based test binaries (built when googletest is present at root or local)
ifneq ($(GTEST_ROOT),)
$(BUILD_DIR)/test_factory_gtest: ensure_gtest $(OBJ_DIR)/FactoryExample.o $(CPP_DIR)/tests/test_factory.cpp
	@$(MKDIR_P) $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(GTEST_CXXFLAGS) -I$(GTEST_ROOT)/include -I$(GTEST_ROOT) -o $@ $(OBJ_DIR)/FactoryExample.o $(CPP_DIR)/tests/test_factory.cpp $(GTEST_LIB_DIR)/libgtest_main.a $(GTEST_LIB_DIR)/libgtest.a $(LDFLAGS)

$(BUILD_DIR)/test_factory_c_gtest: ensure_gtest $(C_OBJ) $(C_DIR)/test/test_factory_gtest.cpp
	@$(MKDIR_P) $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(GTEST_CXXFLAGS) -I$(GTEST_ROOT)/include -I$(GTEST_ROOT) -o $@ $(C_OBJ) $(C_DIR)/test/test_factory_gtest.cpp $(GTEST_LIB_DIR)/libgtest_main.a $(GTEST_LIB_DIR)/libgtest.a $(LDFLAGS)
endif

ifneq ($(GTEST_ROOT),)
test: ensure_gtest
	@echo "Building GoogleTest-based tests via CMake..."
	@cmake --build $(REPO_BUILD_DIR) --config Debug --target test_factory test_factory_c
	@echo "Running GoogleTest tests (ctest)..."
	@ctest --test-dir $(REPO_BUILD_DIR) --output-on-failure
else
test: all
	@echo "Running simple tests..."
	@$(BUILD_DIR)/test_factory || exit $$?
	@$(BUILD_DIR)/test_factory_c || exit $$?
endif

clean:
	$(RM) $(BUILD_DIR)
