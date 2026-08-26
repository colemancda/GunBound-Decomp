#!/usr/bin/env python3
"""Resolve the dropped guard-cell pointer at every guard call site in one function.

Back-tracks the cell register through a linear disassembly of the function,
following mov/lea/add chains, and prints one line per call site:

    <idx> <call_addr> <family>  cell = <resolved expression>   [<chain>]

The point is to do the mechanical part of tools/sweep_guard_instructions.md
("Bare register (edi, esi, ebx, ebp): back-track the register's last load
before the call") in bulk, so a sweep can spend its attention on the part
that actually needs judgement: turning the resolved expression into the
right C local, and checking the landmarks.

THIS IS A HINT GENERATOR, NOT AN ORACLE.  It walks the function linearly, so
at any site whose register was set on a different control-flow path (loop
back-edge, join point after a branch, or a `mov reg,eax` capture of a call
RESULT) the answer is wrong or misleading.  Such sites are marked !! so they
get read by hand.  Same standing rule as the json cell hints: derive from the
disasm, never trust a tool's guess.

Usage:
    tools/.venv-angr/bin/python3 tools/guard_cell_resolve.py <start> <end>
    tools/.venv-angr/bin/python3 tools/guard_cell_resolve.py 0x424ac0 0x425340
"""
import re
import subprocess
import sys
import os

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)

# call target -> (family name, register holding the cell).  From the verified
# ABI table in tools/sweep_guard_instructions.md.
FAMILY = {
    0x40a2e0: ("Peek", "eax"),
    0x40a380: ("Encode", "edi"),
    0x40a470: ("Queue", "eax"),
    # BUG FIX 2026-08-16: 0x40a440 takes its CELL IN EDI, not EAX - EAX holds
    # the VALUE (`mov esi,eax; xor esi,0xeeaeaec0; push esi; call 0x40a380`,
    # EDI never written, i.e. live-in).  The old "eax" entry made every
    # EncodeXored row report the XOR constant 0xeeaeaec0 as if it were a cell.
    # No C site was ever fixed from those rows (checked tree-wide).
    0x40a440: ("EncodeXored", "edi"),
    0x40a2a0: ("Scrub", "ecx"),
    0x4065a0: ("PeekBool", "eax"),
    # Added 2026-08-26.  0x406860 is the NEGATED twin of PeekBool: byte-for-byte
    # the same code with `sete al` on the result, and it takes its cell in EAX the
    # same way (`mov esi,eax` at +0xc, then `mov cl,[esi]`).  Its absence from this
    # table is why the CValueGuard sweep never resolved ANY of its 39 call sites --
    # they are all still argless, and the callee still reads an uninitialised
    # `byte *in_EAX`.
    0x406860: ("DecodeBool", "eax"),
    0x406500: ("SetBool", "eax"),
    0x4064a0: ("EncodeBool", "eax"),
    0x406530: ("RescrambleBool", "eax"),
    0x406610: ("CheckBoolAnd", "eax"),
    0x406710: ("CheckBoolBoth", "eax"),
    0x40afb0: ("EmitSum", "eax"),
    # Added 2026-08-16 (CValueGuard Peek-flip prep).  Each of these takes its
    # cell in a register the raw ports dropped; the second operand, where there
    # is one, is a real stack argument the ports already kept:
    #   Add/Sub          cell EAX, delta   = arg1 ([esp+8])
    #   EmitDiff         cell EAX, 2nd cell= arg1 ([esp+0xc])
    #   EmitMod          cell EAX, divisor = arg1 ([esp+8])
    #   EncodeDec        cell EAX, no stack args
    #   EncodeDiv        cell ECX, divisor = EAX  (BOTH dropped)
    0x40aab0: ("Add", "eax"),
    0x40aaf0: ("Sub", "eax"),
    0x40aff0: ("EmitDiff", "eax"),
    0x40ab60: ("EmitMod", "eax"),
    0x40b060: ("EncodeDec", "eax"),
    0x40ab20: ("EncodeDiv", "ecx"),
    #   Sync             cell EAX, context ECX, plus two stack args
    0x4262d0: ("Sync", "eax"),
    #   FUN_0040b030     cell EAX (Encode(Peek()+1))
    #   FUN_004217b0     ctx  EAX (peeks ctx+0xeb854, then a stack-arg cell)
    #   FUN_00426230     ctx  EAX (peeks ctx+0x6aa67c)
    #   FUN_00420600     idx  ESI (peeks [esp+4] + esi*0x224 + 0x39d0c)
    0x40b030: ("EncodeInc", "eax"),
    0x4217b0: ("PeekCtxSlot", "eax"),
    0x426230: ("ShowElapsed", "eax"),
    0x420600: ("SlotIdxCheck", "esi"),
    #   pair comparators: BOTH cells are stack args (ret 8); listed so the
    #   report shows the site; the resolver reports [esp+..] for them.
    0x40b390: ("CmpMatch", "stack"),
    0x40b490: ("CmpPair", "stack"),
    0x40b4d0: ("CmpAtMost", "stack"),
    0x40b410: ("CmpExceeds", "stack"),
    0x40b3d0: ("PairDiffers", "stack"),
}

REGS = ("eax", "ebx", "ecx", "edx", "esi", "edi", "ebp")

# `test ebp, ebp` / `cmp esi, esi` / `push edi` all start with "<reg>," but
# leave the register alone.  Treating one as a write silently truncates the
# back-track and reports the flag-setting instruction as the cell's source.
NONWRITING = ("test", "cmp", "push")


def disasm(start, end):
    out = subprocess.run(
        [os.path.join(HERE, ".venv-angr/bin/python3"),
         os.path.join(HERE, "disasm_capstone.py"),
         os.path.join(ROOT, "orig/GunBound.gme"), hex(start), hex(end)],
        capture_output=True, text=True, cwd=ROOT).stdout
    insns = []
    for line in out.splitlines():
        m = re.match(r"^([0-9a-f]{8}):\t(\S+)\t?(.*)$", line)
        if m:
            insns.append((int(m.group(1), 16), m.group(2), m.group(3).strip()))
    return insns


def esp_depth(insns):
    """Push-depth of each instruction relative to the settled frame esp.

    Guard call sites are dense with `push 0x5a9068 / call esi` critical-section
    pairs, so an `[esp + X]` written one push deep names a DIFFERENT slot than
    the same text written at the settled depth - a silent way to pick the wrong
    cell.  Every callee in this code cleans its own arguments (__stdcall /
    __thiscall, or cdecl followed by an explicit `add esp,N`), so depth resets
    to 0 at each call; pushes in between accumulate.

    Depth is None until the function's first call: the prologue's `sub esp,N`
    and its callee-saved pushes are not a settled frame, and how much of what
    sits above esp there belongs to the first call's arguments is not knowable
    locally.  Those `[esp + X]` operands are reported unnormalised and flagged
    rather than guessed - in FUN_00491b40 the prologue store `mov [esp+0xc],edi`
    is really frame[0x14], and normalising it with a prologue-inflated depth
    would have named a slot ~0x480 bytes away.
    """
    depths, d, seen_call = [], None, False
    for i, (addr, mnem, ops) in enumerate(insns):
        depths.append(d)
        if mnem == "call":
            # Callee-cleanup (__stdcall/__thiscall) is the common case, and
            # there d is 0 the instant the call returns.  A __cdecl callee is
            # not: its arguments stay on the stack until the caller's own
            # `add esp,N`, so anything reading [esp+X] in that gap is one
            # argument-block deep.  Detect that by looking ahead for the
            # cleanup before the next push/call.  FUN_0048b420 0x48b78c
            # reads a cell between `call 0x4ee9b0` and its `add esp,4`.
            d, seen_call = 0, True
            for _, m2, o2 in insns[i + 1:i + 6]:
                if m2 == "add" and o2.startswith("esp,"):
                    try:
                        d = int(o2.split(",", 1)[1].strip(), 0)
                    except ValueError:
                        pass
                    break
                if m2 in ("push", "call") or m2.startswith("j"):
                    break
            continue
        if not seen_call:
            continue
        if mnem == "push":
            d += 4
        elif mnem == "pop":
            d -= 4
        elif mnem in ("add", "sub") and ops.startswith("esp,"):
            n = ops.split(",", 1)[1].strip()
            try:
                d += (-int(n, 0) if mnem == "add" else int(n, 0))
            except ValueError:
                pass
        if d < 0:
            d = 0
    return depths


def norm_esp(text, d):
    """Rewrite an `[esp + X]` operand to the settled-frame slot it names."""
    if d is None:
        return (text + "  !!PRE-SETTLE, depth unknown - resolve by hand"
                if "[esp" in text else text)
    if not d:
        return text
    m = re.search(r"\[esp \+ (0x[0-9a-f]+)\]", text)
    if not m:
        return text
    return text[:m.start()] + "[esp + 0x%x]" % (int(m.group(1), 16) - d) + text[m.end():]


def resolve(insns, depths, i, reg, depth=0):
    """Walk backwards from insns[i] for the last write to `reg`.

    Returns (expression, chain, confident).  All `[esp + X]` operands are
    normalised to settled-frame slots via depths[] before being reported.
    """
    if depth > 6:
        return reg, [], False
    entry_ok = reg in ("ecx", "esi")  # the usual __thiscall `this` carriers
    for j in range(i - 1, -1, -1):
        addr, mnem, ops = insns[j]
        if mnem in ("jmp", "ret") and j != i - 1:
            # Walking backwards past an unconditional jump / return means
            # the instruction we are now looking at ends a DIFFERENT basic
            # block, one that never falls through to the site.  Whatever
            # it wrote is not what the site sees; the site's block was
            # entered by a branch from somewhere else, and this walk cannot
            # see that path.  Report it rather than keep going and hand back
            # a value from an unrelated block (FUN_00483ff0 0x484b01: the
            # walk crossed `jmp 0x484fa3` into the rand-scramble block and
            # said the cell was ctx+0x62143+0x488).
            return "<%s crosses block end at 0x%x>" % (reg, addr), [], False
        if mnem in NONWRITING or not ops.startswith(reg + ","):
            # a call clobbers eax/ecx/edx; stop guessing past one for those
            if mnem == "call" and reg in ("eax", "ecx", "edx"):
                return "<clobbered by call at 0x%x>" % addr, [], False
            continue
        src = norm_esp(ops[len(reg) + 1:].strip(), depths[j])
        step = "0x%x: %s %s" % (addr, mnem, ops)
        if depths[j]:
            step += "   [esp %s here -> %s]" % (
                "depth unknown" if depths[j] is None else "%+d" % depths[j], src)
        if mnem == "lea":
            m = re.match(r"^\[(\w+) \+ (0x[0-9a-f]+)\]$", src)
            if "!!PRE-SETTLE" in src:
                return src, [step], False
            if m and m.group(1) == "esp":
                # a frame slot, already normalised - naming it needs the
                # per-function frame base, so stop here rather than
                # back-tracking esp itself through the prologue
                return "frame [esp + %s]" % m.group(2), [step], True
            if m and m.group(1) != reg:
                base, chain, ok = resolve(insns, depths, j, m.group(1), depth + 1)
                return "%s + %s" % (base, m.group(2)), [step] + chain, ok
            return "&(%s)" % src, [step], True
        if mnem == "mov":
            if src in REGS:
                base, chain, ok = resolve(insns, depths, j, src, depth + 1)
                return base, [step] + chain, ok
            if "!!PRE-SETTLE" in src:
                return src, [step], False
            if src.startswith("dword ptr ["):
                # a spill slot / arg slot / global load: a definite location,
                # but one the sweep still has to give a C name
                return src, [step], True
            return src, [step], True
        if mnem == "add":
            m = re.match(r"^(0x[0-9a-f]+)$", src)
            if m:
                base, chain, ok = resolve(insns, depths, j, reg, depth + 1)
                return "%s + %s" % (base, m.group(1)), [step] + chain, ok
        return "<%s %s>" % (mnem, ops), [step], False
    return "<%s live-in at entry>" % reg, [], entry_ok


def main():
    start, end = int(sys.argv[1], 16), int(sys.argv[2], 16)
    insns = disasm(start, end)
    depths = esp_depth(insns)
    # a register written between two sites on a *different* path is the main
    # hazard; flag any site whose chain crosses a branch target
    targets = set()
    for addr, mnem, ops in insns:
        if mnem.startswith("j"):
            m = re.match(r"^0x([0-9a-f]+)$", ops)
            if m:
                targets.add(int(m.group(1), 16))
    idx = 0
    for i, (addr, mnem, ops) in enumerate(insns):
        if mnem != "call":
            continue
        m = re.match(r"^0x([0-9a-f]+)$", ops)
        if not m:
            continue
        fam = FAMILY.get(int(m.group(1), 16))
        if not fam:
            continue
        name, reg = fam
        expr, chain, ok = resolve(insns, depths, i, reg)
        src_addr = int(chain[0].split(":")[0], 16) if chain else addr
        crosses = any(src_addr < t <= addr for t in targets)
        flag = "  " if (ok and not crosses) else "!!"
        note = " CROSSES-BRANCH-TARGET" if crosses else ""
        print("%s %3d 0x%x %-14s cell = %s%s" % (flag, idx, addr, name, expr, note))
        for step in chain:
            print("           %s" % step)
        idx += 1


if __name__ == "__main__":
    main()
