"""Translate a raw MobileNN_MainAction.c body into the CMobile method style
(the Mobile00/Mobile01 template).  Mechanical recipe from 43a7ee7."""
import re, sys

def translate(path, nn, addr):
    src = open(path).read()
    body = src[src.index('{', src.index('_MainAction(')):]
    # SEH-state locals: names used ONLY as constant stores (plus the fixed
    # SEH scaffolding).  A uStack_NN with any real use stays.
    seh = {'local_4', 'local_c', 'puStack_8', 'uStack_10', 'unaff_FS_OFFSET'}
    import collections
    uses = collections.defaultdict(list)
    for m in re.finditer(r'\b(uStack_[0-9a-f]+)\b', body):
        uses[m.group(1)].append(m.start())
    for name in uses:
        occ = re.findall(r'[^\n]*\b%s\b[^\n]*' % name, body)
        if all(re.match(r'\s*(undefined4 %s;|%s = (0x[0-9a-f]+|\d+);|'
                        r'%s = CONCAT31\(SUBFIELD\(%s,.*)$'
                        % (name, name, name, name), o.strip())
               for o in occ):
            seh.add(name)
    lines = body.split('\n')
    out = []
    guard_stack = []
    for l in lines:
        ls = l.strip()
        # --- strip SEH scaffolding ---
        m = re.match(r'(?:undefined4 \*?|int |undefined1 \*)?(\w+)(?: = .*)?;$', ls)
        if m and m.group(1) in seh:
            continue
        if re.match(r"(\*unaff_FS_OFFSET = |SUBFIELD\(local_4)", ls):
            continue
        mm = re.match(r'(\w+) = CONCAT31\(SUBFIELD\(\1,', ls)
        if mm and mm.group(1) in seh:
            continue
        if re.match(r'(\w+) = &LAB_', ls) and ls.split(' ')[0] in seh:
            continue
        # --- params ---
        l = re.sub(r'\bswitch\(param_2\)', 'switch (animEvent)', l)
        l = re.sub(r'\bparam_2\b', 'animEvent', l)
        l = re.sub(r'\bparam_3\b', 'subType', l)
        # --- 2-arg bool peek ---
        l = re.sub(r'PeekPacketChecksumBool\((uVar\d+|local_\w+),\s*(\d+)\)',
                   r'PeekPacketChecksumBool_2(\1, \2)', l)
        # --- owner ---
        l = l.replace('*(undefined1 *)(param_1 + 8)', '(char)this->m_owner')
        # --- C-only spellings ---
        l = l.replace('(byte *)(g_clientContext + 0x6a7f74)',
                      '(unsigned char *)(g_clientContext + 0x6a7f74)')
        l = re.sub(r'\(uint\)', '(unsigned int)', l)
        l = re.sub(r'\(byte \*\)', '(unsigned char *)', l)
        # --- bool cells ---
        l = re.sub(r'\(byte \*\)\(param_1 \+ (0x[0-9a-f]+)\)',
                   r'(unsigned char *)this + \1', l)
        # --- typed field accesses ---
        def fld(off):
            o = int(off, 16)
            if o >= 0xae22:
                return 'this->m_padae22 + 0x%x' % (o - 0xae22)
            if o >= 0x908:
                return 'this->m_pad908 + 0x%x' % (o - 0x908)
            return '(unsigned char *)this + 0x%x' % o
        l = re.sub(r'\*\(int \*\)\(param_1 \+ (0x[0-9a-f]+)\)',
                   lambda m: '*reinterpret_cast<int *>(%s)' % fld(m.group(1)), l)
        l = re.sub(r'\*\(undefined4 \*\)\(param_1 \+ (0x[0-9a-f]+)\)',
                   lambda m: '*reinterpret_cast<unsigned int *>(%s)' % fld(m.group(1)), l)
        l = re.sub(r'\*\(ushort \*\)\(param_1 \+ (0x[0-9a-f]+)\)',
                   lambda m: '*reinterpret_cast<unsigned short *>(%s)' % fld(m.group(1)), l)
        l = re.sub(r'\*\(char \*\)\(param_1 \+ (0x[0-9a-f]+)\)',
                   lambda m: ('this->m_pad908[0x%x]' % (int(m.group(1),16)-0x908))
                             if 0x908 <= int(m.group(1),16) < 0xae22 else
                             ('this->m_padae22[0x%x]' % (int(m.group(1),16)-0xae22)), l)
        # bare pointer-arith args (guard cells / aim cells)
        l = re.sub(r'(?<![\w>])param_1 \+ (0x[0-9a-f]+)', lambda m: fld(m.group(1)), l)
        # --- EncodeChecksumPairDiff 3rd arg is unsigned int in the C++ proto ---
        l = re.sub(r'EncodeChecksumPairDiff\(([^,]+),\s*(\w+),\s*(this->m_pad908 \+ 0x[0-9a-f]+)\)',
                   r'EncodeChecksumPairDiff(\1, \2, reinterpret_cast<unsigned int>(\3))', l)
        # --- PeekChecksumStateUnderLock takes void*; peeked-back cell handles are uVar ints ---
        l = re.sub(r'PeekChecksumStateUnderLock\((uVar\d+|local_1[0-9a-f]{3})\)',
                   r'PeekChecksumStateUnderLock(reinterpret_cast<void *>(\1))', l)
        # --- CONCAT31 flag ---
        l = re.sub(r'CONCAT31\([^;]*?,\s*\n?', '', l) if False else l
        # --- types ---
        l = re.sub(r'^(\s*)undefined4 ([a-zA-Z_]\w*);', r'\1unsigned int \2;', l)
        l = re.sub(r'^(\s*)undefined1 (\w+) \[(\d+)\];',
                   lambda m: '%sunsigned char %s[0x%x];' % (m.group(1), m.group(2), int(m.group(3))), l)
        l = re.sub(r'^(\s*)undefined \*puVar', r'\1unsigned char *puVar', l)
        l = re.sub(r'^(\s*)uint uVar', r'\1unsigned int uVar', l)
        # vtable teardown idiom (any iVarN)
        l = re.sub(r'\(\*\*\(code \*\*\)\(\*\*\(int \*\*\)\(DAT_00793554 \+ (\w+) \* 4\) \+ 0xc\)\)\(\);',
                   r'int *obj = *reinterpret_cast<int **>(DAT_00793554 + \1 * 4);\n'
                   r'                (*reinterpret_cast<void (**)()>(*obj + 0xc))();', l)
        # cell pointers stashed in Ghidra int locals
        l = re.sub(r'^(\s*)(iVar\d+) = (this->m_pad908 \+ 0x[0-9a-f]+);',
                   r'\1\2 = reinterpret_cast<int>(\3);', l)
        l = re.sub(r'(EncodeChecksumPair(?:Diff|Sum))\((iVar\d+),',
                   r'\1(reinterpret_cast<void *>(\2),', l)
        l = re.sub(r'(EncodeChecksumPairSum\([^;]+,)(iVar\d+)\);',
                   r'\1reinterpret_cast<void *>(\2));', l)
        # --- guard scrub tracking ---
        m = re.search(r'EncodeChecksum(?:PairDiff|PairSum|Negate|Delta\w+)\([^,]+,\s*(\w+)[,)]', l)
        if m and re.match(r'(local_|auStack_)', m.group(1)):
            guard_stack.append(m.group(1))
        if ls == 'ScrubChecksumGuard();':
            if guard_stack:
                l = l.replace('ScrubChecksumGuard();',
                              'ScrubChecksumGuard(%s);' % guard_stack.pop())
        out.append(l)
    body = '\n'.join(out)
    # CONCAT31 multi-line: collapse `CONCAT31((int3)((uint)*X >> 8),\n  *X != 0)` -> `*X != 0`
    body = re.sub(r'CONCAT31\(\(int3\)\(\(unsigned int\)\*reinterpret_cast<int \*>\(([^)]+\)) >> 8\),\s*\n\s*\*reinterpret_cast<int \*>\(\1 != 0\)',
                  r'*reinterpret_cast<int *>(\1 != 0', body)
    body = re.sub(r'CONCAT31\(\(int3\)\(\(uint\)([^,]+) >> 8\),\s*\n?\s*([^)]+ != 0)\)', r'\2', body)
    # multi-line CONCAT31 with reinterpret_cast inside (post-transform shape)
    body = re.sub(r'CONCAT31\(\(int3\)\(\(uint\)(\*reinterpret_cast<int \*>\([^)]+\)) >> 8\),\s*\n\s*(\*reinterpret_cast<int \*>\([^)]+\) != 0)\)', r'\2', body)
    # leftover undefined4 stores (the DAT_005f3768 turn-transition pokes)
    body = re.sub(r'\*\(undefined4 \*\)\(([^)]+)\)', r'*reinterpret_cast<unsigned int *>(\1)', body)
    body = re.sub(r'\*\(undefined1 \*\)\(([^)]+)\)', r'*reinterpret_cast<unsigned char *>(\1)', body)
    body = re.sub(r'\*\(int \*\)\(([^)]+)\)', r'*reinterpret_cast<int *>(\1)', body)
    body = re.sub(r'\*\(char \*\)\(([^)]+)\)', r'*reinterpret_cast<char *>(\1)', body)
    hdr = ('/* 0x%s Mobile%s_MainAction - mobile TYPE %d\'s vtable-slot-7 weapon-fire\n'
           ' * dispatcher, promoted with the Mobile00/Mobile01 mechanical recipe\n'
           ' * (43a7ee7): SEH stripped, guard scratch as 0x224 buffers, scrub order =\n'
           ' * SEH unwind order, faithful control flow and argument shapes.  The raw\n'
           ' * port (src/battle/Mobile%s_MainAction.c) remains the linking reference. */\n'
           'void CMobile::Mobile%s_MainAction(int animEvent, int subType)\n') % (addr, nn, int(nn), nn, nn)
    return hdr + body

if __name__ == '__main__':
    nn, addr = sys.argv[1], sys.argv[2]
    print(translate('src/battle/Mobile%s_MainAction.c' % nn, nn, addr))

# LIMITS (2026-08-18): handles the standard MainAction decompile shape only.
# Mobile04/06/12 have artifact-heavy decompiles (return-address stack
# artifacts, undefined8 spill modeling; Mobile06's clean twin FUN_0049c13f.c
# dropped every spawn argument) - those need hand translation, not this tool.
# Driver used for the 11-method run: translate NN ADDR, append to Mobile.cpp,
# insert the Mobile.h decl after the Mobile00 anchor line, compile with the
# gb-check MSVC, commit one method per commit.
