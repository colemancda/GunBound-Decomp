"""Code discovery: decode, find function starts, resolve jump tables, build per-function bodies."""
import capstone
from capstone import x86_const as X

REG8 = {"al", "cl", "dl", "bl", "ah", "ch", "dh", "bh"}
REG16 = {"ax", "cx", "dx", "bx", "sp", "bp", "si", "di"}
REG32 = {"eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi"}

JCC = {
    "jo", "jno", "jb", "jae", "je", "jne", "jbe", "ja", "js", "jns", "jp", "jnp", "jl", "jge", "jle", "jg",
}
LOOPS = {"jecxz", "jcxz", "loop", "loope", "loopne"}
TERMINATORS = {"ret", "retf", "iretd", "iret", "int3", "hlt", "ud2"}


class Op:
    """One decoded operand. t is 'r' (register), 'i' (immediate) or 'm' (memory)."""

    __slots__ = ("t", "size", "reg", "imm", "seg", "base", "index", "scale", "disp")

    def __repr__(self):
        if self.t == "r":
            return self.reg
        if self.t == "i":
            return hex(self.imm)
        return "%s[%s%s+%s*%d+%#x]:%d" % (
            (self.seg + ":") if self.seg else "", "", self.base, self.index, self.scale, self.disp, self.size)


class Insn:
    __slots__ = ("addr", "size", "mn", "ops", "rep", "lock", "opc", "modrm", "opsize16", "text")

    @property
    def next(self):
        return self.addr + self.size


class Analysis:
    def __init__(self, img, seeds, names=None, verbose=False):
        self.img = img
        self.names = names or {}
        self.verbose = verbose
        self.md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        self.md.detail = True
        self.insns = {}        # addr -> Insn, reached code only
        self._cache = {}       # decode cache (includes trial decodes)
        self.bad = set()       # addresses that failed to decode
        self.badflow = set()   # reached addresses that could not be decoded
        self.cover = bytearray(img.text_end - img.text_start)  # 1 = insn start, 2 = insn interior
        self.overlaps = 0
        self.rejected_ptrs = 0
        self.starts = set()    # function entry addresses
        self.tables = {}       # jmp insn addr -> (table_va, [targets], how)
        self.table_bytes = {}  # table va -> byte length (data-in-code ranges)
        self.unresolved_ijmp = []   # insn addrs of indirect jumps with no table
        self.seed_kinds = {}
        self._work = []
        for a in seeds:
            self.add_start(a, "seed")

    # ---------------------------------------------------------------- decoding
    def decode(self, a):
        ins = self._cache.get(a)
        if ins is not None:
            return ins
        if a in self.bad or not self.img.in_text(a):
            return None
        code = self.img.bytes_at(a, 16)
        try:
            cs = next(self.md.disasm(code, a, 1))
        except StopIteration:
            self.bad.add(a)
            return None
        ins = Insn()
        ins.addr = a
        ins.size = cs.size
        mn = cs.mnemonic
        ins.rep = None
        ins.lock = False
        for p in ("rep ", "repe ", "repne ", "lock ", "notrack ", "bnd "):
            if mn.startswith(p):
                if p.startswith("rep"):
                    ins.rep = p.strip()
                elif p == "lock ":
                    ins.lock = True
                mn = mn[len(p):]
        ins.mn = mn
        ins.opc = tuple(cs.opcode[:3])
        ins.modrm = cs.modrm
        ins.opsize16 = 0x66 in cs.prefix
        ins.text = (cs.mnemonic + " " + cs.op_str).strip()
        ops = []
        for o in cs.operands:
            op = Op()
            op.size = o.size
            op.reg = op.seg = op.base = op.index = None
            op.imm = op.disp = 0
            op.scale = 1
            if o.type == X.X86_OP_REG:
                op.t = "r"
                op.reg = cs.reg_name(o.reg)
            elif o.type == X.X86_OP_IMM:
                op.t = "i"
                op.imm = o.imm & 0xFFFFFFFF
            elif o.type == X.X86_OP_MEM:
                op.t = "m"
                m = o.mem
                op.seg = cs.reg_name(m.segment) if m.segment else None
                op.base = cs.reg_name(m.base) if m.base else None
                op.index = cs.reg_name(m.index) if m.index else None
                op.scale = m.scale
                op.disp = m.disp & 0xFFFFFFFF
            else:
                op.t = "?"
            ops.append(op)
        ins.ops = ops
        self._cache[a] = ins
        return ins

    # ------------------------------------------------------------- discovery
    def add_start(self, a, kind):
        if a not in self.starts and self.img.in_text(a):
            self.starts.add(a)
            self.seed_kinds[a] = kind
            self._work.append(a)
            return True
        return False

    def direct_target(self, ins):
        if ins.ops and ins.ops[0].t == "i":
            return ins.ops[0].imm
        return None

    def explore(self):
        """Global recursive descent from every queued address."""
        work = self._work
        insns = self.insns
        cover = self.cover
        tbase = self.img.text_start
        while work:
            a = work.pop()
            while a not in insns:
                ins = self.decode(a)
                if ins is None:
                    self.badflow.add(a)
                    break
                insns[a] = ins
                o = a - tbase
                if cover[o] == 2:
                    self.overlaps += 1
                cover[o] = 1
                for k in range(o + 1, min(o + ins.size, len(cover))):
                    if cover[k] == 1:
                        self.overlaps += 1
                    else:
                        cover[k] = 2
                mn = ins.mn
                if mn in TERMINATORS:
                    break
                if mn == "jmp":
                    t = self.direct_target(ins)
                    if t is not None:
                        work.append(t)
                    else:
                        work.extend(self.resolve_table(ins))
                    break
                if mn in JCC or mn in LOOPS:
                    work.append(self.direct_target(ins))
                elif mn == "call":
                    t = self.direct_target(ins)
                    if t is not None and t != ins.next:
                        self.add_start(t, "call")
                a = ins.next

    def run(self, scan_pointers=True):
        self.explore()
        if scan_pointers:
            self.scan_pointers()

    # ------------------------------------------------- pointer-derived seeds
    IMPLAUSIBLE = {
        "in", "out", "insb", "insd", "insw", "outsb", "outsd", "outsw", "hlt", "iretd", "iret", "retf", "lcall",
        "ljmp", "int", "into", "arpl", "bound", "aaa", "aas", "daa", "das", "aam", "aad", "les", "lds", "salc",
        "sysenter", "sysexit", "cli", "sti", "int1", "enter", "xlatb", "cmc", "stc", "clc",
        "loop", "loope", "loopne", "popal", "pushal", "popfd", "pushfd",
    }

    def in_table(self, a):
        for t, n in self.table_bytes.items():
            if t <= a < t + n:
                return True
        return False

    def plausible_code(self, a):
        """Does undiscovered address `a` look like the start of real code?"""
        img = self.img
        o = a - img.text_start
        if o > 0 and self.cover[o - 1] == 0:
            prev = img.u8(a - 1)
            ret_n = o >= 3 and img.u8(a - 3) == 0xC2 and img.u8(a - 1) == 0
            if prev not in (0xCC, 0xC3, 0x90) and not ret_n and (a & 0xF):
                return False
        n = 0
        while n < 32:
            if not img.in_text(a) or self.in_table(a):
                return False
            c = self.cover[a - img.text_start]
            if c == 2:
                return False
            if c == 1:
                return True
            ins = self.decode(a)
            if ins is None or ins.mn in self.IMPLAUSIBLE or ins.opc[0] == 0:
                return False  # opcode 00 (add r/m8, r8) is what zero-filled data decodes to
            for op in ins.ops:
                if op.t == "r" and op.reg in ("cs", "ds", "es", "ss", "fs", "gs"):
                    return False
                if op.t == "?":
                    return False
            if ins.mn in ("ret", "jmp"):
                return True
            if ins.mn == "int3":
                return n > 0
            if ins.mn in ("call",) or ins.mn in JCC:
                t = self.direct_target(ins)
                if t is not None and not img.in_text(t):
                    return False
                if t is not None and self.cover[t - img.text_start] == 2:
                    return False
            a = ins.next
            n += 1
        return True

    def scan_pointers(self):
        """Add function starts referenced only as data: immediates in code and dwords in data sections."""
        img = self.img
        done = set()
        data_cands = {}
        for sec in img.sections:
            if sec.va == img.text_start:
                continue
            n = min(sec.vsize, sec.rawsize, img.end - sec.va)
            for off in range(0, n - 3, 4):
                v = img.u32(sec.va + off)
                if img.text_start <= v < img.text_end:
                    data_cands[v] = "data"
        first = True
        while True:
            cands = {}
            for a, ins in self.insns.items():
                if a in done:
                    continue
                done.add(a)
                if ins.mn in ("call", "jmp") or ins.mn in JCC or ins.mn in LOOPS:
                    continue
                for op in ins.ops:
                    if op.t == "i" and img.text_start <= op.imm < img.text_end:
                        cands[op.imm] = "imm"
            if first:
                for k, v in data_cands.items():
                    cands.setdefault(k, v)
                first = False
            new = 0
            for v in sorted(cands):
                kind = cands[v]
                if v in self.starts or self.in_table(v):
                    continue
                cv = self.cover[v - img.text_start]
                if cv == 2:
                    self.rejected_ptrs += 1
                elif cv == 1:
                    # A pointer to the middle of a known function: an SEH filter/handler label
                    # or similar. Values shaped like 0x00XX00YY are far more often UTF-16 text
                    # or round constants than code pointers, so those are not promoted.
                    if v & 0xFF00:
                        new += self.add_start(v, kind + "-label")
                    else:
                        self.rejected_ptrs += 1
                elif self.plausible_code(v):
                    new += self.add_start(v, kind + "-code")
                    self.explore()
                else:
                    self.rejected_ptrs += 1
            if not new:
                break
            self.explore()

    # ------------------------------------------------------------ jump tables
    def resolve_table(self, ins):
        """`jmp dword ptr [reg*4 + table]`: return the list of table targets (possibly empty)."""
        if ins.addr in self.tables:
            return self.tables[ins.addr][1]
        op = ins.ops[0]
        img = self.img
        if not (op.t == "m" and op.base is None and op.index is not None and op.scale == 4
                and op.seg is None and img.has(op.disp, 4)):
            if ins.addr not in self.unresolved_ijmp:
                self.unresolved_ijmp.append(ins.addr)
            return []
        tbl = op.disp
        bound, btbl = self._table_bound(ins, op.index)
        how = "bound"
        count = None
        if bound is not None:
            if btbl is not None:
                # two-level: byte index table of `bound` entries selects the dword entry
                if img.has(btbl, bound):
                    count = max(img.bytes_at(btbl, bound)) + 1
                    self.table_bytes[btbl] = bound
                    how = "bound2"
            else:
                count = bound
        targets = []
        first = None  # index of the first slot that holds a code address
        i = 0
        while True:
            if count is not None and i >= count:
                break
            ea = tbl + 4 * i
            if not img.has(ea, 4):
                break
            t = img.u32(ea)
            if not img.in_text(t):
                # Leading slots can be unused: memcpy's alignment dispatch indexes its table
                # with 1..3 only, and slot 0 overlaps the instruction before the table.
                if first is None and i < 4:
                    i += 1
                    continue
                break
            if count is None:
                # heuristic scan: stop where known code or another table begins
                if first is not None and (ea in self.starts or ea in self.table_bytes or ea in self.insns):
                    break
                if i >= 1024:
                    break
            if first is None:
                first = i
            targets.append(t)
            i += 1
        if count is None:
            how = "scan"
        elif len(targets) < count:
            how += "-trunc"
        if not targets and count is None:
            # A negative index: memcpy's tail dispatch runs with ecx in -4..-1 and names the
            # address just past the table. Collect the slots below it.
            k = 1
            while k <= 16:
                ea = tbl - 4 * k
                if not img.has(ea, 4) or not img.in_text(img.u32(ea)) or self.cover[ea - img.text_start]:
                    break
                targets.append(img.u32(ea))
                k += 1
            if targets:
                how = "scan-back"
                self.table_bytes.setdefault(tbl - 4 * (k - 1), 4 * (k - 1))
        if not targets:
            how += "-empty"
        if first is not None:
            self.table_bytes[tbl + 4 * first] = 4 * (i - first)
        self.tables[ins.addr] = (tbl, targets, how)
        return targets

    def _prev(self, a):
        """Instruction that linearly precedes address a (by scanning the decode cache)."""
        for back in range(1, 16):
            p = self.insns.get(a - back)
            if p is not None and p.next == a:
                return p
        return None

    def _table_bound(self, jins, idxreg):
        """Look back for `cmp X, N ; ja default` guarding the table jump. Returns (count, bytetable)."""
        btbl = None
        a = jins.addr
        for _ in range(12):
            p = self._prev(a)
            if p is None:
                return None, None
            a = p.addr
            if p.mn == "movzx" and p.ops[0].t == "r" and p.ops[0].reg == idxreg and p.ops[1].t == "m" \
                    and p.ops[1].size == 1 and p.ops[1].index is None and p.ops[1].base is not None \
                    and self.img.in_text(p.ops[1].disp):
                btbl = p.ops[1].disp
                continue
            if p.mn == "mov" and p.ops[0].t == "r" and p.ops[0].reg in REG8 and p.ops[1].t == "m" \
                    and p.ops[1].index is None and p.ops[1].base is not None and self.img.in_text(p.ops[1].disp):
                btbl = p.ops[1].disp
                continue
            if p.mn == "ja":
                q = self._prev(p.addr)
                if q is not None and q.mn == "cmp" and q.ops[1].t == "i":
                    return q.ops[1].imm + 1, btbl
                return None, None
            if p.mn in JCC or p.mn in ("jmp", "ret", "call"):
                return None, None
        return None, None

    # --------------------------------------------------- per-function bodies
    def function_body(self, entry):
        """Addresses of the instructions belonging to the function at `entry` (sorted).

        Descent stops at other function starts (those become tail calls) and never follows calls."""
        insns = self.insns
        starts = self.starts
        body = set()
        work = [entry]
        while work:
            a = work.pop()
            while a not in body:
                if a != entry and a in starts:
                    break
                ins = insns.get(a)
                if ins is None:
                    break
                body.add(a)
                mn = ins.mn
                if mn in TERMINATORS:
                    break
                if mn == "jmp":
                    t = self.direct_target(ins)
                    if t is not None:
                        work.append(t)
                    else:
                        tab = self.tables.get(a)
                        if tab:
                            work.extend(tab[1])
                    break
                if mn in JCC or mn in LOOPS:
                    work.append(self.direct_target(ins))
                a = ins.next
        return sorted(body)
