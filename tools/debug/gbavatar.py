# gbavatar.py — resolve the avatar-store handlers and the Head/Flag word order.
#
# Installs SAFE auto-continuing breakpoints (like gbcursor.py / netcap: never
# halt, no single-step, clean interrupt->delete->detach after GBAVATAR_SECONDS)
# on the avatar subsystem, and logs each hit:
#
#   0x44b170 / 0x44b330 / 0x44b460  the three Avatar-Store slot handlers
#       -> logs WHICH one fired (correlate with what you clicked) + ecx/arg1.
#   0x4141b0  LoadAvatarSprites (the compositor)
#       -> logs the 4 unpacked part codes  head/body/glasses/flag (stack args).
#   0x4dc5c0  LoadRoomSlotAvatar   -> slot=ecx, dumps the 8-byte avatarEquipped
#       record at ctx+0x458bc+slot*8 (the wire/room copy).
#   0x4431a0  LoadReadyRoomSlotAvatar -> slot=eax, dumps ctx+0x501fe+slot*8.
#
# Reading the record dump (4 shorts w0 w1 w2 w3): w0=Body, w2=Glasses (known);
# w1/w3 are Head vs Flag — whichever equals (0x8000|<your equipped flag id>)
# is the FLAG word. Equip a distinctive flag + Standard head first so exactly
# one of w1/w3 is non-Standard.
#
#   (gdb) source gbavatar.py     or use tools/debug/avatar-probe.sh
#
# Image base 0x400000, no ASLR — VAs are live addresses. ctx base 0x7a7ae0.

import gdb
import os
import struct
import threading

CTX = 0x7A7AE0
REC_ROOM = 0x458BC      # ctx+0x458bc + slot*8  (wire/room avatarEquipped copy)
REC_READY = 0x501FE     # ctx+0x501fe + slot*8  (ready-room copy)

LOG_PATH = os.environ.get("GBAVATAR_LOG", "/tmp/gb-avatar.log")
MAX_HITS = int(os.environ.get("GBAVATAR_MAX_HITS", "400"))
DURATION = float(os.environ.get("GBAVATAR_SECONDS", "0"))  # 0 = until Ctrl-C

_log = open(LOG_PATH, "a", buffering=1)
_n = [0]


def out(m):
    _log.write(m + "\n")
    gdb.write(m + "\n")


def _read(addr, size):
    try:
        return bytes(gdb.selected_inferior().read_memory(addr, size))
    except (gdb.MemoryError, gdb.error):
        return None


def _u32(addr):
    b = _read(addr, 4)
    return struct.unpack("<I", b)[0] if b else None


def _shorts(addr, n):
    b = _read(addr, 2 * n)
    return list(struct.unpack("<%dH" % n, b)) if b else None


def reg(name):
    try:
        return int(gdb.parse_and_eval("$" + name)) & 0xFFFFFFFF
    except Exception:
        return None


def _stack_arg(i):
    # cdecl: [esp+4] = arg1, [esp+8] = arg2 ...  (at function entry)
    esp = reg("esp")
    return _u32(esp + 4 * i) if esp is not None else None


def _fmt_rec(base, slot):
    if slot is None or slot > 15:
        return "slot=? (bad)"
    w = _shorts(CTX + base + slot * 8, 4)
    if w is None:
        return "slot=%d <unreadable>" % slot
    return ("slot=%d  w0/Body=0x%04x  w1=0x%04x  w2/Glasses=0x%04x  w3=0x%04x"
            % (slot, w[0], w[1], w[2], w[3]))


class Site(gdb.Breakpoint):
    def __init__(self, va, kind):
        super().__init__("*0x%x" % va, gdb.BP_BREAKPOINT, internal=False)
        self.silent = True
        self.kind = kind
        self.va = va

    def stop(self):
        _n[0] += 1
        if _n[0] > MAX_HITS:
            return False
        k = self.kind
        if k == "handler":
            out("HANDLER 0x%x  ecx=0x%08x arg1=0x%08x   <-- what did you just click?"
                % (self.va, reg("ecx") or 0, _stack_arg(1) or 0))
        elif k == "compose":
            out("LoadAvatarSprites head=0x%04x body=0x%04x glasses=0x%04x flag=0x%04x"
                % ((_stack_arg(1) or 0) & 0xffff, (_stack_arg(2) or 0) & 0xffff,
                   (_stack_arg(3) or 0) & 0xffff, (_stack_arg(4) or 0) & 0xffff))
        elif k == "room":
            out("LoadRoomSlotAvatar  " + _fmt_rec(REC_ROOM, reg("ecx")))
        elif k == "ready":
            out("LoadReadyRoomSlotAvatar  " + _fmt_rec(REC_READY, reg("eax")))
        return False


_detach = [False]
_timer = [None]


def _cleanup(reason):
    if _timer[0] is not None:
        _timer[0].cancel()
        _timer[0] = None
    out("#### gbavatar: %s — cleaning up, detaching ####" % reason)
    # Each gdb.execute() tried independently: if the remote already dropped
    # (see below), "delete"/"detach" raise but "quit" should still run rather
    # than being skipped by one earlier exception.
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
    # The remote (winedbg's gdbstub) can drop on its own - e.g. the game
    # crashing under Wine/wined3d, unrelated to our probe - well before
    # GBAVATAR_SECONDS elapses. Previously the timer thread below stayed
    # alive regardless and fired its gdb.post_event()/gdb.execute() callback
    # into GDB's Python interpreter after the session had already ended
    # (possibly mid-shutdown), which crashed GDB itself with a native
    # segfault (not a catchable Python exception) rather than just erroring.
    # Cancelling here as soon as the inferior is gone avoids that.
    if _timer[0] is not None:
        _timer[0].cancel()
        _timer[0] = None
    out("#### gbavatar: remote/inferior exited - nothing more to detach ####")


gdb.events.stop.connect(_on_stop)
gdb.events.exited.connect(_on_exit)
for va, kind in ((0x44B170, "handler"), (0x44B330, "handler"), (0x44B460, "handler"),
                 (0x4141B0, "compose"), (0x4DC5C0, "room"), (0x4431A0, "ready")):
    Site(va, kind)
out("#### gbavatar: probing avatar subsystem -> %s (cap %d) ####" % (LOG_PATH, MAX_HITS))
if DURATION > 0:
    out("#### gbavatar: auto-detach after %.0fs ####" % DURATION)

    def _fire():
        _detach[0] = True
        try:
            gdb.post_event(lambda: gdb.execute("interrupt"))
        except Exception as e:
            out("  (interrupt request error: %s)" % e)
    # daemon=True: if GDB itself is exiting (interpreter teardown after the
    # user quits, or the remote already dropped - see _on_exit above) this
    # thread is abruptly killed with it instead of firing its callback into
    # a torn-down interpreter, which is what crashed GDB natively last time.
    _timer[0] = threading.Timer(DURATION, _fire)
    _timer[0].daemon = True
    _timer[0].start()
