#!/usr/bin/env python3
"""Classify EVERY open dropped-register pair in one pass over .text.

reg_uniformity_triage.py rescans the whole section per function, which is fine
for the top ten and hopeless for all ~485. This builds the E8 call map ONCE,
then classifies each open pair against it.

Buckets are the same, and the point is to see the SHAPE OF THE WHOLE BACKLOG
rather than its head: how much of it is mechanically sweepable, how much needs
a witness in the C, and how much needs analysis that does not exist yet.
"""
import bisect, collections, csv, json, os, re, struct, subprocess, sys
import capstone, pefile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SUB = {'eax': {'eax','ax','al'}, 'ebx': {'ebx','bx','bl'}, 'ecx': {'ecx','cx','cl'},
       'edx': {'edx','dx','dl'}, 'esi': {'esi','si'}, 'edi': {'edi','di'},
       'ebp': {'ebp','bp'}}

def classify(ins):
    if ins is None: return 'OTHER'
    if re.match(r'mov \w+, (0x[0-9a-f]+|\d+)$', ins): return 'IMMEDIATE'
    if re.match(r'xor (\w+), \1$', ins): return 'IMMEDIATE'
    if re.match(r'add \w+, 0x[0-9a-f]{6}$', ins): return 'CTX-REL'
    if 'esp +' in ins or 'ebp -' in ins: return 'STACK'
    if re.match(r'lea \w+, \[\w+ [-+] 0x[0-9a-f]+\]$', ins): return 'OBJ-REL'
    if re.match(r'(mov|lea) \w+, \w+$', ins): return 'REGISTER'
    return 'OTHER'

def main():
    subprocess.run([sys.executable, os.path.join(ROOT,'tools/dropped_reg_backlog.py'),
                    '--json','/tmp/_all_open.json','--top','0'],
                   capture_output=True, cwd=ROOT)
    openp = json.load(open('/tmp/_all_open.json'))
    rows=[]
    for r in csv.reader(open(os.path.join(ROOT,'PROGRESS.csv'))):
        try: rows.append((int(r[0],16), int(r[1]), r[2]))
        except ValueError: pass
    rows.sort()
    addr_of={nm:a for a,_,nm in rows}
    targets={}
    for e in openp:
        a=addr_of.get(e['func'])
        if a is not None: targets.setdefault(a,[]).append(e)

    pe=pefile.PE(os.path.join(ROOT,'orig/GunBound.gme'), fast_load=True)
    ib=pe.OPTIONAL_HEADER.ImageBase
    sec=[s for s in pe.sections if s.Name.rstrip(b'\x00')==b'.text'][0]
    base=ib+sec.VirtualAddress; data=sec.get_data()
    md=capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)

    sites=collections.defaultdict(list)          # target -> [call va]
    for off in range(len(data)-5):
        if data[off]!=0xE8: continue
        t=base+off+5+struct.unpack('<i',data[off+1:off+5])[0]
        if t in targets: sites[t].append(base+off)

    out=[]
    for t, entries in targets.items():
        vas=sites.get(t,[])
        if not vas: continue
        wins={}
        for va in vas:
            ins=None
            for s in range(80,8,-1):
                d=list(md.disasm(data[va-s-base:va-base+5], va-s))
                if d and any(i.address==va for i in d): ins=d; break
            wins[va]=ins or []
        for e in entries:
            b=collections.Counter()
            for va in vas:
                last=None
                for i in wins[va][:-1]:
                    if i.mnemonic in ('test','cmp','push','call','ret') or i.mnemonic.startswith('j'):
                        continue
                    if i.op_str.split(',')[0].strip() in SUB[e['reg']]:
                        last='%s %s'%(i.mnemonic,i.op_str)
                b[classify(last)]+=1
            n=sum(b.values())
            vals=collections.Counter()
            for va in vas:
                last=None
                for i in wins[va][:-1]:
                    if i.mnemonic in ('test','cmp','push','call','ret') or i.mnemonic.startswith('j'):
                        continue
                    if i.op_str.split(',')[0].strip() in SUB[e['reg']]:
                        last='%s %s'%(i.mnemonic,i.op_str)
                if last is None: continue
                m=re.match(r'mov \w+, (0x[0-9a-f]+|\d+)$',last)
                if m: vals[int(m.group(1),0)]+=1
                elif re.match(r'xor (\w+), \1$',last): vals[0]+=1
                else:
                    m=re.match(r'add \w+, (0x[0-9a-f]{6})$',last)
                    if m: vals['ctx+'+m.group(1)]+=1
            # Record the call-site VAs and the exact defining instruction at
            # each.  Without these a pair can only be handled in bulk; with
            # them a single-call-site pair can be read off directly, since
            # one binary site and one source site must correspond.
            per=[]
            for va in vas:
                last=None
                for i in wins[va][:-1]:
                    if i.mnemonic in ('test','cmp','push','call','ret') or i.mnemonic.startswith('j'):
                        continue
                    if i.op_str.split(',')[0].strip() in SUB[e['reg']]:
                        last='%s %s'%(i.mnemonic,i.op_str)
                per.append({'va':'0x%x'%va,'ins':last,'cls':classify(last)})
            out.append({'func':e['func'],'reg':e['reg'],'sites':n,
                        'values':{str(k):v for k,v in vals.most_common(4)},
                        'top':b.most_common(1)[0][0],'pct':100*b.most_common(1)[0][1]//n,
                        'buckets':dict(b),'path':e['path'],'per_site':per})
    json.dump(out, open(os.path.join(ROOT,'tools/backlog_triage.json'),'w'), indent=1)
    agg=collections.Counter(); wsites=collections.Counter()
    for o in out:
        agg[o['top']]+=1; wsites[o['top']]+=o['sites']
    print('open pairs classified: %d (of %d; rest have no direct call sites)'%(len(out),len(openp)))
    print('%-10s %6s %8s'%('BUCKET','PAIRS','SITES'))
    for k,v in agg.most_common():
        print('%-10s %6d %8d'%(k,v,wsites[k]))

if __name__=='__main__':
    main()
