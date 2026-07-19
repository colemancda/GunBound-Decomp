#!/usr/bin/env python3
"""Mass sweep for genuine dropped-register arguments in the port.

Ghidra emits `unaff_XXX` / `in_XXX` locals whenever a function reads a
register it never wrote. Most are artifacts (SEH prologue residue,
callee-saved register shuffling, dead paths); a few are REAL incoming
arguments passed in a register by a custom calling convention, and those
are silent miscompiles in the port - the C code reads uninitialised stack.

This script separates the two by doing a read-before-write liveness walk
over the ORIGINAL binary's CFG for each ported function, then reports only
the registers that are genuinely live-in at function entry.

Usage:  tools/.venv-angr/bin/python tools/sweep_dropped_regs.py [--json out.json]
"""
import json
import os
import re
import sys

import capstone

BIN = "orig/GunBound.gme"
SRC_ROOTS = ["src"]

# Ghidra local name -> capstone register roots we care about
REGS = ["eax", "ebx", "ecx", "edx", "esi", "edi", "ebp"]
SUB = {
    "eax": {"eax", "ax", "al", "ah"},
    "ebx": {"ebx", "bx", "bl", "bh"},
    "ecx": {"ecx", "cx", "cl", "ch"},
    "edx": {"edx", "dx", "dl", "dh"},
    "esi": {"esi", "si", "sil"},
    "edi": {"edi", "di", "dil"},
    "ebp": {"ebp", "bp", "bpl"},
}
NAME2ROOT = {}
for r in REGS:
    for n in SUB[r]:
        NAME2ROOT[n] = r

ADDR_RE = re.compile(r"^\s*/\*\s*(\w+)\s*-\s*0x([0-9a-fA-F]{6,8})\s+in the original", re.M)
DECL_RE = re.compile(r"\b(?:unaff|in)_(EAX|EBX|ECX|EDX|ESI|EDI|EBP)\b")


def collect_sources():
    """Map original address -> (source path, set of dropped regs declared)."""
    out = {}
    for root in SRC_ROOTS:
        for dirpath, _dirs, files in os.walk(root):
            for fn in files:
                if not fn.endswith((".c", ".cpp")):
                    continue
                path = os.path.join(dirpath, fn)
                try:
                    text = open(path, encoding="utf-8", errors="replace").read()
                except OSError:
                    continue
                m = ADDR_RE.search(text)
                if not m:
                    continue
                regs = {g.lower() for g in DECL_RE.findall(text)}
                if not regs:
                    continue
                out[int(m.group(2), 16)] = (path, m.group(1), regs)
    return out


class Analyzer:
    def __init__(self, binpath):
        import angr
        import logging

        logging.getLogger("angr").setLevel("ERROR")
        logging.getLogger("cle").setLevel("ERROR")
        self.proj = angr.Project(binpath, auto_load_libs=False)
        self.md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        self.md.detail = True

    def read_bytes(self, addr, size):
        try:
            return self.proj.loader.memory.load(addr, size)
        except Exception:
            return b""

    def live_in(self, entry, max_insns=4000):
        """Registers read before written on some path from `entry`.

        Walks the intra-procedural CFG. Each path carries its own
        written-set; a read of a register not yet written on that path
        marks it live-in. Conservative: stops at ret/call-less tails and
        does not follow indirect jumps.
        """
        live = set()
        seen = set()
        # A standard MSVC prologue saves callee-saved registers with
        # `push ebx/esi/edi/ebp` before doing anything else. Those pushes
        # READ the register, but they are saves, not uses - counting them
        # would mark every callee-saved register live-in for essentially
        # every function. Skip the leading save sequence and start the walk
        # after it, treating the saved registers as still-unwritten (a later
        # genuine read of one is what we are hunting for).
        prologue = set()
        start = entry
        fs_seen = False
        data = self.read_bytes(entry, 0x40)
        for ins in self.md.disasm(data, entry):
            # SEH frame setup: `push -1 / push <handler> / mov eax,fs:[0] /
            # push eax / mov fs:[0],esp` runs BEFORE the register saves.
            if "fs:" in ins.op_str:
                fs_seen = True
                start = ins.address + ins.size
                continue
            if ins.mnemonic == "push" and ins.operands and \
               ins.operands[0].type == capstone.x86.X86_OP_IMM:
                start = ins.address + ins.size
                continue
            if fs_seen and ins.mnemonic == "push" and ins.op_str == "eax":
                start = ins.address + ins.size
                continue
            if ins.mnemonic == "push" and ins.operands and \
               ins.operands[0].type == capstone.x86.X86_OP_REG:
                root = NAME2ROOT.get(ins.reg_name(ins.operands[0].reg))
                if root in ("ebx", "esi", "edi", "ebp"):
                    prologue.add(root)
                    start = ins.address + ins.size
                    continue
                break
            if ins.mnemonic == "mov" and ins.op_str in ("ebp, esp", "edi, edi"):
                start = ins.address + ins.size
                continue
            if ins.mnemonic == "sub" and ins.op_str.startswith("esp,"):
                start = ins.address + ins.size
                continue
            break
        # (addr, frozenset(written))
        work = [(start, frozenset())]
        budget = max_insns
        while work and budget > 0:
            addr, written = work.pop()
            key = (addr, written)
            if key in seen:
                continue
            seen.add(key)
            data = self.read_bytes(addr, 0x200)
            if not data:
                continue
            written = set(written)
            for ins in self.md.disasm(data, addr):
                budget -= 1
                if budget <= 0:
                    break
                try:
                    regs_read, regs_written = ins.regs_access()
                except capstone.CsError:
                    regs_read, regs_written = (), ()

                # `xor r,r` / `sub r,r` are idiom-zeroing, not real reads
                idiom = (
                    ins.mnemonic in ("xor", "sub", "pxor")
                    and len(ins.operands) == 2
                    and ins.operands[0].type == capstone.x86.X86_OP_REG
                    and ins.operands[1].type == capstone.x86.X86_OP_REG
                    and ins.operands[0].reg == ins.operands[1].reg
                )

                if not idiom:
                    for r in regs_read:
                        root = NAME2ROOT.get(ins.reg_name(r))
                        if root and root not in written:
                            live.add(root)
                for r in regs_written:
                    root = NAME2ROOT.get(ins.reg_name(r))
                    if root:
                        written.add(root)

                mn = ins.mnemonic
                if mn == "ret" or mn.startswith("ret"):
                    break
                if mn == "call":
                    # caller-saved regs are clobbered; callee-saved survive
                    written |= {"eax", "ecx", "edx"}
                    continue
                if mn.startswith("j"):
                    tgt = None
                    if ins.operands and ins.operands[0].type == capstone.x86.X86_OP_IMM:
                        tgt = ins.operands[0].imm
                    if tgt is not None and abs(tgt - entry) < 0x4000:
                        work.append((tgt, frozenset(written)))
                    if mn == "jmp":
                        break
                    continue
        return live


def main():
    if not os.path.exists(BIN):
        sys.exit(f"missing {BIN} (run from the repo root)")
    sources = collect_sources()
    az = Analyzer(BIN)

    results = []
    for addr, (path, name, declared) in sorted(sources.items()):
        try:
            live = az.live_in(addr)
        except Exception as exc:  # noqa: BLE001
            results.append(
                {"addr": f"{addr:08x}", "func": name, "path": path,
                 "declared": sorted(declared), "error": str(exc)}
            )
            continue
        confirmed = sorted(declared & live)
        if confirmed:
            results.append(
                {"addr": f"{addr:08x}", "func": name, "path": path,
                 "declared": sorted(declared), "confirmed": confirmed}
            )

    results.sort(key=lambda r: (-len(r.get("confirmed", [])), r["path"]))
    print(f"scanned {len(sources)} ported functions carrying dropped-register locals")
    print(f"CONFIRMED live-in (genuine dropped args): {len(results)}\n")
    for r in results:
        if "error" in r:
            continue
        print(f"{r['addr']}  {r['func']:<44} {','.join(r['confirmed'])}")
        print(f"          {r['path']}")

    if "--json" in sys.argv:
        out = sys.argv[sys.argv.index("--json") + 1]
        json.dump(results, open(out, "w"), indent=2)
        print(f"\nwrote {out}")


if __name__ == "__main__":
    main()
