# Dev environment for the GunBound decompilation toolchain, adapted from
# tools/README.md (written for the original author's Apple Silicon Mac) to a
# self-contained Debian container. Bakes in everything needed for:
#   - native behavioral-parity build     (make            -> clang/gcc + make)
#   - winelib syntax-check               (make winelib-syntax-check -> winegcc)
#   - asm-differ diffing/scoring         (python deps + llvm-objdump)
#
# NOT included (proprietary — must be supplied by hand, see tools/README.md's
# "Rebuilding this setup from scratch"):
#   - the real MSVC 7.10 tree at tools/msvc-env/msvc7/  (byte-matching route)
#   - the target binary orig/GunBound.gme
# The MSVC route runs its own Docker image (tools/msvc-env/); to use it from
# inside this container, enable the docker-in-docker feature in devcontainer.json.
FROM debian:13-slim

# winegcc (wine32-tools) and the 32-bit wine loader both require i386.
RUN dpkg --add-architecture i386 \
 && apt-get update \
 && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      ca-certificates git make \
      clang gcc \
      llvm binutils \
      wine wine32:i386 wine32-tools:i386 \
      python3 python3-pip \
 && rm -rf /var/lib/apt/lists/*

# asm-differ's Python dependencies (same set as tools/README.md).
RUN pip3 install --no-cache-dir --break-system-packages \
      colorama cxxfilt watchdog levenshtein

# asm-differ picks its objdump flag spelling by string-matching "llvm-" in the
# executable path, so a plainly-named `llvm-objdump` must be on PATH. Debian's
# `llvm` package sometimes only ships a version-suffixed binary — symlink it.
RUN if ! command -v llvm-objdump >/dev/null 2>&1; then \
      target="$(ls /usr/bin/llvm-objdump-* 2>/dev/null | sort -V | tail -1)"; \
      [ -n "$target" ] && ln -s "$target" /usr/local/bin/llvm-objdump; \
    fi \
 && llvm-objdump --version | head -1
