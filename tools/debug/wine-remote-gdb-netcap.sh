#!/usr/bin/bash
#@title gdb (wine remote stub + netcap logging)
#@desc <html><body width="320px">
#@desc   <h3>Connect to a <tt>winedbg --gdb</tt> stub AND log network vectors</h3>
#@desc   <p>Same as "gdb (wine remote stub)", but also installs netcap's
#@desc   auto-continuing logger breakpoints on the packet/checksum/receive
#@desc   functions. They never halt the game; captured vectors stream to
#@desc   <tt>NETCAP_LOG</tt>. Drive the game (World List refresh, join a room,
#@desc   fire) to produce traffic. Disconnect in Ghidra to detach cleanly —
#@desc   there is no timed auto-detach here.</p>
#@desc </body></html>
#@menu-group gdb
#@icon icon.debugger
#@help TraceRmiLauncherServicePlugin#gdb
#@env OPT_GDB_PATH:str="gdb" "Path to gdb" "The path to gdb. Omit the full path to resolve using the system PATH."
#@env OPT_HOST:str="localhost" "Stub host" "Host where the winedbg gdb stub is listening."
#@env OPT_PORT:str="12345" "Stub port" "TCP port passed to wine-gdbstub.sh / wine-attach.sh."
#@env OPT_ARCH:str="i386" "Architecture" "gdb architecture of the guest (GunBound is 32-bit i386)."
#@env OPT_NETCAP_LOG:str="/tmp/gunbound-netvectors.log" "Vector log" "Where netcap appends captured vectors."
#@env OPT_NETCAP_GROUPS:str="checksum,blob,recv" "netcap groups" "Which function groups to log."

NETCAP_PY=/home/coleman/Developer/GunBound-Decomp/tools/debug/netcap.py

if [ -d ${GHIDRA_HOME}/ghidra/.git ]
then
  export PYTHONPATH=$GHIDRA_HOME/ghidra/Ghidra/Debug/Debugger-agent-gdb/build/pypkg/src:$PYTHONPATH
  export PYTHONPATH=$GHIDRA_HOME/ghidra/Ghidra/Debug/Debugger-rmi-trace/build/pypkg/src:$PYTHONPATH
elif [ -d ${GHIDRA_HOME}/.git ]
then
  export PYTHONPATH=$GHIDRA_HOME/Ghidra/Debug/Debugger-agent-gdb/build/pypkg/src:$PYTHONPATH
  export PYTHONPATH=$GHIDRA_HOME/Ghidra/Debug/Debugger-rmi-trace/build/pypkg/src:$PYTHONPATH
else
  export PYTHONPATH=$GHIDRA_HOME/Ghidra/Debug/Debugger-agent-gdb/pypkg/src:$PYTHONPATH
  export PYTHONPATH=$GHIDRA_HOME/Ghidra/Debug/Debugger-rmi-trace/pypkg/src:$PYTHONPATH
fi

# netcap reads these at import time. Internal=1 keeps the loggers out of Ghidra's
# breakpoint list; SECONDS=0 means no timed auto-detach (Ghidra owns the session).
export NETCAP_LOG="$OPT_NETCAP_LOG"
export NETCAP_GROUPS="$OPT_NETCAP_GROUPS"
export NETCAP_INTERNAL=1
export NETCAP_SECONDS=0

"$OPT_GDB_PATH" \
  -q \
  -ex "set pagination off" \
  -ex "set confirm off" \
  -ex "set auto-solib-add off" \
  -ex "show version" \
  -ex "python import ghidragdb" \
  -ex "set architecture $OPT_ARCH" \
  -ex "echo Connecting to Wine stub $OPT_HOST:$OPT_PORT ...\n" \
  -ex "target remote $OPT_HOST:$OPT_PORT" \
  -ex "ghidra trace connect \"$GHIDRA_TRACE_RMI_ADDR\"" \
  -ex "ghidra trace start GunBound" \
  -ex "ghidra trace sync-enable" \
  -ex "source $NETCAP_PY" \
  -ex "set confirm on" \
  -ex "set pagination on"
