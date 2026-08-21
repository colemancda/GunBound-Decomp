#!/usr/bin/env python3
"""Variant of rw_fingerprint_pair.py: fingerprint includes LITERAL ARGUMENTS.

Each call in a run contributes (callee name, set of its literal argument
values) instead of just the name. Use it ALONGSIDE the name-only version and
union the results, never instead of it:

  name-only  16 sites - loses runs whose callee tuples collide
  with args    2 sites - far stricter, because the binary pushes values the
               source never renders as literals (addresses, globals), so the
               sets often fail to match even for the same call

They disagree about which runs they can key, but not about any site they both
key: unioning them across all callers gives 0 conflicting assignments. Sets
rather than tuples, because the binary pushes arguments right-to-left and only
the stack ones, so positional comparison does not survive.

Original description follows.

Pair RemoveWidget call sites to source by the CALL FINGERPRINT of their run.

tools/rw_run_pair.py keys a straight-line run on the CreateButtonWidget it
contains. That works where such a landmark exists and is unique, and it runs
out - most remaining runs contain no CreateButtonWidget at all, e.g.

    QueueOutgoingPacketField(0);
    RemoveWidget(); RemoveWidget(); RemoveWidget(); RemoveWidget();
    CreateAvatarStoreButtons(param_1);

Here the run is identified by WHAT ELSE IT CALLS. Build, for each run, the
tuple of non-RemoveWidget callee names in order; that is the key. Runs whose
key is unique on both sides pair, and the RemoveWidget calls inside them pair
positionally - which is sound because a run is straight-line by construction.

Same boundaries as rw_run_pair.py: control flow on both sides, and the binary
only breaks at branch targets the source can also see.

Usage: python3 tools/rw_fingerprint_pair.py <func> <file.c> <out.json>
"""
import struct,re,csv,sys,json,collections
import pefile,capstone
RW=0x405fb0
rows=[]
for r in csv.reader(open('PROGRESS.csv')):
    try: a=int(r[0],16); n=int(r[1])
    except Exception: continue
    rows.append((a,n,r[2]))
rows.sort(); starts=[a for a,_,_ in rows]
import bisect
def nameof(va):
    i=bisect.bisect_right(starts,va)-1
    return rows[i][2] if i>=0 else None
def span(name):
    for a,n,nm in rows:
        if nm==name: return a,a+n
pe=pefile.PE('orig/GunBound.gme',fast_load=True); ib=pe.OPTIONAL_HEADER.ImageBase
sec=[s for s in pe.sections if s.Name.rstrip(b'\x00')==b'.text'][0]
base=ib+sec.VirtualAddress; data=sec.get_data()
md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)

def binary_runs(name, srclabels):
    a,b=span(name); ins=list(md.disasm(data[a-base:b-base],a))
    targets={int(i.op_str,16) for i in ins
             if i.mnemonic.startswith('j') and i.op_str.startswith('0x')} & srclabels
    runs=[]; cur={'calls':[],'esi':[]}; pend=[]
    def flush():
        nonlocal cur
        if cur['esi']: runs.append(cur)
        cur={'calls':[],'esi':[]}
    for idx,i in enumerate(ins):
        if i.address in targets: flush()
        if i.mnemonic=='push':
            m=re.fullmatch(r'0x[0-9a-f]+|\d+',i.op_str)
            pend.append(int(i.op_str,0) if m else None)
        elif i.mnemonic=='call' and i.op_str.startswith('0x'):
            t=int(i.op_str,16)
            if t==RW:
                e=None
                for j in range(idx-1,max(0,idx-6),-1):
                    m=re.match(r'esi, (0x[0-9a-f]+|\d+)$',ins[j].op_str)
                    if m: e=int(m.group(1),0); break
                    if ins[j].op_str.startswith('esi,'): break
                cur['esi'].append(e)
            else:
                cur['calls'].append((nameof(t),frozenset(x for x in pend if x is not None)))
            pend=[]
        elif i.mnemonic.startswith('j') or i.mnemonic=='ret':
            flush()
    flush()
    return runs

def source_runs(path):
    src=re.sub(r'/\*.*?\*/',lambda m:' '*(m.end()-m.start()),
               open(path,errors='replace').read(),flags=re.S)
    runs=[]; cur={'calls':[],'pos':[]}
    def flush():
        nonlocal cur
        if cur['pos']: runs.append(cur)
        cur={'calls':[],'pos':[]}
    tok=re.compile(r'\b([A-Za-z_]\w*)\s*\(|\bgoto\b|\bbreak\b|\bcase\b|\bdefault\b'
                   r'|\bLAB_00[0-9a-f]{6}:|\bif\b|\bwhile\b|\bfor\b|\belse\b|\breturn\b|[{}]')
    KW={'if','while','for','switch','return','sizeof','else','case','default','goto','break'}
    for m in tok.finditer(src):
        g=m.group(1)
        if g and g not in KW:
            if g=='RemoveWidget':
                j=m.end(); d=1
                while d and j<len(src):
                    if src[j]=='(':d+=1
                    elif src[j]==')':d-=1
                    j+=1
                cur['pos'].append((m.start(),src[m.end():j-1].strip()==''))
            else:
                j=m.end(); d=1
                while d and j<len(src):
                    if src[j]=='(':d+=1
                    elif src[j]==')':d-=1
                    j+=1
                def val(x):
                    x=x.strip()
                    try: return int(x,0)
                    except Exception: pass
                    m2=re.search(r'_00([0-9a-f]{6})$',x)
                    return int(m2.group(1),16) if m2 else None
                inner=src[m.end():j-1]
                args=tuple(val(x) for x in re.split(r',(?![^()]*\))',inner)) if inner.strip() else ()
                cur['calls'].append((g,frozenset(x for x in args if x is not None)))
        elif not g:
            flush()
    flush()
    return runs,src

name,path=sys.argv[1],sys.argv[2]
s,src=source_runs(path)
srclabels={int(m.group(1),16) for m in re.finditer(r'\bLAB_00([0-9a-f]{6})\b',src)}
b=binary_runs(name,srclabels)
def key(r): return (tuple(r['calls']), len(r.get('esi') or r.get('pos')))
def uniq(runs):
    c=collections.Counter(key(r) for r in runs)
    return {key(r):r for r in runs if c[key(r)]==1}
bk=uniq(b); sk=uniq(s)
pairs=[]
for k,sr in sk.items():
    br=bk.get(k)
    if br is None or any(e is None for e in br['esi']): continue
    for (pos,argless),e in zip(sr['pos'],br['esi']):
        if argless: pairs.append((pos,e))
print('runs: binary %d source %d  unique keys: %d / %d  paired: %d'
      %(len(b),len(s),len(bk),len(sk),len(pairs)))
json.dump(pairs,open(sys.argv[3],'w'),indent=1)
