#!/usr/bin/env bash
# Build the recompiled client as an iOS app.
#
#   recomp/ios/build_ios.sh [--sim] [--exe GunBound.gme] [--install [DEVICE]] [--run]
#
#   --sim            for the iOS simulator (default: a device)
#   --exe PATH       the original executable to lift (default: orig/GunBound.gme)
#   --install [DEV]  install it: on the booted simulator, or with devicectl on the
#                    device DEV (a name or identifier from xcrun devicectl list devices)
#   --run            and start it
#
# Output: recomp/build/ios-app/{iphoneos,iphonesimulator}/GunBound.app
#
# Needs SDL2 built by recomp/ios/build_sdl.sh. The simulator app is signed ad hoc.
# A device app needs a signing identity and a provisioning profile for the bundle
# identifier (a free Apple account works, for seven days at a time):
#   BUNDLE_ID          bundle identifier (default: local.recomp.gunbound; with a free
#                      account it must be one Xcode has made a profile for)
#   CODESIGN_IDENTITY  e.g. "Apple Development: name (TEAMID)"  (security find-identity -p codesigning)
#   PROFILE            the .mobileprovision file to embed
#
# The app contains code lifted from the game's executable. It is for the owner of
# the game, built from their own copy; do not publish the .app or an .ipa.
set -euo pipefail
here="$(cd "$(dirname "$0")" && pwd)"
recomp="$(cd "$here/.." && pwd)"
target=ios sdk=iphoneos platform=iPhoneOS
install=0 run=0 device=""
while [ $# -gt 0 ]; do
    case "$1" in
    --sim) target=iossim sdk=iphonesimulator platform=iPhoneSimulator; shift ;;
    --exe) export RECOMP_EXE="$2"; shift 2 ;;
    --install)
        install=1; shift
        if [ $# -gt 0 ] && [ "${1#--}" = "$1" ]; then device="$1"; shift; fi ;;
    --run) run=1; shift ;;
    -h | --help) sed -n '2,26p' "$0" | sed 's/^# \{0,1\}//'; exit 0 ;;
    *) echo "build_ios.sh: unknown option $1" >&2; exit 2 ;;
    esac
done
[ -f "$recomp/build/deps/sdl-ios/$sdk/lib/libSDL2.a" ] ||
    { echo "build_ios.sh: no SDL2 for $sdk; run recomp/ios/build_sdl.sh first" >&2; exit 2; }

"$recomp/build.sh" "$target"
bundle_id="${BUNDLE_ID:-local.recomp.gunbound}"
app="$recomp/build/ios-app/$sdk/GunBound.app"
rm -rf "$app"
mkdir -p "$app"
cp "$recomp/build/$target/gunbound" "$app/gunbound"
sed -e "s/@BUNDLE_ID@/$bundle_id/" -e "s/@PLATFORM@/$platform/" -e "s/@IOS_MIN@/${IOS_MIN:-15.0}/" \
    "$here/Info.plist" > "$app/Info.plist"
plutil -convert binary1 "$app/Info.plist"
printf 'APPL????' > "$app/PkgInfo"

if [ "$target" = iossim ]; then
    codesign --force --sign - --timestamp=none "$app"
else
    [ -n "${CODESIGN_IDENTITY:-}" ] && [ -f "${PROFILE:-}" ] || {
        echo "build_ios.sh: a device build needs CODESIGN_IDENTITY and PROFILE (see --help); $app is unsigned" >&2
        exit 2
    }
    cp "$PROFILE" "$app/embedded.mobileprovision"
    ent="$recomp/build/ios-app/entitlements.plist"
    security cms -D -i "$PROFILE" > "$ent.profile"
    /usr/libexec/PlistBuddy -x -c 'Print :Entitlements' "$ent.profile" > "$ent"
    codesign --force --sign "$CODESIGN_IDENTITY" --entitlements "$ent" --timestamp=none "$app"
fi
echo "== $app"

if [ "$install" = 1 ]; then
    if [ "$target" = iossim ]; then
        xcrun simctl install booted "$app"
        [ "$run" = 1 ] && xcrun simctl launch --console-pty booted "$bundle_id"
    else
        [ -n "$device" ] || { echo "build_ios.sh: --install needs the device (xcrun devicectl list devices)" >&2; exit 2; }
        xcrun devicectl device install app --device "$device" "$app"
        [ "$run" = 1 ] && xcrun devicectl device process launch --device "$device" "$bundle_id"
    fi
fi
exit 0
