# Behavioral-parity reimplementation build (see src/README.md for what
# that means and how it differs from the matching-decompilation goal).
#
# Builds and runs with a native host compiler (no MSVC 7.10 / Windows
# toolchain required) since nothing here yet depends on Windows APIs.

CC ?= clang
CFLAGS ?= -std=c11 -Wall -Wextra -O2 -Iinclude
BUILD ?= build

SRCS := src/lzhuf.c
TEST_SRCS := src/test_lzhuf.c

.PHONY: all test clean

all: $(BUILD)/test_lzhuf

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/test_lzhuf: $(SRCS) $(TEST_SRCS) | $(BUILD)
	$(CC) $(CFLAGS) -o $@ $(SRCS) $(TEST_SRCS)

test: $(BUILD)/test_lzhuf
	@echo "See src/README.md for how to run this against real archive data."

clean:
	rm -rf $(BUILD)
