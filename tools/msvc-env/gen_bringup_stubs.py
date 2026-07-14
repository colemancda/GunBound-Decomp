#!/usr/bin/env python3
"""Generate no-op stub .c files for every symbol still unresolved in the
MSVC link attempt, so the bring-up exe never jumps to a zeroed /FORCE
call target. Reads link.log, writes bringup_stubs_*.c next to it.

Decorated-name classes handled:
  @name@N   -> int __fastcall name(int a1..a{N/4})      { return 0; }
  _name@N   -> int __stdcall  name(int a1..a{N/4})      { return 0; }
  _name     -> int            name()                    { return 0; }

Every stub returns 0: pointer-returning callees are null-checked at the
raw-port call sites, so 0 degrades to "feature absent" instead of a
crash. One file per (convention, argbytes) class because the same
identifier can be unresolved under several decorations (e.g.
@PanelManager_BringToFront@0 AND @4) and each spelling needs its own TU.

MANUAL_STUBS below are the exceptions to that "return 0 is safe" rule:
symbols whose raw-port callers do NOT null-check the result, so a 0
return is itself the crash. Each entry supplies a hand-written body that
satisfies the invariant its callers actually rely on. They are emitted
to bringup_stubs_manual.c (same bringup_stubs_* glob the link script
already cleans, compiles and links) and excluded from the auto groups.

Usage: gen_bringup_stubs.py <link.log> <outdir>
"""
import re
import sys
from collections import defaultdict

log_path, outdir = sys.argv[1], sys.argv[2]

# Decorated symbol -> hand-written definition. See the module docstring.
MANUAL_STUBS = {
    "_FUN_004d2170": r"""
/* FUN_004d2170 (0x004d2170) - the network-connection constructor, dropped
 * from the bring-up link (see bringup_drop.txt) because its raw port spawns
 * the real socket thread. The auto-generated `return 0` stub could not stand
 * in for it: WinMain does
 *
 *     pvVar4 = operator_new(0x84f0);
 *     DAT_005b2b58 = FUN_004d2170(pvVar4, 0, &DAT_00795070);   // 5c / 60 too
 *
 * so a 0 return leaves all three connection globals NULL - and the raw ports
 * that consume them do NOT null-check the outer object. ProcessIncomingPackets
 * (called every tick from PumpBattleActions, ungated by game state) does:
 *
 *     if (*(char *)(param_1 + 0x84e4) != '\0') ...      // page fault at 0x84e4
 *     iVar6 = *(int *)(param_1 + 0x84e0);               // inner session object
 *     iVar14 = *(int *)(iVar6 + 0x24238);               // ...also unchecked
 *     if (iVar14 == *(int *)(iVar6 + 0x24234)) return;  // empty ring -> return
 *
 * ShowErrorDialog / ShowMessageDialog / ShowErrorDialogFmt / Shutdown all read
 * `*(int *)(conn + 0x84e0)` unguarded too, then null-check that INNER pointer.
 * So the invariant the ports rely on is: outer connection object non-NULL,
 * inner +0x84e0 session object non-NULL, inner socket nullable.
 *
 * This stub reproduces exactly that much of the real constructor - the field
 * writes below are its offsets, minus the socket thread and the value-guard
 * encode calls (both dropped for bring-up anyway):
 *   +0x4cc   = connection index (real: param_1[0x133] = param_2)
 *   +0x84e0  = zeroed 0x24a70 session object (real: operator_new + FUN_004e54e0)
 *   +0x84e4  = 0, no connect pending  (real: *(undefined1 *)(param_1 + 0x2139))
 *   +0x84e5/+0x84e6 = 0
 *   +0x84e8  = zeroed 0x210 object    (real: param_1[0x213a])
 * The zeroed session object's receive ring has head == tail == 0, so
 * ProcessIncomingPackets sees an empty ring and returns immediately - which is
 * what we want with no server to talk to. The inner socket (+0x24) is set to
 * INVALID_SOCKET so the Shutdown / ShowErrorDialog teardown paths skip
 * closesocket() instead of closing fd 0. No thread is started.
 */
#include <stdlib.h>
#include <string.h>

void *FUN_004d2170(void *self, int index, void *cfg)
{
    unsigned char *conn = (unsigned char *)self;
    unsigned char *session;

    (void)cfg;
    if (conn == 0) {
        return 0;                       /* mirrors WinMain's own alloc check */
    }
    memset(conn, 0, 0x84f0);

    /* A NULL session would just move the fault from +0x84e4 to +0x24238, so
     * fail the whole construction the way WinMain's operator_new check does -
     * the callers' outer null-checks (Shutdown) then take the absent path. */
    session = (unsigned char *)calloc(1, 0x24a70);
    if (session == 0) {
        return 0;
    }
    *(unsigned int *)(session + 0x24) = 0xffffffff;   /* INVALID_SOCKET */

    *(int *)(conn + 0x4cc) = index;
    *(void **)(conn + 0x84e0) = session;
    *(void **)(conn + 0x84e8) = calloc(1, 0x210);
    return conn;
}
""",
}

syms = set()
with open(log_path, errors="replace") as f:
    for m in re.finditer(r"unresolved external symbol (\S+)", f.read()):
        s = m.group(1).rstrip("\r")
        if s.startswith('"'):  # C++-mangled: none expected; fail loudly
            sys.exit(f"C++-mangled unresolved remains, no stub possible: {s}")
        syms.add(s)

manual = sorted(syms & set(MANUAL_STUBS))
unused = sorted(set(MANUAL_STUBS) - syms)
if unused:
    # A manual stub that is no longer unresolved means its real object is back
    # in the link; leaving the override in would be a duplicate definition.
    sys.exit(f"MANUAL_STUBS entries no longer unresolved, remove them: {unused}")

groups = defaultdict(list)  # (conv, argbytes) -> [identifier]
for s in sorted(syms - set(MANUAL_STUBS)):
    if s.startswith("@"):                       # fastcall @name@N
        name, n = s[1:].rsplit("@", 1)
        groups[("__fastcall", int(n))].append(name)
    elif "@" in s:                              # stdcall _name@N
        name, n = s[1:].rsplit("@", 1)
        groups[("__stdcall", int(n))].append(name)
    else:                                       # cdecl _name
        groups[("", 0)].append(s[1:])

total = 0
if manual:
    with open(f"{outdir}/bringup_stubs_manual.c", "w") as f:
        f.write("/* GENERATED by gen_bringup_stubs.py from its MANUAL_STUBS table.\n"
                " * Hand-written bodies - edit them in gen_bringup_stubs.py, not here.\n"
                " * These callees' results are NOT null-checked by their raw-port\n"
                " * callers, so the usual `return 0` stub would itself be the crash. */\n")
        for s in manual:
            f.write(MANUAL_STUBS[s])
    total += len(manual)
    print(f"bringup_stubs_manual.c: {len(manual)} hand-written stubs ({', '.join(manual)})")
for (conv, n), names in sorted(groups.items()):
    tag = {"__fastcall": f"fc{n}", "__stdcall": f"std{n}"}.get(conv, "cdecl")
    args = ", ".join(f"int a{i+1}" for i in range(n // 4)) if conv else ""
    with open(f"{outdir}/bringup_stubs_{tag}.c", "w") as f:
        f.write(f"/* AUTO-GENERATED by gen_bringup_stubs.py - do not edit.\n"
                f" * No-op bring-up stubs, {conv or 'cdecl'}"
                f"{f' {n} arg bytes' if conv else ''}. */\n")
        for name in names:
            f.write(f"int {conv + ' ' if conv else ''}{name}({args}) {{ return 0; }}\n")
    total += len(names)
    print(f"bringup_stubs_{tag}.c: {len(names)} stubs")
print(f"total: {total} stubs for {len(syms)} unresolved symbols")
