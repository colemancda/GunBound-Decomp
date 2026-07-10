#!/usr/bin/bash
#@title gdb (wine remote stub)
#@desc <html><body width="300px">
#@desc   <h3>Connect to a running <tt>winedbg --gdb</tt> stub</h3>
#@desc   <p>Attaches Ghidra's <tt>gdb</tt> to a Wine gdb remote stub that is
#@desc   already listening (start it with <tt>tools/debug/wine-gdbstub.sh</tt>).
#@desc   The GunBound client image loads at 0x400000, so it maps 1:1 onto the
#@desc   <tt>GunBound.gme</tt> program in this project.</p>
#@desc </body></html>
#@menu-group gdb
#@icon icon.debugger
#@help TraceRmiLauncherServicePlugin#gdb
#@env OPT_GDB_PATH:str="gdb" "Path to gdb" "The path to gdb. Omit the full path to resolve using the system PATH."
#@env OPT_HOST:str="localhost" "Stub host" "Host where the winedbg gdb stub is listening."
#@env OPT_PORT:str="12345" "Stub port" "TCP port passed to wine-gdbstub.sh."
#@env OPT_ARCH:str="i386" "Architecture" "gdb architecture of the guest (GunBound is 32-bit i386)."

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

# Notes on the option flags below:
#  - auto-solib-add off: don't try to load Wine's host ELF .so symbols (noise/errors).
#  - set architecture $OPT_ARCH: force the 32-bit i386 view the stub exposes.
#  - target remote: attach to the already-stopped GunBound process in the stub.
#  - sync-enable records the current (stopped) frame into the trace immediately and
#    installs stop-hooks, so the CPU/PC syncs onto the listing on every subsequent stop.
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
  -ex "set confirm on" \
  -ex "set pagination on"
