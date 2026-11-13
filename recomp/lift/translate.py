"""x86 instruction -> C statement translation (everything except control transfers).

Each translator returns a Tr: code that computes temporaries and performs the
writes, a dict of flag -> C expression (emitted only for flags that are live
afterwards), trailing code, and the flag use/kill sets for liveness analysis.
"""

FLAG_BITS = {"cf": 1, "pf": 2, "af": 4, "zf": 8, "sf": 16, "of": 32}
ALL_FLAGS = 63
SZP = ("zf", "sf", "pf")

R32 = {"eax": "EAX", "ecx": "ECX", "edx": "EDX", "ebx": "EBX", "esp": "ESP", "ebp": "EBP", "esi": "ESI", "edi": "EDI"}
R16 = {"ax": "AX", "cx": "CX", "dx": "DX", "bx": "BX", "sp": "SP", "bp": "BP", "si": "SI", "di": "DI"}
R8 = {"al": "AL", "cl": "CL", "dl": "DL", "bl": "BL", "ah": "AH", "ch": "CH", "dh": "DH", "bh": "BH"}
REGS = {}
REGS.update(R32)
REGS.update(R16)
REGS.update(R8)
# Flat-model selector values a 32-bit Windows process sees.
SEGVAL = {"cs": 0x23, "ds": 0x2B, "es": 0x2B, "ss": 0x2B, "fs": 0x53, "gs": 0x2B}

MASK = {1: "0xffu", 2: "0xffffu", 4: "0xffffffffu"}
STYPE = {1: "int8_t", 2: "int16_t", 4: "int32_t"}

COND = {
    "o": ("c->of", 32), "no": ("!c->of", 32),
    "b": ("c->cf", 1), "ae": ("!c->cf", 1),
    "e": ("c->zf", 8), "ne": ("!c->zf", 8),
    "be": ("(c->cf | c->zf)", 9), "a": ("!(c->cf | c->zf)", 9),
    "s": ("c->sf", 16), "ns": ("!c->sf", 16),
    "p": ("c->pf", 2), "np": ("!c->pf", 2),
    "l": ("(c->sf != c->of)", 48), "ge": ("(c->sf == c->of)", 48),
    "le": ("(c->zf | (c->sf != c->of))", 56), "g": ("!(c->zf | (c->sf != c->of))", 56),
}


class Unsupported(Exception):
    pass


class Tr:
    __slots__ = ("pre", "flags", "post", "uses", "kills")

    def __init__(self, pre="", flags=None, post="", uses=0, kills=None, cond=False):
        self.pre = pre
        self.flags = flags or {}
        self.post = post
        self.uses = uses
        if kills is None:
            kills = 0
            if not cond:
                for f in self.flags:
                    kills |= FLAG_BITS[f]
        self.kills = kills

    def render(self, live):
        parts = [self.pre]
        for f, e in self.flags.items():
            if live & FLAG_BITS[f]:
                parts.append("c->%s = %s; " % (f, e))
        parts.append(self.post)
        return "".join(parts).strip()


def insn_name(ins):
    name = (ins.rep + " " if ins.rep else "") + ins.mn
    if ins.opc[0] == 0x0F and ins.mn in ("movsd", "cmpsd"):
        name += "(sse2)"
    return name


def trap(ins):
    name = insn_name(ins)
    return Tr('rt_unimplemented_insn(c, 0x%08xu, "%s");' % (ins.addr, name), uses=ALL_FLAGS)


def m(expr, sz):
    return expr if sz == 4 else "(%s) & %s" % (expr, MASK[sz])


def sx(expr, sz):
    """expr (zero-extended in a uint32_t) reinterpreted as a signed value of sz bytes."""
    return "(%s)(%s)" % (STYPE[sz], expr)


class Translator:
    def __init__(self):
        self.trapped = {}

    # ------------------------------------------------------------- operands
    def ea(self, op):
        parts = []
        if op.seg == "fs":
            parts.append("c->fs_base")
        elif op.seg == "gs":
            raise Unsupported("gs segment")
        if op.base:
            if op.base not in R32:
                raise Unsupported("16-bit addressing")
            parts.append(R32[op.base])
        if op.index:
            if op.index not in R32:
                raise Unsupported("16-bit addressing")
            parts.append(R32[op.index] if op.scale == 1 else "%s * %d" % (R32[op.index], op.scale))
        if op.disp or not parts:
            parts.append("0x%xu" % op.disp)
        return " + ".join(parts)

    def rd(self, op, sz=None):
        sz = sz or op.size
        if op.t == "r":
            if op.reg in REGS:
                return REGS[op.reg]
            if op.reg in SEGVAL:
                return "0x%xu" % SEGVAL[op.reg]
            raise Unsupported("register " + str(op.reg))
        if op.t == "i":
            return "0x%xu" % (op.imm & ((1 << (8 * sz)) - 1))
        if op.t == "m":
            return "ld%d(%s)" % (op.size * 8, self.ea(op))
        raise Unsupported("operand")

    def wr(self, op, val):
        if op.t == "r":
            if op.reg not in REGS:
                raise Unsupported("write register " + str(op.reg))
            return "%s = %s; " % (REGS[op.reg], val)
        if op.t == "m":
            return "st%d(%s, %s); " % (op.size * 8, self.ea(op), val)
        raise Unsupported("write operand")

    def dst(self, op):
        """Read-modify-write access: (setup, read expression, write function)."""
        if op.t == "r":
            if op.reg not in REGS:
                raise Unsupported("register " + str(op.reg))
            r = REGS[op.reg]
            return "", r, lambda v: "%s = %s; " % (r, v)
        if op.t == "m":
            bits = op.size * 8
            return ("uint32_t m = %s; " % self.ea(op), "ld%d(m)" % bits, lambda v: "st%d(m, %s); " % (bits, v))
        raise Unsupported("operand")

    # ------------------------------------------------------------- dispatch
    # Instructions with an atomic translation; a `lock` prefix on anything else is trapped
    # rather than silently lifted as a plain read-modify-write.
    LOCKABLE = ("xadd", "cmpxchg", "xchg")

    def translate(self, ins):
        try:
            if ins.lock and ins.mn not in self.LOCKABLE:
                raise Unsupported("lock " + ins.mn)
            if 0xD8 <= ins.opc[0] <= 0xDF and ins.mn.startswith("f"):
                return self.x87(ins)
            fn = getattr(self, "t_" + ins.mn, None)
            if fn is None:
                cc = self.cc_of(ins.mn)
                if cc:
                    return cc(ins)
                raise Unsupported(ins.mn)
            return fn(ins)
        except Unsupported:
            self.note_trap(ins)
            return trap(ins)

    def note_trap(self, ins):
        """Record a trapped instruction (by address, so duplicated tails count once)."""
        self.trapped.setdefault(insn_name(ins), set()).add(ins.addr)

    def cc_of(self, mn):
        if mn.startswith("set") and mn[3:] in COND:
            return lambda ins: self.setcc(ins, mn[3:])
        if mn.startswith("cmov") and mn[4:] in COND:
            return lambda ins: self.cmovcc(ins, mn[4:])
        return None

    # ---------------------------------------------------------------- moves
    def t_mov(self, ins):
        d, s = ins.ops
        return Tr(self.wr(d, self.rd(s, d.size)))

    def t_movzx(self, ins):
        d, s = ins.ops
        return Tr(self.wr(d, self.rd(s)))

    def t_movsx(self, ins):
        d, s = ins.ops
        return Tr(self.wr(d, "(uint32_t)%s" % sx(self.rd(s), s.size)))

    def t_lea(self, ins):
        d, s = ins.ops
        return Tr(self.wr(d, self.ea(s)))

    def t_xchg(self, ins):
        d, s = ins.ops
        if d.t == "r" and s.t == "m":
            d, s = s, d
        if s.t != "r":
            raise Unsupported("xchg form")
        if d.t == "m" and d.size == 4:
            # xchg with memory locks the bus whether or not a lock prefix is present
            return Tr("uint32_t a = rt_atomic_xchg32(%s, %s); %s" % (self.ea(d), self.rd(s), self.wr(s, "a")))
        setup, rdx, wrx = self.dst(d)
        return Tr("%suint32_t a = %s, b = %s; %s%s" % (setup, rdx, self.rd(s), wrx("b"), self.wr(s, "a")))

    def t_nop(self, ins):
        return Tr("")

    t_wait = t_nop

    def t_push(self, ins):
        o = ins.ops[0]
        if o.t == "r" and o.reg in SEGVAL:
            if ins.opsize16:
                raise Unsupported("push seg16")
            return Tr("PUSH32(%s);" % self.rd(o, 4))
        if o.size == 2 and o.t != "i":
            return Tr("PUSH16(%s);" % self.rd(o))
        if o.size == 2 and ins.opsize16:
            return Tr("PUSH16(%s);" % self.rd(o, 2))
        return Tr("PUSH32(%s);" % self.rd(o, 4))

    def t_pop(self, ins):
        o = ins.ops[0]
        if o.size == 2:
            return Tr("{ uint16_t v = ld16(ESP); ESP += 2; %s}" % self.wr(o, "v"))
        return Tr("{ uint32_t v = ld32(ESP); ESP += 4; %s}" % self.wr(o, "v"))

    def t_pushal(self, ins):
        return Tr("{ uint32_t s = ESP; PUSH32(EAX); PUSH32(ECX); PUSH32(EDX); PUSH32(EBX); PUSH32(s); "
                  "PUSH32(EBP); PUSH32(ESI); PUSH32(EDI); }")

    def t_popal(self, ins):
        return Tr("EDI = ld32(ESP); ESI = ld32(ESP + 4); EBP = ld32(ESP + 8); EBX = ld32(ESP + 16); "
                  "EDX = ld32(ESP + 20); ECX = ld32(ESP + 24); EAX = ld32(ESP + 28); ESP += 32;")

    def t_pushfd(self, ins):
        return Tr("PUSH32(rt_get_eflags(c));", uses=ALL_FLAGS)

    def t_popfd(self, ins):
        return Tr("{ uint32_t v = ld32(ESP); ESP += 4; rt_set_eflags(c, v); }", kills=ALL_FLAGS)

    def t_leave(self, ins):
        return Tr("ESP = EBP; EBP = ld32(ESP); ESP += 4;")

    def t_cdq(self, ins):
        return Tr("EDX = (uint32_t)((int32_t)EAX >> 31);")

    def t_cwde(self, ins):
        return Tr("EAX = (uint32_t)(int16_t)AX;")

    def t_cbw(self, ins):
        return Tr("AX = (uint16_t)(int8_t)AL;")

    def t_cwd(self, ins):
        return Tr("DX = (uint16_t)((int16_t)AX >> 15);")

    def t_bswap(self, ins):
        r = self.rd(ins.ops[0])
        return Tr("%s = __builtin_bswap32(%s);" % (r, r))

    def t_lahf(self, ins):
        return Tr("AH = rt_lahf(c);", uses=1 | 2 | 4 | 8 | 16)

    def t_sahf(self, ins):
        return Tr("rt_sahf(c, AH);", kills=1 | 2 | 4 | 8 | 16)

    def t_cld(self, ins):
        return Tr("c->df = 0;")

    def t_std(self, ins):
        return Tr("c->df = 1;")

    def t_clc(self, ins):
        return Tr("", {"cf": "0"})

    def t_stc(self, ins):
        return Tr("", {"cf": "1"})

    def t_cmc(self, ins):
        return Tr("", {"cf": "!c->cf"}, uses=1)

    def t_cpuid(self, ins):
        return Tr("rt_cpuid(c);")

    def t_rdtsc(self, ins):
        return Tr("rt_rdtsc(c);")

    def setcc(self, ins, cc):
        e, uses = COND[cc]
        return Tr(self.wr(ins.ops[0], e), uses=uses)

    def cmovcc(self, ins, cc):
        e, uses = COND[cc]
        d, s = ins.ops
        return Tr("if (%s) { %s}" % (e, self.wr(d, self.rd(s))), uses=uses)

    # ----------------------------------------------------------- arithmetic
    def szp(self, sz):
        b = sz * 8
        return {"zf": "r == 0", "sf": "r >> %d" % (b - 1), "pf": "rt_pf(r)"}

    def addsub_flags(self, kind, sz, carry_from_t=False):
        b = sz * 8
        fl = {}
        if kind == "add":
            if carry_from_t:
                fl["cf"] = "(uint32_t)(t >> %d) & 1" % b
            elif sz == 4:
                fl["cf"] = "r < a"
            else:
                fl["cf"] = "((a + b) >> %d) & 1" % b
            fl["of"] = "(((a ^ r) & (b ^ r)) >> %d) & 1" % (b - 1)
        else:
            fl["cf"] = "(uint32_t)(t >> %d) & 1" % b if carry_from_t else "a < b"
            fl["of"] = "(((a ^ b) & (a ^ r)) >> %d) & 1" % (b - 1)
        fl["af"] = "((a ^ b ^ r) >> 4) & 1"
        fl.update(self.szp(sz))
        return fl

    def alu(self, ins, kind, write=True, carry=False):
        d, s = ins.ops
        sz = d.size
        setup, rdx, wrx = self.dst(d)
        pre = "%suint32_t a = %s, b = %s; " % (setup, rdx, self.rd(s, sz))
        uses = 0
        if kind in ("add", "sub"):
            op = "+" if kind == "add" else "-"
            if carry:
                pre += "uint64_t t = (uint64_t)a %s b %s c->cf; uint32_t r = %s; " % (op, op, m("(uint32_t)t", sz))
                uses = 1
            else:
                pre += "uint32_t r = %s; " % m("a %s b" % op, sz)
            fl = self.addsub_flags(kind, sz, carry)
        else:
            op = {"and": "&", "or": "|", "xor": "^"}[kind]
            pre += "uint32_t r = a %s b; " % op
            fl = {"cf": "0", "of": "0", "af": "0"}
            fl.update(self.szp(sz))
        if write:
            pre += wrx("r")
        return Tr(pre, fl, uses=uses)

    def t_add(self, ins):
        return self.alu(ins, "add")

    def t_adc(self, ins):
        return self.alu(ins, "add", carry=True)

    def t_sub(self, ins):
        return self.alu(ins, "sub")

    def t_sbb(self, ins):
        return self.alu(ins, "sub", carry=True)

    def t_cmp(self, ins):
        return self.alu(ins, "sub", write=False)

    def t_and(self, ins):
        return self.alu(ins, "and")

    def t_or(self, ins):
        return self.alu(ins, "or")

    def t_xor(self, ins):
        return self.alu(ins, "xor")

    def t_test(self, ins):
        return self.alu(ins, "and", write=False)

    def t_inc(self, ins):
        d = ins.ops[0]
        sz = d.size
        setup, rdx, wrx = self.dst(d)
        pre = "%suint32_t a = %s, r = %s; %s" % (setup, rdx, m("a + 1", sz), wrx("r"))
        fl = {"of": "r == 0x%xu" % (1 << (sz * 8 - 1)), "af": "(r & 0xf) == 0"}
        fl.update(self.szp(sz))
        return Tr(pre, fl)

    def t_dec(self, ins):
        d = ins.ops[0]
        sz = d.size
        setup, rdx, wrx = self.dst(d)
        pre = "%suint32_t a = %s, r = %s; %s" % (setup, rdx, m("a - 1", sz), wrx("r"))
        fl = {"of": "a == 0x%xu" % (1 << (sz * 8 - 1)), "af": "(r & 0xf) == 0xf"}
        fl.update(self.szp(sz))
        return Tr(pre, fl)

    def t_neg(self, ins):
        d = ins.ops[0]
        sz = d.size
        setup, rdx, wrx = self.dst(d)
        pre = "%suint32_t a = %s, r = %s; %s" % (setup, rdx, m("0u - a", sz), wrx("r"))
        fl = {"cf": "a != 0", "of": "a == 0x%xu" % (1 << (sz * 8 - 1)), "af": "((a ^ r) >> 4) & 1"}
        fl.update(self.szp(sz))
        return Tr(pre, fl)

    def t_not(self, ins):
        d = ins.ops[0]
        setup, rdx, wrx = self.dst(d)
        return Tr("%suint32_t r = ~(uint32_t)%s; %s" % (setup, rdx, wrx("r")))

    def t_xadd(self, ins):
        d, s = ins.ops
        sz = d.size
        if ins.lock:
            if d.t != "m" or sz != 4:
                raise Unsupported("lock xadd form")
            pre = "uint32_t b = %s; uint32_t a = rt_atomic_xadd32(%s, b); uint32_t r = a + b; %s" % (
                self.rd(s, sz), self.ea(d), self.wr(s, "a"))
            return Tr(pre, self.addsub_flags("add", sz))
        setup, rdx, wrx = self.dst(d)
        pre = "%suint32_t a = %s, b = %s; uint32_t r = %s; %s%s" % (
            setup, rdx, self.rd(s, sz), m("a + b", sz), self.wr(s, "a"), wrx("r"))
        return Tr(pre, self.addsub_flags("add", sz))

    def t_cmpxchg(self, ins):
        d, s = ins.ops
        sz = d.size
        acc = {1: "AL", 2: "AX", 4: "EAX"}[sz]
        if ins.lock:
            if d.t != "m" or sz != 4:
                raise Unsupported("lock cmpxchg form")
            pre = "uint32_t a = EAX; uint32_t b = rt_atomic_cmpxchg32(%s, a, %s); uint32_t r = a - b; EAX = b; " % (
                self.ea(d), self.rd(s, sz))
            return Tr(pre, self.addsub_flags("sub", sz))
        setup, rdx, wrx = self.dst(d)
        pre = "%suint32_t a = %s, b = %s; uint32_t r = %s; if (r == 0) { %s} else { %s = b; } " % (
            setup, acc, rdx, m("a - b", sz), wrx(self.rd(s, sz)), acc)
        return Tr(pre, self.addsub_flags("sub", sz))

    # --------------------------------------------------------------- shifts
    def shift(self, ins, kind):
        d = ins.ops[0]
        cnt = ins.ops[1] if len(ins.ops) > 1 else None
        sz = d.size
        b = sz * 8
        setup, rdx, wrx = self.dst(d)
        const = None
        if cnt is None:
            const = 1
        elif cnt.t == "i":
            const = cnt.imm & 31
        if const == 0:
            return Tr("")
        n = str(const) if const is not None else "n"
        pre = setup
        if const is None:
            pre += "uint32_t n = %s & 31; if (n) { " % self.rd(cnt)
        pre += "uint32_t a = %s; " % rdx
        fl = {}
        if kind == "shl":
            pre += "uint64_t t = (uint64_t)a << %s; uint32_t r = %s; " % (n, m("(uint32_t)t", sz))
            fl["cf"] = "(uint32_t)(t >> %d) & 1" % b
            fl["of"] = "((r >> %d) ^ (uint32_t)(t >> %d)) & 1" % (b - 1, b)
            fl["af"] = "0"
            fl.update(self.szp(sz))
        elif kind == "shr":
            pre += "uint32_t r = a >> %s; " % n
            fl["cf"] = "(a >> (%s - 1)) & 1" % n
            fl["of"] = "a >> %d" % (b - 1)
            fl["af"] = "0"
            fl.update(self.szp(sz))
        elif kind == "sar":
            pre += "int32_t sa = %s; uint32_t r = %s; " % (sx("a", sz), m("(uint32_t)(sa >> %s)" % n, sz))
            fl["cf"] = "(uint32_t)(sa >> (%s - 1)) & 1" % n
            fl["of"] = "0"
            fl["af"] = "0"
            fl.update(self.szp(sz))
        elif kind in ("rol", "ror"):
            k = "(%s & %d)" % (n, b - 1)
            if kind == "rol":
                rot = "(a << k) | (a >> (%d - k))" % b
            else:
                rot = "(a >> k) | (a << (%d - k))" % b
            pre += "uint32_t k = %s; uint32_t r = k ? %s : a; " % (k, m(rot, sz))
            if kind == "rol":
                fl["cf"] = "r & 1"
                fl["of"] = "((r >> %d) ^ r) & 1" % (b - 1)
            else:
                fl["cf"] = "r >> %d" % (b - 1)
                fl["of"] = "((r >> %d) ^ (r >> %d)) & 1" % (b - 1, b - 2)
        pre += wrx("r")
        if const is None:
            return Tr(pre, fl, "} ", cond=True)
        return Tr(pre, fl)

    def t_shl(self, ins):
        return self.shift(ins, "shl")

    t_sal = t_shl

    def t_shr(self, ins):
        return self.shift(ins, "shr")

    def t_sar(self, ins):
        return self.shift(ins, "sar")

    def t_rol(self, ins):
        return self.shift(ins, "rol")

    def t_ror(self, ins):
        return self.shift(ins, "ror")

    def rc(self, ins, fn):
        d = ins.ops[0]
        cnt = self.rd(ins.ops[1]) if len(ins.ops) > 1 else "1"
        setup, rdx, wrx = self.dst(d)
        return Tr("%suint32_t r = %s(c, %s, %s, %d); %s" % (setup, fn, rdx, cnt, d.size * 8, wrx("r")),
                  uses=1, kills=0)

    def t_rcl(self, ins):
        return self.rc(ins, "rt_rcl")

    def t_rcr(self, ins):
        return self.rc(ins, "rt_rcr")

    def dshift(self, ins, fn):
        d, s, cnt = ins.ops
        setup, rdx, wrx = self.dst(d)
        return Tr("%suint32_t r = %s(c, %s, %s, %s, %d); %s" % (
            setup, fn, rdx, self.rd(s), self.rd(cnt), d.size * 8, wrx("r")), kills=0)

    def t_shld(self, ins):
        return self.dshift(ins, "rt_shld")

    def t_shrd(self, ins):
        return self.dshift(ins, "rt_shrd")

    # ------------------------------------------------------ multiply/divide
    def t_mul(self, ins):
        s = ins.ops[0]
        v = self.rd(s)
        if s.size == 4:
            return Tr("uint64_t t = (uint64_t)EAX * %s; EAX = (uint32_t)t; EDX = (uint32_t)(t >> 32); " % v,
                      {"cf": "(t >> 32) != 0", "of": "(t >> 32) != 0"})
        if s.size == 2:
            return Tr("uint32_t t = (uint32_t)AX * %s; AX = (uint16_t)t; DX = (uint16_t)(t >> 16); " % v,
                      {"cf": "(t >> 16) != 0", "of": "(t >> 16) != 0"})
        return Tr("uint32_t t = (uint32_t)AL * %s; AX = (uint16_t)t; " % v,
                  {"cf": "(t >> 8) != 0", "of": "(t >> 8) != 0"})

    def t_imul(self, ins):
        ops = ins.ops
        if len(ops) == 1:
            s = ops[0]
            v = self.rd(s)
            if s.size == 4:
                return Tr("int64_t t = (int64_t)(int32_t)EAX * (int32_t)%s; EAX = (uint32_t)t; "
                          "EDX = (uint32_t)((uint64_t)t >> 32); " % v,
                          {"cf": "t != (int32_t)t", "of": "t != (int32_t)t"})
            if s.size == 2:
                return Tr("int32_t t = (int32_t)(int16_t)AX * (int16_t)%s; AX = (uint16_t)t; "
                          "DX = (uint16_t)((uint32_t)t >> 16); " % v,
                          {"cf": "t != (int16_t)t", "of": "t != (int16_t)t"})
            return Tr("int32_t t = (int32_t)(int8_t)AL * (int8_t)%s; AX = (uint16_t)t; " % v,
                      {"cf": "t != (int8_t)t", "of": "t != (int8_t)t"})
        d = ops[0]
        sz = d.size
        if len(ops) == 2:
            a, b = self.rd(d), self.rd(ops[1], sz)
        else:
            a, b = self.rd(ops[1], sz), self.rd(ops[2], sz)
        st = STYPE[sz]
        pre = "int64_t t = (int64_t)(%s)%s * (int64_t)(%s)%s; %s" % (st, a, st, b, self.wr(d, "(uint32_t)t"))
        return Tr(pre, {"cf": "t != (%s)t" % st, "of": "t != (%s)t" % st})

    def t_div(self, ins):
        s = ins.ops[0]
        return Tr("rt_div%d(c, %s, 0x%08xu);" % (s.size * 8, self.rd(s), ins.addr))

    def t_idiv(self, ins):
        s = ins.ops[0]
        return Tr("rt_idiv%d(c, %s, 0x%08xu);" % (s.size * 8, self.rd(s), ins.addr))

    # ------------------------------------------------------------- bit ops
    def bitop(self, ins, kind):
        d, s = ins.ops
        sz = d.size
        if sz not in (2, 4):
            raise Unsupported("bt size")
        b = sz * 8
        idx = self.rd(s, sz)
        if d.t == "m" and s.t == "r":
            # bit string addressing: the bit offset may reach outside the addressed word
            pre = "int32_t i = %s; uint32_t m = %s + (uint32_t)((i >> %d) * %d); uint32_t a = ld%d(m), k = (uint32_t)i & %d; " % (
                sx(idx, sz), self.ea(d), 5 if sz == 4 else 4, sz, b, b - 1)
            wrx = lambda v: "st%d(m, %s); " % (b, v)
        else:
            setup, rdx, wrx = self.dst(d)
            pre = "%suint32_t a = %s, k = %s & %d; " % (setup, rdx, idx, b - 1)
        if kind == "bts":
            pre += wrx("a | (1u << k)")
        elif kind == "btr":
            pre += wrx("a & ~(1u << k)")
        elif kind == "btc":
            pre += wrx("a ^ (1u << k)")
        return Tr(pre, {"cf": "(a >> k) & 1"})

    def t_bt(self, ins):
        return self.bitop(ins, "bt")

    def t_bts(self, ins):
        return self.bitop(ins, "bts")

    def t_btr(self, ins):
        return self.bitop(ins, "btr")

    def t_btc(self, ins):
        return self.bitop(ins, "btc")

    def t_bsf(self, ins):
        d, s = ins.ops
        return Tr("uint32_t a = %s; if (a) { %s} " % (self.rd(s), self.wr(d, "(uint32_t)__builtin_ctz(a)")),
                  {"zf": "a == 0"})

    def t_bsr(self, ins):
        d, s = ins.ops
        return Tr("uint32_t a = %s; if (a) { %s} " % (self.rd(s), self.wr(d, "31u - (uint32_t)__builtin_clz(a)")),
                  {"zf": "a == 0"})

    # ----------------------------------------------------------- string ops
    def strop(self, ins, name):
        op = ins.opc[0]
        if op & 1:
            bits = 16 if ins.opsize16 else 32
        else:
            bits = 8
        for o in ins.ops:
            if o.t == "m" and o.seg in ("fs", "gs"):
                raise Unsupported("string op with segment override")
        compare = name in ("cmps", "scas")
        if ins.rep:
            if compare:
                want = 0 if ins.rep == "repne" else 1
                return Tr("rt_rep_%s%d(c, %d);" % (name, bits, want), kills=0)
            if name == "lods":
                raise Unsupported("rep lods")
            return Tr("rt_rep_%s%d(c);" % (name, bits))
        if name == "lods":
            acc = {8: "AL", 16: "AX", 32: "EAX"}[bits]
            return Tr("%s = rt_lods%d(c);" % (acc, bits))
        if compare:
            return Tr("rt_%s%d(c);" % (name, bits), kills=ALL_FLAGS)
        return Tr("rt_%s%d(c);" % (name, bits))

    def _str(self, ins, lo, name):
        if ins.opc[0] not in (lo, lo + 1):
            raise Unsupported(ins.mn)
        return self.strop(ins, name)

    def t_movsb(self, ins):
        return self._str(ins, 0xA4, "movs")

    t_movsw = t_movsd = t_movsb

    def t_stosb(self, ins):
        return self._str(ins, 0xAA, "stos")

    t_stosw = t_stosd = t_stosb

    def t_lodsb(self, ins):
        return self._str(ins, 0xAC, "lods")

    t_lodsw = t_lodsd = t_lodsb

    def t_cmpsb(self, ins):
        return self._str(ins, 0xA6, "cmps")

    t_cmpsw = t_cmpsd = t_cmpsb

    def t_scasb(self, ins):
        return self._str(ins, 0xAE, "scas")

    t_scasw = t_scasd = t_scasb

    # ------------------------------------------------------------------ x87
    @staticmethod
    def farith(grp, a, b):
        return {0: "%s + %s", 1: "%s * %s", 4: "%s - %s", 6: "%s / %s"}[grp] % (a, b) if grp in (0, 1, 4, 6) \
            else {5: "%s - %s", 7: "%s / %s"}[grp] % (b, a)

    def x87(self, ins):
        op0 = ins.opc[0]
        modrm = ins.modrm
        grp = (modrm >> 3) & 7
        i = modrm & 7
        if modrm < 0xC0:
            return self.x87_mem(ins, op0, grp)
        sti = "ST(%d)" % i
        if op0 == 0xD8:
            if grp == 2:
                return Tr("rt_fcom(c, ST(0), %s);" % sti)
            if grp == 3:
                return Tr("rt_fcom(c, ST(0), %s); fpop(c);" % sti)
            return Tr("ST(0) = rt_fpr(c, %s);" % self.farith(grp, "ST(0)", sti))
        if op0 == 0xD9:
            if grp == 0:
                return Tr("{ double v = %s; fpush(c, v); }" % sti)
            if grp == 1:
                return Tr("{ double v = ST(0); ST(0) = %s; %s = v; }" % (sti, sti))
            simple = {
                0xD0: "",
                0xE0: "ST(0) = -ST(0);",
                0xE1: "ST(0) = fabs(ST(0));",
                0xE4: "rt_fcom(c, ST(0), 0.0);",
                0xE5: "rt_fxam(c);",
                0xE8: "fpush(c, 1.0);",
                0xE9: "fpush(c, 3.3219280948873623);",
                0xEA: "fpush(c, 1.4426950408889634);",
                0xEB: "fpush(c, 3.14159265358979323846);",
                0xEC: "fpush(c, 0.30102999566398120);",
                0xED: "fpush(c, 0.69314718055994531);",
                0xEE: "fpush(c, 0.0);",
                0xF0: "ST(0) = expm1(ST(0) * 0.69314718055994531);",
                0xF1: "{ double v = ST(1) * log2(ST(0)); fpop(c); ST(0) = v; }",
                0xF2: "ST(0) = tan(ST(0)); fpush(c, 1.0); c->fsw &= ~FSW_C2;",
                0xF3: "{ double v = atan2(ST(1), ST(0)); fpop(c); ST(0) = v; }",
                0xF4: "rt_fxtract(c);",
                0xF5: "rt_fprem(c, 1);",
                0xF6: "c->ftop = (c->ftop - 1) & 7;",
                0xF7: "c->ftop = (c->ftop + 1) & 7;",
                0xF8: "rt_fprem(c, 0);",
                0xF9: "{ double v = ST(1) * (log1p(ST(0)) / 0.69314718055994531); fpop(c); ST(0) = v; }",
                0xFA: "ST(0) = rt_fpr(c, sqrt(ST(0)));",
                0xFB: "{ double v = ST(0); ST(0) = sin(v); fpush(c, cos(v)); c->fsw &= ~FSW_C2; }",
                0xFC: "ST(0) = rt_fround(c, ST(0));",
                0xFD: "ST(0) = ldexp(ST(0), (int)fmax(fmin(trunc(ST(1)), 65536.0), -65536.0));",
                0xFE: "ST(0) = sin(ST(0)); c->fsw &= ~FSW_C2;",
                0xFF: "ST(0) = cos(ST(0)); c->fsw &= ~FSW_C2;",
            }
            if modrm in simple:
                return Tr(simple[modrm])
        if op0 in (0xDA, 0xDB) and modrm < 0xE0:
            cc = {0: "c->cf", 1: "c->zf", 2: "(c->cf | c->zf)", 3: "c->pf"}[grp & 3]
            uses = {0: 1, 1: 8, 2: 9, 3: 2}[grp & 3]
            neg = "!" if op0 == 0xDB else ""
            return Tr("if (%s%s) ST(0) = %s;" % (neg, cc, sti), uses=uses)
        if op0 == 0xDA and modrm == 0xE9:
            return Tr("rt_fcom(c, ST(0), ST(1)); fpop(c); fpop(c);")
        if op0 == 0xDB:
            if modrm == 0xE2:
                return Tr("c->fsw &= 0x7f00;")
            if modrm == 0xE3:
                return Tr("c->fcw = 0x37f; c->fsw = 0; c->ftop = 0; c->ftag = 0;")
            if grp in (5, 6):
                return Tr("rt_fcomi(c, ST(0), %s);" % sti, kills=ALL_FLAGS)
        if op0 == 0xDC:
            if grp == 2:
                return Tr("rt_fcom(c, ST(0), %s);" % sti)
            if grp == 3:
                return Tr("rt_fcom(c, ST(0), %s); fpop(c);" % sti)
            # register-destination forms: sub/subr and div/divr are swapped relative to D8
            g = {0: 0, 1: 1, 4: 5, 5: 4, 6: 7, 7: 6}[grp]
            return Tr("%s = rt_fpr(c, %s);" % (sti, self.farith(g, sti, "ST(0)")))
        if op0 == 0xDD:
            if grp == 0:
                return Tr("c->ftag &= (uint8_t)~(1u << ((c->ftop + %d) & 7));" % i)
            if grp == 2:
                return Tr("%s = ST(0);" % sti)
            if grp == 3:
                return Tr("%s = ST(0); fpop(c);" % sti)
            if grp == 4:
                return Tr("rt_fcom(c, ST(0), %s);" % sti)
            if grp == 5:
                return Tr("rt_fcom(c, ST(0), %s); fpop(c);" % sti)
        if op0 == 0xDE:
            if modrm == 0xD9:
                return Tr("rt_fcom(c, ST(0), ST(1)); fpop(c); fpop(c);")
            if grp in (0, 1, 4, 5, 6, 7):
                g = {0: 0, 1: 1, 4: 5, 5: 4, 6: 7, 7: 6}[grp]
                return Tr("%s = rt_fpr(c, %s); fpop(c);" % (sti, self.farith(g, sti, "ST(0)")))
        if op0 == 0xDF:
            if modrm == 0xE0:
                return Tr("AX = rt_fnstsw(c);")
            if grp in (5, 6):
                return Tr("rt_fcomi(c, ST(0), %s); fpop(c);" % sti, kills=ALL_FLAGS)
            if grp == 0:
                return Tr("c->ftag &= (uint8_t)~(1u << ((c->ftop + %d) & 7)); fpop(c);" % i)
        raise Unsupported(ins.mn)

    def x87_mem(self, ins, op0, grp):
        if not ins.ops or ins.ops[0].t != "m":
            raise Unsupported(ins.mn)
        a = self.ea(ins.ops[0])
        if op0 in (0xD8, 0xDC, 0xDA, 0xDE):
            src = {0xD8: "ldf32(%s)", 0xDC: "ldf64(%s)", 0xDA: "(double)(int32_t)ld32(%s)",
                   0xDE: "(double)(int16_t)ld16(%s)"}[op0] % a
            if grp == 2:
                return Tr("rt_fcom(c, ST(0), %s);" % src)
            if grp == 3:
                return Tr("rt_fcom(c, ST(0), %s); fpop(c);" % src)
            return Tr("ST(0) = rt_fpr(c, %s);" % self.farith(grp, "ST(0)", src))
        table = {
            (0xD9, 0): "fpush(c, ldf32(%s));",
            (0xD9, 2): "stf32(%s, ST(0));",
            (0xD9, 3): "stf32(%s, ST(0)); fpop(c);",
            (0xD9, 4): "rt_fldenv(c, %s);",
            (0xD9, 5): "c->fcw = ld16(%s);",
            (0xD9, 6): "rt_fnstenv(c, %s);",
            (0xD9, 7): "st16(%s, c->fcw);",
            (0xDB, 0): "fpush(c, (double)(int32_t)ld32(%s));",
            (0xDB, 2): "st32(%s, rt_fist32(c, ST(0)));",
            (0xDB, 3): "st32(%s, rt_fist32(c, ST(0))); fpop(c);",
            (0xDB, 5): "fpush(c, rt_ld80(%s));",
            (0xDB, 7): "rt_st80(%s, ST(0)); fpop(c);",
            (0xDD, 0): "fpush(c, ldf64(%s));",
            (0xDD, 2): "stf64(%s, ST(0));",
            (0xDD, 3): "stf64(%s, ST(0)); fpop(c);",
            (0xDD, 4): "rt_frstor(c, %s);",
            (0xDD, 6): "rt_fnsave(c, %s);",
            (0xDD, 7): "st16(%s, rt_fnstsw(c));",
            (0xDF, 0): "fpush(c, (double)(int16_t)ld16(%s));",
            (0xDF, 2): "st16(%s, rt_fist16(c, ST(0)));",
            (0xDF, 3): "st16(%s, rt_fist16(c, ST(0))); fpop(c);",
            (0xDF, 5): "fpush(c, (double)(int64_t)ld64(%s));",
            (0xDF, 7): "st64(%s, rt_fist64(c, ST(0))); fpop(c);",
        }
        code = table.get((op0, grp))
        if code is None:
            raise Unsupported(ins.mn)
        return Tr(code % a)
