# Linux container providing a working `winegcc`, for compiling the
# Winelib target (src/main.c and friends) while a real macOS-native
# Winelib toolchain isn't available (see src/README.md - building Wine
# from source on macOS to get winegcc was judged too heavy for now).
#
# IMPORTANT CAVEAT: a binary built here is a Linux ELF Winelib binary
# (winegcc always targets whatever platform it's running on) - it runs
# inside this same container via its own `wine`, not natively on macOS.
# This validates that the code actually compiles/links against real
# Win32/DirectX/Winsock declarations, which is real progress, but it is
# NOT the same as the eventual "native Winelib binary on macOS" goal.
#
# Build:
#   docker build --platform linux/amd64 -t gb-winelib tools/winelib-env
# Compile (mounts repo at /work):
#   docker run --rm --platform linux/amd64 -v "$PWD":/work gb-winelib \
#       make winelib
# Run the result inside the container:
#   docker run --rm --platform linux/amd64 -v "$PWD":/work gb-winelib \
#       wine build/gunbound.exe.so

FROM --platform=linux/amd64 debian:bookworm-slim

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        wine64 wine64-tools make gcc g++ ca-certificates && \
    rm -rf /var/lib/apt/lists/*

ENV WINEDEBUG=-all \
    WINEPREFIX=/root/.wine \
    WINEARCH=win64 \
    WINEGCC=winegcc-stable

WORKDIR /work
