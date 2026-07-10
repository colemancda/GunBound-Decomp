# gbstate.py — read GunBound's live C++ GameState (and client context) over the
# winedbg gdb stub, decoding fields by the names/offsets from src/cxx/GameState.h
# and src/cxx/ClientContext.h.
#
#   (gdb) source gbstate.py       # registers the `gbstate` command
#   (gdb) gbstate                 # dump the current CGameState* object, named fields
#   (gdb) gbstate ctx             # dump the server-list SoA from g_clientContext
#   (gdb) gbstate raw 0x80        # hexdump N bytes of the current state object
#
# Anchors (globals.h / ARCHITECTURE.md, image base 0x400000, no ASLR):
#   g_currentGameState  int32   @ 0x7934d0   (state id 0..15)
#   g_gameStateObjects  ptr[16] @ 0x5b33f8   (per-state object pointers)
#   g_clientContext     int32   @ 0x5b3484   (holds the base ADDRESS of the arena)
#
# Works standalone or alongside netcap.py. Read-only; never modifies the target.

import gdb
import struct

G_CURRENT_STATE = 0x7934D0
G_STATE_OBJECTS = 0x5B33F8
G_CLIENT_CTX    = 0x5B3484

STATE_NAMES = {
    0: "NULL", 1: "Title", 2: "ServerSelect", 3: "GameRoomList", 5: "Logo1",
    6: "Logo2", 7: "AvatarStore", 9: "ReadyRoom", 10: "Loading",
    11: "InBattle", 15: "Quit",
}

# (offset, fmt, name).  fmt: struct code — B/b u8/i8, H/h u16/i16, I/i u32/i32.
FIELDS = {
    1:  [(0x04, "i", "m_frameCounter")],
    5:  [(0x04, "i", "m_frameCounter")],
    6:  [(0x04, "i", "m_frameCounter")],
    2:  [
        (0x04, "B", "m_connecting"), (0x05, "B", "m_sendHandshake"),
        (0x06, "B", "m_uiDirty"),    (0x07, "B", "m_wantInitialList"),
        (0x08, "i", "m_highlightedSlot"), (0x0c, "i", "m_unk0c"),
        (0x10, "B", "m_viewMode"),   (0x14, "i", "m_scrollA"),
        (0x18, "i", "m_scrollOffset"), (0x1c, "i", "m_unk1c"),
        (0x20, "i", "m_tickCounter"), (0x24, "B", "m_inputEnabled"),
        (0x68, "i", "m_connectingSlot"),
    ],
    3:  [
        (0x04, "i", "m_selectedRoom"), (0x08, "i", "m_hoveredRoom"),
        (0x11c, "i", "m_unk11c"), (0x288, "B", "m_unk288"),
    ],
}
# States whose field map isn't reconstructed — show size + a hexdump instead.
OPAQUE_SIZE = {7: 0x34818, 9: 0x78c, 10: 0x150, 11: 0x2408}


def _rd(addr, n):
    try:
        return bytes(gdb.selected_inferior().read_memory(addr, n))
    except (gdb.MemoryError, gdb.error) as e:
        raise gdb.GdbError("read @%#x failed: %s" % (addr, e))


def _u32(addr):
    return struct.unpack("<I", _rd(addr, 4))[0]


def _hexdump(base, data):
    lines = []
    for i in range(0, len(data), 16):
        chunk = data[i:i + 16]
        hx = " ".join("%02x" % b for b in chunk)
        asc = "".join(chr(b) if 32 <= b < 127 else "." for b in chunk)
        lines.append("  %08x  %-47s  %s" % (base + i, hx, asc))
    return "\n".join(lines)


def _dump_state():
    sid = struct.unpack("<i", _rd(G_CURRENT_STATE, 4))[0]
    pending = struct.unpack("<i", _rd(G_CURRENT_STATE + 4, 4))[0]
    name = STATE_NAMES.get(sid, "?")
    obj = _u32(G_STATE_OBJECTS + sid * 4)
    print("g_currentGameState = %d (%s)   g_pendingGameState = %d (%s)"
          % (sid, name, pending, STATE_NAMES.get(pending, "?")))
    print("state object  = 0x%08x" % obj)
    if obj == 0:
        print("  (null object)")
        return
    print("vtable        = 0x%08x" % _u32(obj))
    fields = FIELDS.get(sid)
    if fields:
        print("CState%02d%s fields:" % (sid, name))
        for off, fmt, fname in fields:
            size = struct.calcsize("<" + fmt)
            val = struct.unpack("<" + fmt, _rd(obj + off, size))[0]
            print("  +0x%03x  %-20s = %d (0x%x)" % (off, fname, val, val & 0xFFFFFFFF))
    else:
        n = min(OPAQUE_SIZE.get(sid, 0x40), 0x80)
        print("(no reconstructed field map; first %#x bytes)" % n)
        print(_hexdump(obj, _rd(obj, n)))


def _dump_ctx():
    ctx = _u32(G_CLIENT_CTX)
    print("g_clientContext base = 0x%08x" % ctx)
    if ctx == 0:
        print("  (not yet allocated)")
        return
    soa = ctx + 0x3F808
    count = _rd(soa, 1)[0]
    sel = struct.unpack("<i", _rd(ctx + 0x3F804, 4))[0]
    print("ServerListSoA @0x%08x  count=%d  selectedServerId=%d" % (soa, count, sel))
    online = _rd(soa + 0x001, 16)
    sid_arr = struct.unpack("<16H", _rd(soa + 0x012, 32))
    cur = struct.unpack("<16H", _rd(soa + 0x18c2, 32))
    cap = struct.unpack("<16H", _rd(soa + 0x18e2, 32))
    for i in range(min(count if count <= 16 else 16, 16)):
        nm = _rd(soa + 0x042 + i * 128, 128).split(b"\x00")[0].decode("latin1", "replace")
        print("  [%2d] id=%-5d online=%d players=%d/%d  %r"
              % (i, sid_arr[i], online[i], cur[i], cap[i], nm))


class GbState(gdb.Command):
    """Decode GunBound's live C++ GameState. Usage: gbstate [ctx|raw [N]]"""

    def __init__(self):
        super().__init__("gbstate", gdb.COMMAND_USER)

    def invoke(self, arg, from_tty):
        args = arg.split()
        if args and args[0] == "ctx":
            _dump_ctx()
        elif args and args[0] == "raw":
            n = int(args[1], 0) if len(args) > 1 else 0x40
            sid = struct.unpack("<i", _rd(G_CURRENT_STATE, 4))[0]
            obj = _u32(G_STATE_OBJECTS + sid * 4)
            print(_hexdump(obj, _rd(obj, n)))
        else:
            _dump_state()


GbState()
print("gbstate: registered. Try `gbstate`, `gbstate ctx`, `gbstate raw 0x80`.")
