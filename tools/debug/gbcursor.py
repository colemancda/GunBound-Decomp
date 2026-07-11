# gbcursor.py — resolve the cursor-frame mystery on the live client.
#
# Logs the cursor draw each frame at 0x4139dc (right after `call FindSpriteFrame`):
#   $esi = the frame key passed in (g_cursorFrame)
#   $eax = the resolved sprite-frame node
#   plus the g_cursorFrame (0x7a7674) and g_frameCounter (0x793504) globals.
# Reading:
#   esi counts 0,1,2,... -> something writes the frame key at runtime.
#   esi==0 and node constant -> animation is inside that node (pixel ptr swap).
#
# SAFE like netcap: auto-continuing breakpoint (never halts), NO single-stepping,
# NO FinishBreakpoint, and a clean interrupt->delete->detach after NETCAP_SECONDS.
#   (gdb) source gbcursor.py     or use tools/debug/cursor-probe.sh
#
# Image base 0x400000, no ASLR — VAs are live addresses.

import gdb
import os
import struct
import threading

DRAW_VA        = 0x4139DC       # after call FindSpriteFrame (eax=node, esi=frame key)
G_CURSOR_FRAME = 0x7A7674
G_FRAME_COUNTER = 0x793504

LOG_PATH = os.environ.get("GBCURSOR_LOG", "/tmp/gb-cursor.log")
MAX_HITS = int(os.environ.get("GBCURSOR_MAX_HITS", "120"))   # frames to log
DURATION = float(os.environ.get("GBCURSOR_SECONDS", "0"))    # 0 = until Ctrl-C

_log = open(LOG_PATH, "a", buffering=1)
_n = [0]


def out(m):
    _log.write(m + "\n")
    gdb.write(m + "\n")


def _u32(addr):
    try:
        return struct.unpack("<I", bytes(gdb.selected_inferior().read_memory(addr, 4)))[0]
    except (gdb.MemoryError, gdb.error):
        return None


def reg(name):
    try:
        return int(gdb.parse_and_eval("$" + name)) & 0xFFFFFFFF
    except Exception:
        return None


class DrawBP(gdb.Breakpoint):
    def __init__(self):
        super().__init__("*0x%x" % DRAW_VA, gdb.BP_BREAKPOINT, internal=False)
        self.silent = True

    def stop(self):
        _n[0] += 1
        if _n[0] > MAX_HITS:
            return False
        esi = reg("esi")
        eax = reg("eax")
        out("frame#%-4d esi=%s node=%s g_cursorFrame=%s g_frameCounter=%s"
            % (_n[0],
               "%d" % esi if esi is not None else "?",
               "0x%08x" % eax if eax is not None else "?",
               "%s" % _u32(G_CURSOR_FRAME), "%s" % _u32(G_FRAME_COUNTER)))
        return False


_detach = [False]
_timer = [None]


def _cleanup(reason):
    if _timer[0] is not None:
        _timer[0].cancel()
        _timer[0] = None
    out("#### gbcursor: %s — cleaning up, detaching ####" % reason)
    for cmd in ("delete", "detach", "quit"):
        try:
            gdb.execute(cmd)
        except Exception as e:
            out("  (%s error: %s)" % (cmd, e))


def _on_stop(evt):
    if not _detach[0]:
        return
    _detach[0] = False
    _cleanup("budget reached")


def _on_exit(evt):
    # The remote can drop on its own (game crash under Wine/wined3d, unrelated
    # to this probe) before NETCAP_SECONDS elapses - cancel the pending timer
    # so its callback doesn't fire into a torn-down interpreter later and
    # crash GDB itself (see gbavatar.py's _on_exit for the full writeup of
    # the crash this caused there).
    if _timer[0] is not None:
        _timer[0].cancel()
        _timer[0] = None
    out("#### gbcursor: remote/inferior exited - nothing more to detach ####")


gdb.events.stop.connect(_on_stop)
gdb.events.exited.connect(_on_exit)
DrawBP()
out("#### gbcursor: logging cursor draw @0x%x -> %s (cap %d) ####" % (DRAW_VA, LOG_PATH, MAX_HITS))
if DURATION > 0:
    out("#### gbcursor: auto-detach after %.0fs ####" % DURATION)

    def _fire():
        _detach[0] = True
        try:
            gdb.post_event(lambda: gdb.execute("interrupt"))
        except Exception as e:
            out("  (interrupt request error: %s)" % e)
    # daemon=True: get killed with the interpreter on shutdown rather than
    # firing its callback into a torn-down GDB later.
    _timer[0] = threading.Timer(DURATION, _fire)
    _timer[0].daemon = True
    _timer[0].start()
