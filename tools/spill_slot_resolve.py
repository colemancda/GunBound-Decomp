import json, re, sys, collections
sys.path.insert(0,'tools')
import capstone
from reg_trace_caller import load, caller_of, disasm_function
import esp_frame_model as E
import callsites, os as _os

# the caller's own declared parameter count, to validate a computed index
_ARITY={}
for _b,_,_fs in _os.walk('src'):
    for _f in _fs:
        if not _f.endswith(('.c','.cpp')): continue
        _p=_os.path.join(_b,_f); _t=open(_p,errors='replace').read()
        _bl=callsites.blank_comments(_t)
        for _c in callsites.find(_t,_os.path.splitext(_f)[0],_bl):
            if _c['kind']=='definition':
                _a=callsites.split_args(_t[_c['open']:_c['close']])
                _ARITY[_os.path.splitext(_f)[0]] = 0 if (len(_a)==1 and _a[0].strip() in ('void','')) else len(_a)
base,data,funcs=load(); md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
rows=json.load(open('tools/reg_trace.json'))
cache={}
stat=collections.Counter(); found=[]
for r in rows:
    if r['form']!='FRAME': continue
    m=re.match(r'(esp|ebp)([-+])(0x[0-9a-f]+)$', r['detail'])
    if not m: stat['unparsed']+=1; continue
    va=int(r['va'],16); c=caller_of(funcs,va)
    if not c: stat['no-caller']+=1; continue
    if c[0] not in cache: cache[c[0]]=disasm_function(md,data,base,c[0],c[1])
    ins=cache[c[0]]
    mrows,ebp=E.model(ins)
    d=next((dl for i,dl,_ in mrows if i.address==va), None)
    if d is None: stat['call-not-in-fn']+=1; continue
    num=int(m.group(3),0); v=num if m.group(2)=='+' else -num
    off = d+v if m.group(1)=='esp' else (ebp+v if ebp is not None else None)
    if off is None: stat['no-ebp-frame']+=1; continue
    # the model's own trust flag at the call must be honoured on EVERY path,
    # including the caller-parameter one -- otherwise an unsafe model still
    # produces a confident "caller param_N".
    call_ok=next((o for i,dl,o in mrows if i.address==va), False)
    if not call_ok:
        stat['model-unsafe']+=1; continue
    got=E.slot_source(ins, va, off, ebp)
    if not got:
        # frame offset >= +4 is the CALLER's own incoming stack parameter
        # (its return address sits at 0), not an unwritten local.  Those are
        # nameable: parameter index = (off - 4) / 4.
        # Sanity bound.  A real function has a handful of stack parameters,
        # so a "parameter" at frame +12668 is not a parameter -- it is proof
        # the esp model drifted in that caller (a missed sub esp, or a branch
        # the linear walk mis-tracked).  Rejecting those is the whole point:
        # an unbounded reading would report param_3167 with a straight face.
        idx=(off-4)//4+1
        declared=_ARITY.get(r['caller'])
        # Validate against the caller's OWN declared arity rather than a
        # guessed ceiling.  If the index exceeds what the caller actually
        # takes, the esp model drifted -- that is a fact about this caller,
        # not a threshold someone picked.
        if 4 <= off and declared is not None and idx <= declared:
            stat['CALLER-PARAM']+=1
            found.append((r['func'], r['reg'], r['caller'], r['detail'],
                          'caller param_%d (frame +%d)'%((off-4)//4+1, off)))
        elif off >= 4:
            stat['index-exceeds-caller-arity']+=1
        else:
            stat['unwritten-local']+=1
        continue
    i,ok = got
    if not ok: stat['model-unsafe']+=1; continue
    src=i.op_str.split(',',1)[1].strip() if ',' in i.op_str else ''
    stat['RESOLVED']+=1
    found.append((r['func'], r['reg'], r['caller'], r['detail'], '%s %s'%(i.mnemonic,i.op_str)))
print('FRAME-form pairs:', sum(stat.values()))
for k,v in stat.most_common(): print('   %-22s %d'%(k,v))
print()
for f in found[:26]: print('  %-24s %-4s %-28s %-12s <- %s'%f)
