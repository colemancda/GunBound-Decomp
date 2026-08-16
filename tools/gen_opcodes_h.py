#!/usr/bin/env python3
"""Generate include/opcodes.h from the server repo's Opcode.swift.

The C tree dispatches on bare hex literals (`opcode == 0x3020`,
`case 0x4412:`), and the only complete, named opcode list lives in the
Swift server (Sources/GunBoundProtocol/Opcode.swift - `enum Opcode:
UInt16` with the original SVC_* names as trailing comments).  This
script turns that enum into `#define GB_OP_<SWIFT_CASE_NAME> 0xNNNN`
macros so the C can name opcodes without the two repos drifting apart.

Names are derived mechanically from the Swift case name (camelCase ->
UPPER_SNAKE), never invented, and the SVC_* comment is carried along
where the Swift source has one.  Re-run after editing Opcode.swift:

    python3 tools/gen_opcodes_h.py [path/to/Opcode.swift]

Default path: ~/Developer/GunBound/Sources/GunBoundProtocol/Opcode.swift
"""
import os
import re
import sys

DEFAULT = os.path.expanduser(
    "~/Developer/GunBound/Sources/GunBoundProtocol/Opcode.swift")
OUT = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                   "..", "include", "opcodes.h")

CASE = re.compile(
    r"^\s*case\s+(\w+)\s*=\s*0x([0-9A-Fa-f]{1,4})\s*(?://\s*(.*?))?\s*$")
MARK = re.compile(r"^\s*//\s*MARK:\s*-\s*(.*?)\s*$")


# Channel-2 (ProcessBattleAction) ACTION codes.  These are a different
# namespace from the packet opcodes above - the u16 at +0x02 of the 33-byte
# battle-action header - and the server enum does not carry them, so they
# are maintained here by hand from CONSTANTS.md section 4 plus what the
# 2026-08 CValueGuard sweep confirmed from the handlers themselves.  Only
# CONFIRMED meanings get a name; codes CONSTANTS.md still marks tentative
# are listed as comments so their existence is visible without asserting a
# meaning.  Keep in step with CONSTANTS.md when either changes.
ACTIONS = """
/* --- Channel-2 battle ACTION codes (ProcessBattleAction, +0x02 of the ---
 * --- 33-byte action header).  Not part of the server's Opcode enum.  --- */
#define GB_ACT_NOTIFICATION_TOAST                    0x0003
#define GB_ACT_PLAYER_INFO_SYNC                      0x8000
#define GB_ACT_CHAT_BUFFER_UPDATE                    0x8003
#define GB_ACT_UI_REFRESH                            0x8004
#define GB_ACT_FIELD_RELAY                           0x8005
#define GB_ACT_FIRE_FEEDBACK_SOUND                   0x8006
#define GB_ACT_MOBILE_MODEL_SYNC                     0x8100
#define GB_ACT_MAP_SELECTION_SYNC                    0x8101
#define GB_ACT_ALL_PLAYERS_READY                     0x8102
#define GB_ACT_SHOW_RESULT_CONFIRM                   0x8104
#define GB_ACT_KICK_FROM_ROOM                        0x8200
#define GB_ACT_MOBILE_MODEL_SYNC_ALT                 0x8400
#define GB_ACT_AIM_RELAY                             0x8402  /* angle+power, +0x243/+0x2cc */
#define GB_ACT_FIRE                                  0x8403  /* "ifire"; 8 server-resolved u16 */
#define GB_ACT_HIT_LOG                               0x8404
#define GB_ACT_WEAPON_SELECT_SOUND                   0x8405
#define GB_ACT_AIM_RELAY_ALT                         0x8406
#define GB_ACT_CHECKSUM_KEEPALIVE                    0x8407
#define GB_ACT_PLAYER_SPAWN                          0x8408
#define GB_ACT_POSITION_RELAY                        0x8500  /* also a replay-event code */
#define GB_ACT_GAME_START_COUNTDOWN                  0x9002  /* countdown := 0x31 */
#define GB_ACT_TURN_START                            0xC300  /* BeginNewTurn */
#define GB_ACT_TURN_SETUP                            0xC301  /* turn-timer + wind/spawn write */
#define GB_ACT_TURN_PHASE                            0xC303
#define GB_ACT_MOVEMENT                              0xC304  /* 4-bit dir | 0x10 running */
#define GB_ACT_TURN_TIMEOUT                          0xC305
#define GB_ACT_AIM_CONFIRM                           0xC306
#define GB_ACT_WIND_UPDATE                           0xC308
#define GB_ACT_SCHED_CHECKPOINT                      0xC400  /* no-op */
#define GB_ACT_TIMEOUT_WEAPON_SELECT                 0xC401
#define GB_ACT_FIRE_COMMITTED                        0xC409
#define GB_ACT_TIMEOUT_BOOKKEEPING                   0xC40B  /* all 8 slots */
#define GB_ACT_PERIODIC_STATUS                       0xC801
#define GB_ACT_QUIT                                  0xF008
#define GB_ACT_CHANGE_MOBILE                         0xF009  /* ChangePlayerMobile */
#define GB_ACT_PLAYER_FIELD_QUERY                    0xF00A
#define GB_ACT_TERRAIN_DEFORM                        0xF00B  /* crater frame swap */
/* Seen but still marked tentative in CONSTANTS.md, so left unnamed:
 *   0x0001 (ready-room player-data load), 0x4001-0x4006 (in-battle chat /
 *   status relays; 0x4002 is proximity chat), 0xC40A (final position sync).
 * Confirmed never implemented (default no-op): 0xC302, 0xC307, 0xC309,
 *   0xC402-0xC408. */
"""


def snake(name):
    s = re.sub(r"(?<=[a-z0-9])(?=[A-Z])", "_", name)
    s = re.sub(r"(?<=[A-Z])(?=[A-Z][a-z])", "_", s)
    return s.upper()


def main():
    src = sys.argv[1] if len(sys.argv) > 1 else DEFAULT
    lines = open(src, encoding="utf-8").read().splitlines()
    out = []
    out.append("/* include/opcodes.h - GunBound wire opcodes.")
    out.append(" *")
    out.append(" * GENERATED by tools/gen_opcodes_h.py from the server repo's")
    out.append(" * Sources/GunBoundProtocol/Opcode.swift - do not hand-edit; re-run the")
    out.append(" * generator after changing the Swift enum so both repos stay in step.")
    out.append(" *")
    out.append(" * Macro names are the Swift case names in UPPER_SNAKE with a GB_OP_")
    out.append(" * prefix; where the Swift source carries the original SVC_* name as a")
    out.append(" * trailing comment it is repeated here.  Values are the 16-bit opcode")
    out.append(" * as the client compares it (`opcode == 0x3020`, `case 0x4412:`).")
    out.append(" * See CONSTANTS.md section 3/4 and PROTOCOL.md for what each one does.")
    out.append(" */")
    out.append("#ifndef GB_OPCODES_H")
    out.append("#define GB_OPCODES_H")
    out.append("")
    seen = {}
    n = 0
    for ln in lines:
        m = MARK.match(ln)
        if m:
            out.append("")
            out.append("/* --- %s --- */" % m.group(1))
            continue
        m = CASE.match(ln)
        if not m:
            continue
        name, hexv, comment = m.group(1), m.group(2).upper(), m.group(3)
        macro = "GB_OP_" + snake(name)
        val = int(hexv, 16)
        if macro in seen:
            sys.exit("duplicate macro %s (%s vs %s)" % (macro, seen[macro], hexv))
        seen[macro] = hexv
        line = "#define %-44s 0x%04X" % (macro, val)
        if comment:
            line += "  /* %s */" % comment.strip()
        out.append(line)
        n += 1
    out.append("")
    out.append(ACTIONS.rstrip())
    out.append("")
    out.append("#endif /* GB_OPCODES_H */")
    open(OUT, "w", encoding="utf-8", newline="\n").write("\n".join(out) + "\n")
    print("wrote %s: %d opcodes" % (os.path.relpath(OUT), n))


if __name__ == "__main__":
    main()
