# gbroomsettings.py — bind the Ready Room option labels (A SIDE / SSDEATH /
# ATTACK / DEATH72 / game-mode) to the 0x3101 settings-dword bit groups.
#
# The *encode* of the host room-options bitfield is already decoded statically
# (see docs/screens/09_ready_room.md): State09_ReadyRoom_OnCommand's buttonId
# (param_4) selects a case that writes one bit group of the guarded settings
# dword at state+0x26c, then re-sends it as opcode 0x3101. What is NOT in the
# code is which on-screen label is which group, because the host config toggles
# are image-mapped hit regions, not sprite-labelled widgets.
#
# This resolves it live: each time you click an option toggle, OnCommand fires
# with the buttonId, which THIS script maps to its group + bit range. So:
#   click the toggle you see labelled "A SIDE"  -> read the GROUP it prints.
# That is the binding. As a cross-check it also captures the actual settings
# dword the client re-sends (QueueOutgoingPacketField, filtered to OnCommand)
# and prints which bit group changed since the last send.
#
# Installs SAFE auto-continuing breakpoints (same pattern as gbavatar.py: never
# halt, no single-step, clean interrupt->delete->detach after GBROOM_SECONDS).
#
#   (gdb) source gbroomsettings.py     or use tools/debug/roomsettings-probe.sh
#
# Image base 0x400000, no ASLR — VAs are live addresses.

import gdb
import os
import struct
import threading

ONCOMMAND = 0x4D54E0            # State09_ReadyRoom_OnCommand (__thiscall)
ONCOMMAND_END = 0x4D6000        # end of its body (for caller filtering)
QUEUE_FIELD = 0x40A470          # QueueOutgoingPacketField(value); value @ [esp+4]

# buttonId (OnCommand param_4) -> (group label, bit range). These come straight
# from the static case decode; the point of the probe is to learn which visible
# toggle sends which of these buttonIds.
GROUPS = {
    0x28: ("A", "bits 0-3  (mask 0x0000000f)"),
    0x29: ("A", "bits 0-3  (mask 0x0000000f)"),
    0x2A: ("A", "bits 0-3  (mask 0x0000000f)"),
    0x1E: ("B", "bits 8-11 (mask 0x00000f00)"),
    0x1F: ("B", "bits 8-11 (mask 0x00000f00)"),
    0x20: ("B", "bits 8-11 (mask 0x00000f00)"),
    0x21: ("B", "bits 8-11 (mask 0x00000f00)"),
    0x32: ("C", "bits 12-13 (mask 0x00003000)"),
    0x33: ("C", "bits 12-13 (mask 0x00003000)"),
    0x34: ("C", "bits 12-13 (mask 0x00003000)"),
    0x35: ("C", "bits 12-13 (mask 0x00003000)"),
    0x3C: ("D", "bits 14-15 (mask 0x0000c000)"),
    0x3D: ("D", "bits 14-15 (mask 0x0000c000)"),
    0x3E: ("D", "bits 14-15 (mask 0x0000c000)"),
    0x0A: ("E/game-mode", "bits 18-23 (mask 0x00fc0000)"),
    0x0B: ("E/game-mode", "bits 18-23 (mask 0x00fc0000)"),
    0x0C: ("E/game-mode", "bits 18-23 (mask 0x00fc0000)"),
    0x0D: ("E/game-mode", "bits 18-23 (mask 0x00fc0000)"),
    0x46: ("map-variant", "bits 16-17 (mask 0x00030000)"),
    0x47: ("map-variant", "bits 16-17 (mask 0x00030000)"),
    0x48: ("map-variant", "bits 16-17 (mask 0x00030000)"),
}

# group masks for the settings-dword diff cross-check
GROUP_MASKS = [
    ("A", 0x0000000F), ("B", 0x00000F00), ("C", 0x00003000),
    ("D", 0x0000C000), ("map-variant", 0x00030000), ("E/game-mode", 0x00FC0000),
]

LOG_PATH = os.environ.get("GBROOM_LOG", "/tmp/gb-roomsettings.log")
MAX_HITS = int(os.environ.get("GBROOM_MAX_HITS", "400"))
DURATION = float(os.environ.get("GBROOM_SECONDS", "0"))  # 0 = until Ctrl-C

_log = open(LOG_PATH, "a", buffering=1)
_n = [0]
_prev_settings = [None]


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


def reg(name):
    try:
        return int(gdb.parse_and_eval("$" + name)) & 0xFFFFFFFF
    except Exception:
        return None


def _changed_groups(new, prev):
    if prev is None:
        return "(first send — no prior value to diff)"
    diff = new ^ prev
    hit = [("%s [%s]" % (g, _fmt_bits(new, m)))
           for (g, m) in GROUP_MASKS if diff & m]
    return "changed: " + (", ".join(hit) if hit else "(no group bits changed)")


def _fmt_bits(val, mask):
    # value of this group, shifted down to its low bit
    shift = (mask & -mask).bit_length() - 1
    return "0x%x -> %d" % (mask, (val & mask) >> shift)


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
        if self.kind == "oncommand":
            self._oncommand()
        elif self.kind == "queue":
            self._queue()
        return False  # never halt — auto-continue

    def _oncommand(self):
        esp = reg("esp")
        if esp is None:
            return
        event_type = _u32(esp + 4)      # param_2
        button_id = _u32(esp + 0xC)     # param_4
        if event_type != 0 or button_id is None:
            return                       # only button-press events
        g = GROUPS.get(button_id & 0xFFFF)
        if g is None:
            return                       # not an option toggle — ignore
        out("CLICK  buttonId=0x%02x  ->  GROUP %s  %s   <-- which label did you click?"
            % (button_id & 0xFFFF, g[0], g[1]))

    def _queue(self):
        esp = reg("esp")
        if esp is None:
            return
        ret = _u32(esp)                 # caller return address
        if ret is None or not (ONCOMMAND <= ret < ONCOMMAND_END):
            return                       # only the room-settings sends
        val = _u32(esp + 4)             # the value being queued = new settings dword
        if val is None:
            return
        out("   settings=0x%08x  %s" % (val, _changed_groups(val, _prev_settings[0])))
        _prev_settings[0] = val


_detach = [False]
_timer = [None]


def _cleanup(reason):
    if _timer[0] is not None:
        _timer[0].cancel()
        _timer[0] = None
    out("#### gbroomsettings: %s — cleaning up, detaching ####" % reason)
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
    if _timer[0] is not None:
        _timer[0].cancel()
        _timer[0] = None
    out("#### gbroomsettings: remote/inferior exited — nothing to detach ####")


gdb.events.stop.connect(_on_stop)
gdb.events.exited.connect(_on_exit)
Site(ONCOMMAND, "oncommand")
Site(QUEUE_FIELD, "queue")
out("#### gbroomsettings: probing Ready Room option toggles -> %s (cap %d) ####"
    % (LOG_PATH, MAX_HITS))
out("#### In a room you HOST, click each option toggle once and read its GROUP. ####")
if DURATION > 0:
    out("#### gbroomsettings: auto-detach after %.0fs ####" % DURATION)

    def _fire():
        _detach[0] = True
        try:
            gdb.post_event(lambda: gdb.execute("interrupt"))
        except Exception as e:
            out("  (interrupt request error: %s)" % e)
    _timer[0] = threading.Timer(DURATION, _fire)
    _timer[0].daemon = True
    _timer[0].start()
