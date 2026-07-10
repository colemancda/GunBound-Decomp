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
import json

G_CURRENT_STATE = 0x7934D0
G_STATE_OBJECTS = 0x5B33F8
G_CLIENT_CTX    = 0x5B3484
# g_uiPanelManager (Panel.cpp): +4 = list head, +8 = tail; nodes are
# CPanelListNode { m_next@+0, m_prev@+4, m_panel@+8 }, null-terminated.
G_UI_PANEL_MGR  = 0x00E53C40

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


# --- g_clientContext export (offsets from src/cxx/ClientContext.h) --------------
def _cstr(addr, maxlen):
    b = _rd(addr, maxlen)
    if b is None:
        return None
    return b.split(b"\x00")[0].decode("latin1", "replace")


def _ip(v):
    return "%d.%d.%d.%d" % (v & 0xFF, (v >> 8) & 0xFF, (v >> 16) & 0xFF, (v >> 24) & 0xFF)


def _server_list(ctx):
    soa = ctx + 0x3F808
    count = _rd(soa, 1)[0]
    online = _rd(soa + 0x001, 16)
    sid = struct.unpack("<16H", _rd(soa + 0x012, 32))
    region = _rd(soa + 0x032, 16)
    ip = struct.unpack("<16I", _rd(soa + 0x1842, 64))
    port = struct.unpack("<16H", _rd(soa + 0x1882, 32))
    cur = struct.unpack("<16H", _rd(soa + 0x18c2, 32))
    # maxCapacity is stored big-endian (live: 100 -> bytes 00 64; LE read gave
    # 0x6400/25600). See ClientContext.h note. currentPlayers was 0 in all
    # samples so its byte order is still unconfirmed (left little-endian).
    cap = struct.unpack(">16H", _rd(soa + 0x18e2, 32))
    anim = _rd(soa + 0x1902, 16)
    servers = []
    for i in range(16):
        nm = _cstr(soa + 0x042 + i * 128, 128)
        if not (i < count or online[i] or nm):
            continue
        servers.append({
            "idx": i, "id": sid[i], "online": online[i], "region": region[i],
            "name": nm, "desc": _cstr(soa + 0x842 + i * 256, 256),
            "ip": _ip(ip[i]), "port": port[i],
            "players": cur[i], "maxCapacity": cap[i], "anim": anim[i],
        })
    return {
        "base": "0x%08x" % soa, "count": count,
        "selectedServerId": struct.unpack("<i", _rd(ctx + 0x3F804, 4))[0],
        "currentServerName": _cstr(ctx + 0x3B8E8, 64),
        "servers": servers,
    }


def _rooms(ctx):
    rooms = []
    for i in range(6):
        info = _u32(ctx + 0x44984 + i * 4)
        rooms.append({
            "slot": i,
            "cardId": struct.unpack("<H", _rd(ctx + 0x44664 + i * 2, 2))[0],
            "map": _rd(ctx + 0x4497C + i, 1)[0],
            "info": "0x%08x" % info, "fullness": (info >> 18) & 3,
            "flagA": _rd(ctx + 0x4499C + i, 1)[0], "flagB": _rd(ctx + 0x449A2 + i, 1)[0],
            "status": _rd(ctx + 0x449A8 + i, 1)[0], "lock": _rd(ctx + 0x449AE + i, 1)[0],
        })
    return rooms


def _players(ctx, maxslots=16):
    out = []
    for s in range(maxslots):
        nm = _cstr(ctx + 0x4467C + s * 0x80, 0x80)
        if nm:
            out.append({"slot": s, "name": nm})
    return out


def _peer(ctx):
    return {"addr": _ip(_u32(ctx + 0x23330)), "field4": "0x%08x" % _u32(ctx + 0x23334),
            "field8": "0x%08x" % _u32(ctx + 0x23338), "flagC": _rd(ctx + 0x2333C, 1)[0]}


def _inventory(ctx):
    items = []
    for i in range(16):
        w0 = _u32(ctx + 0x44BE8 + i * 0x9C)
        if w0:
            items.append({"slot": i, "word0": "0x%08x" % w0})
    return items


def _channel_roster(ctx):
    # The lobby/channel user list (CChannelUserListPanel). Found live at
    # ctx+0x41440 as ~0xD-byte, name-inline records (admin@+5, colemancda2@+0x12).
    # Scan the region for NUL-terminated printable names rather than assume the
    # exact stride (only 2 users were available to sample).
    region = _rd(ctx + 0x41440, 0x400) or b""
    users, i = [], 0
    while i < len(region):
        if 32 <= region[i] < 127:
            j = region.find(b"\x00", i)
            if j < 0:
                j = len(region)
            s = region[i:j]
            if len(s) >= 2 and all(32 <= b < 127 for b in s):
                users.append({"off": "ctx+0x%x" % (0x41440 + i), "name": s.decode("latin1")})
            i = j + 1
        else:
            i += 1
    return {"base": "ctx+0x41440", "users": users}


def _room_slots(ctx, maxslots=8):
    # Ready-Room (State 9) slot occupants. Found live at ctx+0x457f1 as 0xD-byte
    # records: a 12-byte NUL-terminated name buffer + a trailing status byte at
    # record+0xc (candidate ready/team flag - semantics inferred from one sample,
    # confirm by toggling Ready). Distinct from Ctx_roomPlayerName (+0x4467c, the
    # lobby room-card array, empty in-room).
    slots = []
    for s in range(maxslots):
        rec = ctx + 0x457F1 + s * 0xD
        nm = _cstr(rec, 0xC)
        st = _rd(rec + 0xC, 1)[0]
        if nm or st:
            slots.append({"slot": s, "name": nm, "status": st})
    return slots


def _local_user(ctx):
    # ctx+0x2331c holds the local account name (confirmed live). The struct
    # ClientContext.h calls "PeerEndpoint" (0x23330) overlaps a second copy.
    return {"off": "ctx+0x2331c", "name": _cstr(ctx + 0x2331C, 0x20)}


def _context_obj():
    ctx = _u32(G_CLIENT_CTX)
    if not ctx:
        return {"g_clientContext": 0, "note": "not allocated"}
    return {
        "g_clientContext": "0x%08x" % ctx,
        "localUser": _local_user(ctx),
        "serverList": _server_list(ctx),
        "channelRoster": _channel_roster(ctx),
        "roomSlots": _room_slots(ctx),
        "rooms": _rooms(ctx),
        "roomPlayers": _players(ctx),
        "peerEndpoint": _peer(ctx),
        "inventory": _inventory(ctx),
    }


def _find(needle, size=0x120000):
    """Scan the g_clientContext arena for a byte string; report ctx+offset hits."""
    ctx = _u32(G_CLIENT_CTX)
    if not ctx:
        print("g_clientContext not allocated")
        return
    data = _rd(ctx, size) or b""
    t = needle.encode("latin1") if isinstance(needle, str) else needle
    hits, idx = [], 0
    while len(hits) < 64:
        j = data.find(t, idx)
        if j < 0:
            break
        hits.append(j)
        idx = j + 1
    print("find %r in [ctx, ctx+0x%x): %d hit(s)" % (needle, size, len(hits)))
    for h in hits:
        print("  ctx+0x%-6x  (0x%08x)" % (h, ctx + h))


def _dump_ctx():
    doc = _context_obj()
    if not doc.get("serverList"):
        print("g_clientContext = %s (%s)" % (doc.get("g_clientContext"), doc.get("note")))
        return
    print("g_clientContext = %s" % doc["g_clientContext"])
    lu = doc["localUser"]
    print("localUser %s: %r" % (lu["off"], lu["name"]))
    cr = doc["channelRoster"]
    print("channelRoster %s: %s" % (cr["base"], [u["name"] for u in cr["users"]]))
    rs = doc["roomSlots"]
    if rs:
        print("roomSlots (ctx+0x457f1, 0xD stride):")
        for s in rs:
            print("  slot %d: status=0x%02x  %r" % (s["slot"], s["status"], s["name"]))
    sl = doc["serverList"]
    print("ServerList %s  count=%d  selected=%d  currentServerName=%r"
          % (sl["base"], sl["count"], sl["selectedServerId"], sl["currentServerName"]))
    for s in sl["servers"]:
        print("  [%2d] id=%-5d online=%d region=%d %s:%d  players=%d/%d anim=%d  %r"
              % (s["idx"], s["id"], s["online"], s["region"], s["ip"], s["port"],
                 s["players"], s["maxCapacity"], s["anim"], s["name"]))
    pl = doc["roomPlayers"]
    print("Room players (%d named):" % len(pl))
    for p in pl:
        print("  slot %2d: %r" % (p["slot"], p["name"]))
    print("Rooms (6 lobby slots):")
    for r in doc["rooms"]:
        if r["map"] or r["status"] or r["cardId"]:
            print("  slot %d: card=%d map=%d status=%d lock=%d full=%d info=%s"
                  % (r["slot"], r["cardId"], r["map"], r["status"], r["lock"],
                     r["fullness"], r["info"]))
    pe = doc["peerEndpoint"]
    print("PeerEndpoint: addr=%s field4=%s field8=%s flagC=%d"
          % (pe["addr"], pe["field4"], pe["field8"], pe["flagC"]))
    inv = doc["inventory"]
    print("Inventory: %d non-empty slots" % len(inv))


def _dump_widget(addr, depth, maxdepth, seen):
    # CWidget layout (Widget.h): +0x00 vtable, +0x04 m_focused, +0x08 m_parent,
    # +0x0c m_children (CAtlArray: m_pData@+0x0c, m_nSize@+0x10), +0x1c m_enabled,
    # +0x1e m_hidden, +0x20 m_typeId, +0x24 m_id, +0x28 x, +0x2c y, +0x30 w, +0x34 h.
    ind = "  " * depth
    if addr == 0:
        print(ind + "(null)")
        return
    if addr in seen:
        print(ind + "0x%08x (cycle)" % addr)
        return
    seen.add(addr)
    vt = _u32(addr)
    r = lambda off, fmt: struct.unpack("<" + fmt, _rd(addr + off, struct.calcsize(fmt)))[0]
    flags = ("F" if r(0x04, "B") else "-") + ("E" if r(0x1c, "B") else "-") + ("H" if r(0x1e, "B") else "-")
    cnt = r(0x10, "i")
    data = _u32(addr + 0x0c)
    print("%s0x%08x vt=%08x type=%d id=%d rect=(%d,%d %dx%d) [%s] children=%d"
          % (ind, addr, vt, r(0x20, "i"), r(0x24, "i"),
             r(0x28, "i"), r(0x2c, "i"), r(0x30, "i"), r(0x34, "i"), flags, cnt))
    if depth < maxdepth and 0 < cnt <= 256 and data:
        for i in range(cnt):
            _dump_widget(_u32(data + i * 4), depth + 1, maxdepth, seen)


def _dump_panels(maxdepth):
    head = _u32(G_UI_PANEL_MGR + 4)
    tail = _u32(G_UI_PANEL_MGR + 8)
    print("g_uiPanelManager @0x%08x  list head=0x%08x tail=0x%08x" % (G_UI_PANEL_MGR, head, tail))
    node, n, seen = head, 0, set()
    while node and node not in seen and n < 64:
        seen.add(node)
        n += 1
        panel = _u32(node + 8)
        print("--- panel #%d  node=0x%08x  panel=0x%08x ---" % (n, node, panel))
        _dump_widget(panel, 0, maxdepth, set())
        node = _u32(node)          # m_next
    if n == 0:
        print("(no panels attached to the manager)")


def _widget_obj(addr, depth, maxdepth, seen):
    if addr == 0:
        return None
    if addr in seen:
        return {"addr": "0x%08x" % addr, "cycle": True}
    seen.add(addr)
    r = lambda off, fmt: struct.unpack("<" + fmt, _rd(addr + off, struct.calcsize(fmt)))[0]
    cnt = r(0x10, "i")
    data = _u32(addr + 0x0c)
    node = {
        "addr": "0x%08x" % addr,
        "vtable": "0x%08x" % _u32(addr),
        "typeId": r(0x20, "i"),
        "id": r(0x24, "i"),
        "rect": {"x": r(0x28, "i"), "y": r(0x2c, "i"), "w": r(0x30, "i"), "h": r(0x34, "i")},
        "focused": bool(r(0x04, "B")),
        "enabled": bool(r(0x1c, "B")),
        "hidden": bool(r(0x1e, "B")),
        "childCount": cnt,
        "children": [],
    }
    if depth < maxdepth and 0 < cnt <= 256 and data:
        for i in range(cnt):
            c = _widget_obj(_u32(data + i * 4), depth + 1, maxdepth, seen)
            if c is not None:
                node["children"].append(c)
    return node


def _panels_obj(maxdepth):
    head = _u32(G_UI_PANEL_MGR + 4)
    panels, node, seen, n = [], head, set(), 0
    while node and node not in seen and n < 64:
        seen.add(node)
        n += 1
        panels.append(_widget_obj(_u32(node + 8), 0, maxdepth, set()))
        node = _u32(node)
    return {"manager": "0x%08x" % G_UI_PANEL_MGR, "head": "0x%08x" % head, "panels": panels}


def _state_obj_dict():
    sid = struct.unpack("<i", _rd(G_CURRENT_STATE, 4))[0]
    obj = _u32(G_STATE_OBJECTS + sid * 4)
    d = {"id": sid, "name": STATE_NAMES.get(sid, "?"),
         "object": "0x%08x" % obj, "vtable": "0x%08x" % _u32(obj) if obj else None,
         "fields": {}}
    for off, fmt, fname in FIELDS.get(sid, []):
        d["fields"][fname] = struct.unpack("<" + fmt, _rd(obj + off, struct.calcsize(fmt)))[0]
    return d


class GbState(gdb.Command):
    """Decode GunBound's live C++ GameState. Usage: gbstate [ctx [json path]|find <s>|raw [N]|widget <a> [d]|panels [d]|json [path]]"""

    def __init__(self):
        super().__init__("gbstate", gdb.COMMAND_USER)

    def invoke(self, arg, from_tty):
        args = arg.split()
        if args and args[0] == "ctx":
            if len(args) > 1 and args[1] == "json":
                path = args[2] if len(args) > 2 else "/tmp/gb-context.json"
                with open(path, "w") as fh:
                    json.dump(_context_obj(), fh, indent=2)
                print("gbstate: wrote %s" % path)
            else:
                _dump_ctx()
        elif args and args[0] == "raw":
            n = int(args[1], 0) if len(args) > 1 else 0x40
            sid = struct.unpack("<i", _rd(G_CURRENT_STATE, 4))[0]
            obj = _u32(G_STATE_OBJECTS + sid * 4)
            print(_hexdump(obj, _rd(obj, n)))
        elif args and args[0] == "widget":
            if len(args) < 2:
                print("usage: gbstate widget <addr> [maxdepth]   "
                      "(walks the CWidget/CPanel tree; get a root ptr from the "
                      "state object or the decompiler)")
                return
            addr = int(args[1], 0)
            maxdepth = int(args[2], 0) if len(args) > 2 else 8
            _dump_widget(addr, 0, maxdepth, set())
        elif args and args[0] == "find":
            if len(args) < 2:
                print("usage: gbstate find <string> [hexsize]")
                return
            size = int(args[2], 0) if len(args) > 2 else 0x120000
            _find(args[1], size)
        elif args and args[0] == "panels":
            maxdepth = int(args[1], 0) if len(args) > 1 else 8
            _dump_panels(maxdepth)
        elif args and args[0] == "json":
            path = args[1] if len(args) > 1 else "/tmp/gb-view.json"
            doc = {"gameState": _state_obj_dict(), "view": _panels_obj(16)}
            with open(path, "w") as fh:
                json.dump(doc, fh, indent=2)
            print("gbstate: wrote %s" % path)
        else:
            _dump_state()


GbState()
print("gbstate: registered. Try `gbstate`, `gbstate ctx`, `gbstate raw 0x80`.")
