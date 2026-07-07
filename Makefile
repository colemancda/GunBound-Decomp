# Behavioral-parity reimplementation build (see src/README.md for what
# that means and how it differs from the matching-decompilation goal).
#
# Targets:
#   make              - native host build of pure-algorithm modules only
#                       (currently src/lzhuf/), no Windows toolchain needed.
#   make winelib      - attempts a full link of every raw/verbatim-ported
#                       function via Winelib (winegcc). WILL NOT LINK YET -
#                       most raw ports reference not-yet-ported globals/
#                       helpers (see src/README.md's "Raw/verbatim ports"
#                       section) - this target exists to make that failure
#                       visible/trackable, not because it's expected to
#                       succeed right now.
#   make winelib-syntax-check - per-file syntax-only compile (-c) of every
#                       raw port, the actually-useful check at this stage.
#                       Needs Wine installed (see src/README.md).

CC ?= clang
CFLAGS ?= -std=c11 -Wall -Wextra -O2 -Iinclude
BUILD ?= build

LZHUF_SRCS := $(wildcard src/lzhuf/*.c)
TEST_SRCS := src/test_lzhuf.c

WINEGCC ?= winegcc
# src/unnamed/msvc_crt_atl/ is the statically-linked MSVC CRT/ATL runtime,
# deliberately excluded from the build - see that directory's README.md.
RAW_SRCS := $(filter-out src/test_lzhuf.c, $(shell find src -name '*.c' ! -path 'src/lzhuf/*' ! -path 'src/unnamed/msvc_crt_atl/*'))
MAIN_SRCS := $(LZHUF_SRCS) $(RAW_SRCS)

.PHONY: all winelib winelib-syntax-check test clean

all: $(BUILD)/test_lzhuf

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/test_lzhuf: $(LZHUF_SRCS) $(TEST_SRCS) | $(BUILD)
	$(CC) $(CFLAGS) -o $@ $(LZHUF_SRCS) $(TEST_SRCS)

# Requires winegcc on PATH (part of a Wine install - see src/README.md).
# gnu11, not c11: Wine's winsock.h expects glibc's BSD typedefs
# (u_short/u_int), which strict c11 mode hides.
winelib: | $(BUILD)
	$(WINEGCC) -std=gnu11 -Wall -Wextra -Iinclude -o $(BUILD)/gunbound.exe $(MAIN_SRCS) -lws2_32

winelib-syntax-check:
	@for f in $(RAW_SRCS); do \
		$(WINEGCC) -std=gnu11 -Iinclude -c "$$f" -o /tmp/gb_syntax_check.o 2>&1 | grep -q 'error:' && echo "FAIL: $$f" || true; \
	done

test: $(BUILD)/test_lzhuf
	@echo "See src/README.md for how to run this against real archive data."

clean:
	rm -rf $(BUILD)
