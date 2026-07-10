#!/usr/bin/env bash
# Capture ground-truth test vectors from the network encode/checksum functions of
# the RUNNING GunBound client, by attaching a gdb (through the winedbg stub) and
# logging inputs/outputs with netcap.py.
#
# Prereq: a stub is already listening (start it with wine-attach.sh in another
# terminal). NOTE: only one gdb can use the stub at a time, so this is an
# ALTERNATIVE to connecting Ghidra — run one or the other against a given stub.
#
# Usage: capture-net-vectors.sh [PORT] [LOGFILE]
#   PORT     stub port (default 12345)
#   LOGFILE  where to append vectors (default /tmp/gunbound-netvectors.log)
#
# Runs until you Ctrl-C. Detaches cleanly so the game keeps running.
set -euo pipefail

PORT="${1:-12345}"
export NETCAP_LOG="${2:-/tmp/gunbound-netvectors.log}"
export NETCAP_MAX_HITS="${NETCAP_MAX_HITS:-25}"

GH=/home/coleman/Downloads/ghidra_11.0.1_PUBLIC
HERE="$(cd "$(dirname "$0")" && pwd)"
export PYTHONPATH="$GH/Ghidra/Debug/Debugger-agent-gdb/pypkg/src:$GH/Ghidra/Debug/Debugger-rmi-trace/pypkg/src"

echo "[*] Connecting to stub localhost:$PORT ; logging to $NETCAP_LOG (cap $NETCAP_MAX_HITS/func)"
echo "[*] Ctrl-C to stop and detach."

exec gdb -q \
  -ex "set pagination off" \
  -ex "set confirm off" \
  -ex "set architecture i386" \
  -ex "target remote localhost:$PORT" \
  -ex "source $HERE/netcap.py" \
  -ex "continue"
