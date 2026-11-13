#!/usr/bin/env bash
# Build SDL2 as static libraries for iOS devices and the iOS simulator (arm64).
#
#   recomp/ios/build_sdl.sh [SDL_SOURCE]
#
# SDL_SOURCE defaults to recomp/build/deps/SDL2, a checkout of SDL 2.32.x:
#   git clone --depth 1 --branch release-2.32.10 https://github.com/libsdl-org/SDL.git recomp/build/deps/SDL2
# Output: recomp/build/deps/sdl-ios/{iphoneos,iphonesimulator}/{include/SDL2,lib/libSDL2.a,lib/libSDL2main.a}
# IOS_MIN sets the deployment target (default 15.0).
set -euo pipefail
here="$(cd "$(dirname "$0")" && pwd)"
build="$here/../build/deps"
src="${1:-$build/SDL2}"
[ -f "$src/CMakeLists.txt" ] || { echo "no SDL source at $src" >&2; exit 2; }
mkdir -p "$build/sdl-ios-build"
for sdk in iphoneos iphonesimulator; do
    b="$build/sdl-ios-build/$sdk"
    cmake -S "$src" -B "$b" -G Ninja \
        -DCMAKE_SYSTEM_NAME=iOS -DCMAKE_OSX_SYSROOT="$sdk" -DCMAKE_OSX_ARCHITECTURES=arm64 \
        -DCMAKE_OSX_DEPLOYMENT_TARGET="${IOS_MIN:-15.0}" -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_C_COMPILER="$(xcrun -f clang)" -DCMAKE_CXX_COMPILER="$(xcrun -f clang++)" \
        -DSDL_SHARED=OFF -DSDL_STATIC=ON -DSDL_TEST=OFF \
        -DCMAKE_INSTALL_PREFIX="$build/sdl-ios/$sdk" > "$b.configure.log" 2>&1 \
        || { echo "configure failed: $b.configure.log" >&2; exit 1; }
    cmake --build "$b" > "$b.build.log" 2>&1 || { echo "build failed: $b.build.log" >&2; exit 1; }
    cmake --install "$b" > /dev/null
    echo "SDL2 for $sdk -> $build/sdl-ios/$sdk"
done
