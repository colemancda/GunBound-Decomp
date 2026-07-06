# amd64 Wine environment for running the Visual C++ 2003 (MSVC 7.10) toolchain
# on an Apple Silicon Mac. Docker Desktop emulates linux/amd64 via Rosetta so the
# 32-bit Windows cl.exe/link.exe run here for byte-matching decompilation.
#
# Build (from repo root):
#   docker build --platform linux/amd64 -t gb-msvc tools/msvc-env
# Run a compile (mount repo at /work):
#   docker run --rm --platform linux/amd64 -v "$PWD":/work gb-msvc \
#       wine cl.exe /c /work/src/foo.c
#
# NOTE: The MSVC 7.10 binaries (cl.exe, link.exe, headers, libs) are proprietary
# and are NOT included. Drop a Visual Studio .NET 2003 "Vc7" tree into
# tools/msvc-env/msvc7/ before building; it is COPYed in below. See README.md.

FROM --platform=linux/amd64 debian:bookworm-slim

RUN dpkg --add-architecture i386 && apt-get update && \
    apt-get install -y --no-install-recommends \
        wine wine32:i386 winbind ca-certificates && \
    rm -rf /var/lib/apt/lists/*

ENV WINEDEBUG=-all \
    WINEPREFIX=/root/.wine \
    WINEARCH=win32

# Proprietary compiler tree supplied by the user (git-ignored).
COPY msvc7/ /opt/msvc7/

# Point Wine's PATH/INCLUDE/LIB at the MSVC tree.
ENV WINEPATH="C:\\msvc7\\bin" \
    INCLUDE="C:\\msvc7\\include;C:\\msvc7\\PlatformSDK\\include" \
    LIB="C:\\msvc7\\lib;C:\\msvc7\\PlatformSDK\\lib"

WORKDIR /work
