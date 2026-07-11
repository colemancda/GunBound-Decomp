# netcap.py — capture ground-truth test vectors for GunBound's network
# encode/checksum functions by breakpointing them on the live client (via the
# winedbg gdb stub) and logging inputs and outputs.
#
# Load from a gdb already connected to the stub:  (gdb) source netcap.py
# Or use tools/debug/capture-net-vectors.sh which does the whole thing headless.
#
# DESIGN: every breakpoint auto-continues (stop() returns False) and does NOTHING
# but read registers/memory. There is deliberately NO gdb.FinishBreakpoint and NO
# single-stepping: FinishBreakpoint over the winedbg remote stub trips a gdb
# assertion (finish_step_over), and a gdb crash leaves the game frozen at a
# breakpoint. "Output" is captured with ordinary breakpoints planted at the
# functions' fixed `ret` addresses instead.
#
# Addresses/conventions from objdump -M intel on orig/GunBound.gme (base 0x400000,
# no ASLR, so VAs == live addresses):
#   PeekPacketChecksumState  0x40a2e0  entry: state obj in EAX
#   EncodeOutgoingPacketField 0x40a380 entry: state obj in EDI, value [esp+4]
#   EncodeChecksumState      0x40a4a0  entry: state in EAX;  ret 0x40a4cb: EAX=state
#   AddToPacketChecksum      0x40aab0  entry: state EAX, add value [esp+4]
#   SubFromPacketChecksum    0x40aaf0  entry: state EAX, sub value [esp+4]
#   BuildSystemInfoBlob      0x40d260  entry: out ptr [esp+4]; ret 0x40d365: out ptr [esp+4]
#   ReceiveFramedPackets     0x4e5610  entry/ret: conn ctx EBX; buf [EBX+0x230], len [EBX+0x4230]

import gdb
import os
import time
import threading

LOG_PATH = os.environ.get("NETCAP_LOG", "/tmp/gunbound-netvectors.log")
MAX_HITS = int(os.environ.get("NETCAP_MAX_HITS", "25"))   # per breakpoint
DURATION = float(os.environ.get("NETCAP_SECONDS", "0"))   # 0 = until Ctrl-C / disconnect
# Comma list to limit which groups install: checksum, blob, recv (default all).
GROUPS = set(os.environ.get("NETCAP_GROUPS", "checksum,blob,recv").split(","))
# When embedded in the Ghidra Debugger launcher, make the loggers internal so they
# don't clutter Ghidra's breakpoint list or churn its trace sync. Standalone (the
# headless capture) keeps them visible.
INTERNAL = os.environ.get("NETCAP_INTERNAL", "0") == "1"

_log = open(LOG_PATH, "a", buffering=1)
_hits = {}


def out(msg):
    _log.write(msg + "\n")
    gdb.write(msg + "\n")


def reg(name):
    try:
        return int(gdb.parse_and_eval("$" + name)) & 0xFFFFFFFF
    except Exception:
        return None


def rd(addr, n):
    if addr is None:
        return None
    try:
        return bytes(gdb.selected_inferior().read_memory(addr, n))
    except (gdb.MemoryError, gdb.error):
        return None


def hexs(b):
    return b.hex().upper() if b else "<unreadable>"


def dword_at(addr):
    b = rd(addr, 4)
    return int.from_bytes(b, "little") if b else None


def regs_line():
    return "  regs eax=%08x ecx=%08x edx=%08x ebx=%08x esi=%08x edi=%08x esp=%08x ebp=%08x" % tuple(
        (reg(r) or 0) for r in ("eax", "ecx", "edx", "ebx", "esi", "edi", "esp", "ebp"))


def stackargs(n=2):
    esp = reg("esp")
    parts = []
    for i in range(1, n + 1):
        v = dword_at(esp + 4 * i) if esp is not None else None
        parts.append("arg%d=%s" % (i, "%08x" % v if v is not None else "??"))
    return "  " + " ".join(parts)


def _base(spec):
    """spec base: 'reg:eax' -> $eax ; 'sarg:1' -> *(esp+4) (a pointer)."""
    kind, val = spec.split(":")
    if kind == "reg":
        return reg(val)
    if kind == "sarg":
        esp = reg("esp")
        return dword_at(esp + 4 * int(val)) if esp is not None else None
    return None


class NetBP(gdb.Breakpoint):
    def __init__(self, addr, name, mems=None, value_arg=False):
        super().__init__("*0x%x" % addr, gdb.BP_BREAKPOINT, internal=INTERNAL)
        self.name = name
        self.mems = mems or []          # list of (base_spec, offset, length, label)
        self.value_arg = value_arg
        self.silent = True

    def stop(self):
        n = _hits.get(self.name, 0) + 1
        _hits[self.name] = n
        if n > MAX_HITS:
            return False                 # capped; keep running silently
        out("== %s  (hit %d/%d)  t=%.3f" % (self.name, n, MAX_HITS, time.time()))
        out(regs_line())
        if self.value_arg:
            out(stackargs(2))
        for base_spec, off, length, label in self.mems:
            base = _base(base_spec)
            if base is None:
                out("  %s: <no base %s>" % (label, base_spec))
                continue
            addr = base + off
            out("  %s @%08x: %s" % (label, addr, hexs(rd(addr, length))))
        return False                     # ALWAYS auto-continue; never halt the game


def install():
    n = 0
    if "checksum" in GROUPS:
        NetBP(0x40a2e0, "PeekPacketChecksumState",   [("reg:eax", 0, 0x20, "state")]); n += 1
        NetBP(0x40a380, "EncodeOutgoingPacketField", [("reg:edi", 0, 0x20, "state")], value_arg=True); n += 1
        NetBP(0x40a4a0, "EncodeChecksumState.entry", [("reg:eax", 0, 0x20, "state")]); n += 1
        NetBP(0x40a4cb, "EncodeChecksumState.ret",   [("reg:eax", 0, 0x20, "state_out")]); n += 1
        NetBP(0x40aab0, "AddToPacketChecksum",       [("reg:eax", 0, 0x20, "state")], value_arg=True); n += 1
        NetBP(0x40aaf0, "SubFromPacketChecksum",     [("reg:eax", 0, 0x20, "state")], value_arg=True); n += 1
    if "blob" in GROUPS:
        NetBP(0x40d260, "BuildSystemInfoBlob.entry", value_arg=True); n += 1
        NetBP(0x40d365, "BuildSystemInfoBlob.ret",   [("sarg:1", 0, 0x60, "blob_out")]); n += 1
    if "recv" in GROUPS:
        recv_mems = [("reg:ebx", 0x230, 0x80, "recvbuf"), ("reg:ebx", 0x4230, 4, "buflen")]
        NetBP(0x4e5610, "ReceiveFramedPackets.entry", recv_mems); n += 1
        for ret in (0x4e576f, 0x4e5797, 0x4e57bf):   # data-path returns
            NetBP(ret, "ReceiveFramedPackets.ret@%x" % ret, recv_mems); n += 1
    out("\n#### netcap installed %d breakpoints, groups=%s, log=%s, cap=%d/bp ####"
        % (n, ",".join(sorted(GROUPS)), LOG_PATH, MAX_HITS))
    return n


# --- clean timed auto-detach ---------------------------------------------------
# Deleting breakpoints / detaching requires a STOPPED target. You cannot do it from
# inside a post_event that then blocks (gdb's event loop is stalled, the stop never
# lands). So: the timer just requests an `interrupt`; the real cleanup happens in a
# gdb stop-event handler that fires once the target genuinely halts. And we NEVER
# hard-kill winedbg (attach mode = KillOnExit — that would take the game with it).
_detach_requested = False
_timer = None


def _on_stop(event):
    global _detach_requested
    if not _detach_requested:
        return
    _detach_requested = False
    out("\n#### netcap: budget reached — deleting breakpoints, detaching, quitting ####")
    for cmd in ("delete", "detach", "quit"):   # tried independently - see _on_exit
        try:
            gdb.execute(cmd)
        except Exception as e:
            out("  (%s error: %s)" % (cmd, e))


def _on_exit(event):
    # The remote (winedbg's gdbstub) can drop on its own - e.g. the game
    # crashing under Wine/wined3d, unrelated to this probe - well before
    # NETCAP_SECONDS elapses. The timer below used to stay alive regardless
    # and fire its gdb.post_event()/gdb.execute() callback into GDB's Python
    # interpreter after the session had already ended, which crashed GDB
    # itself with a native segfault rather than a catchable exception (seen
    # in practice on gbavatar.py, which shares this exact pattern - see that
    # file's _on_exit for the full writeup). Cancelling here avoids it.
    global _timer
    if _timer is not None:
        _timer.cancel()
        _timer = None
    out("#### netcap: remote/inferior exited - nothing more to detach ####")


def _request_detach():
    global _detach_requested
    _detach_requested = True
    try:
        gdb.post_event(lambda: gdb.execute("interrupt"))   # quick, non-blocking
    except Exception as e:
        out("  (interrupt request error: %s)" % e)


gdb.events.stop.connect(_on_stop)
gdb.events.exited.connect(_on_exit)
install()
if DURATION > 0:
    out("#### netcap: will auto-detach after %.0fs ####" % DURATION)
    # daemon=True: get killed with the interpreter on shutdown rather than
    # firing its callback into a torn-down GDB later.
    _timer = threading.Timer(DURATION, _request_detach)
    _timer.daemon = True
    _timer.start()
