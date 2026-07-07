# Behavioral-parity reimplementation build (see src/README.md for what
# that means and how it differs from the matching-decompilation goal).
#
# Two build targets:
#   make            - native host build of pure-algorithm modules only
#                     (currently src/lzhuf/), no Windows toolchain needed.
#   make winelib    - full game build via Winelib (winegcc), including
#                     main.c's real Win32/DirectX/Winsock entry point.
#                     Needs Wine installed (see src/README.md).

CC ?= clang
CFLAGS ?= -std=c11 -Wall -Wextra -O2 -Iinclude
BUILD ?= build

LZHUF_SRCS := $(wildcard src/lzhuf/*.c)
TEST_SRCS := src/test_lzhuf.c

WINEGCC ?= winegcc
MAIN_SRCS := src/main.c $(LZHUF_SRCS)

.PHONY: all winelib test clean

all: $(BUILD)/test_lzhuf

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/test_lzhuf: $(LZHUF_SRCS) $(TEST_SRCS) | $(BUILD)
	$(CC) $(CFLAGS) -o $@ $(LZHUF_SRCS) $(TEST_SRCS)

# Requires winegcc on PATH (part of a Wine install - see src/README.md).
winelib: | $(BUILD)
	$(WINEGCC) -std=c11 -Wall -Wextra -Iinclude -o $(BUILD)/gunbound.exe $(MAIN_SRCS)

test: $(BUILD)/test_lzhuf
	@echo "See src/README.md for how to run this against real archive data."

clean:
	rm -rf $(BUILD)
