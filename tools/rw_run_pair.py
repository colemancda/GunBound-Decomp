"""Pair RemoveWidget call sites to source using straight-line RUNS.

A run is a maximal stretch with no control flow in it. Inside a run, source
order must equal VA order - that is the one ordering assumption that is not an
assumption. Runs are delimited on BOTH sides:
  binary: any jmp/jcc/ret, or an address that is a branch target
  source: goto/break/case/label/if/while/}/{ - anything that is not a call
Each run is identified by the CreateButtonWidget that opens it, whose (key,id)
literals are unique within the function.
"""
import struct,re,csv,bisect,sys,json,collections
import pefile,capstone
RW=0x405fb0; CBW=0x406020
rows=[]
for r in csv.reader(open('PROGRESS.csv')):
    try: a=int(r[0],16); n=int(r[1])
    except Exception: continue
    rows.append((a,n,r[2]))
rows.sort()
def span(name):
    for a,n,nm in rows:
        if nm==name: return a,a+n
pe=pefile.PE('orig/GunBound.gme',fast_load=True); ib=pe.OPTIONAL_HEADER.ImageBase
sec=[s for s in pe.sections if s.Name.rstrip(b'\x00')==b'.text'][0]
base=ib+sec.VirtualAddress; data=sec.get_data()
md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)

def binary_runs(name, srclabels=None):
    a,b=span(name)
    ins=list(md.disasm(data[a-base:b-base],a))
    targets=set()
    for i in ins:
        if i.mnemonic.startswith('j') and i.op_str.startswith('0x'): targets.add(int(i.op_str,16))
    # Only break at targets the SOURCE can also see. Ghidra emits LAB_ for the
    # targets it cannot express structurally; the rest it renders as if/else,
    # which the source-side tokenizer already breaks on. Breaking at every
    # target makes the binary runs finer than the source runs, and then no
    # count ever matches.
    if srclabels is not None: targets &= srclabels
    runs=[]; key=None; buf=[]; pend=[]
    def flush():
        nonlocal key,buf
        if key is not None: runs.append({'key':key,'esi':buf})
        key=None; buf=[]
    for idx,i in enumerate(ins):
        if i.address in targets:
            flush(); key=('LAB',i.address)         # branch target: exact anchor
        if i.mnemonic=='push':
            m=re.fullmatch(r'0x[0-9a-f]+|\d+',i.op_str); pend.append(int(i.op_str,0) if m else None)
        elif i.mnemonic=='call' and i.op_str.startswith('0x'):
            t=int(i.op_str,16)
            if t==CBW:
                args=list(reversed(pend[-11:])) if len(pend)>=11 else None
                k=tuple(args[2:7]) if args and len(args)>6 else None
                if k is not None and key is None: key=k   # label anchor wins - it is exact
            elif t==RW:
                e=None
                for j in range(idx-1,max(0,idx-6),-1):
                    m=re.match(r'esi, (0x[0-9a-f]+|\d+)$',ins[j].op_str)
                    if m: e=int(m.group(1),0); break
                    if ins[j].op_str.startswith('esi,'): break
                buf.append(e)
            pend=[]
        elif i.mnemonic.startswith('j') or i.mnemonic=='ret':
            flush()
    flush()
    return [r for r in runs if r['key']]

def source_runs(path):
    # blank comments out RATHER THAN removing them, so every offset below is a
    # real offset into the file on disk - deleting them shifts every position
    src=re.sub(r'/\*.*?\*/',lambda m:' '*(m.end()-m.start()),
               open(path,errors='replace').read(),flags=re.S)
    runs=[]; key=None; buf=[]
    def flush():
        nonlocal key,buf
        if key is not None: runs.append({'key':key,'pos':buf})
        key=None; buf=[]
    tok=re.compile(r'\bCreateButtonWidget\s*\(|\bRemoveWidget\s*\(|\bgoto\b|\bbreak\b|\bcase\b|\bdefault\b|\bLAB_00[0-9a-f]{6}:|\bif\b|\bwhile\b|\bfor\b|\belse\b|[{}]')
    for m in tok.finditer(src):
        t=m.group(0)
        if t.startswith('CreateButtonWidget'):
            d=1; j=m.end()
            while d and j<len(src):
                if src[j]=='(':d+=1
                elif src[j]==')':d-=1
                j+=1
            a=[x.strip() for x in re.split(r',(?![^()]*\))',src[m.end():j-1])]
            def num(x):
                try: return int(x,0)
                except Exception: pass
                # Ghidra's string symbols carry their own address: s_foo_0055412c
                m2=re.search(r'_00([0-9a-f]{6})$',x)
                return int(m2.group(1),16) if m2 else None
            k=tuple(num(x) for x in a[2:7]) if len(a)>6 else None
            if k is not None and key is None: key=k   # label anchor wins - it is exact
        elif t.startswith('RemoveWidget'):
            # count ALREADY-RECOVERED calls too, or their absence desynchronises
            # the run against the binary and the whole run gets skipped
            j=m.end(); d=1
            while d and j<len(src):
                if src[j]=='(':d+=1
                elif src[j]==')':d-=1
                j+=1
            buf.append((m.start(),src[m.end():j-1].strip()==''))
        elif t.startswith('LAB_'):
            flush(); key=('LAB',int(t[6:12],16))   # label: exact anchor
        else:
            flush()
    flush()
    return [r for r in runs if r['key']],src

name,path=sys.argv[1],sys.argv[2]
s,src=source_runs(path)
srclabels={int(m.group(1),16) for m in re.finditer(r'\bLAB_00([0-9a-f]{6})\b',src)}
b=binary_runs(name,srclabels)
def uniq(runs):
    '''Drop runs whose key is not unique - an ambiguous key cannot pair anything,
    and aborting the whole function over one loses every unambiguous run in it.'''
    seen=collections.Counter(r['key'] for r in runs)
    return {r['key']:r for r in runs if seen[r['key']]==1}, sum(1 for r in runs if seen[r['key']]>1)
bk,bdup=uniq(b); sk,sdup=uniq(s)
if bdup or sdup: print('ambiguous runs dropped: %d binary, %d source'%(bdup,sdup))
pairs=[]; mism=0
for k,sr in sk.items():
    br=bk.get(k)
    if br is None or len(br['esi'])!=len(sr['pos']) or any(e is None for e in br['esi']):
        if sr['pos'] or (br and br['esi']): mism+=1
        continue
    for (pos,argless),e in zip(sr['pos'],br['esi']):
        if argless: pairs.append((pos,e))      # skip sites already recovered
print('runs: binary %d, source %d'%(len(b),len(s)))
print('runs paired cleanly: %d ; runs skipped: %d'%(len(sk)-mism,mism))
print('RemoveWidget calls paired: %d'%len(pairs))
json.dump([[p,e] for p,e in pairs],open(sys.argv[3],'w'),indent=1)
