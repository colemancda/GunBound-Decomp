#!/usr/bin/env python3
"""Apply CONFIRMED dropped-register proposals produced by the analysis workflow.

Input: a JSON list of {proposal, verdict} records.  For each record whose
verdict is CONFIRMED overall and whose proposal resolves EVERY site:
  * promote the callee's Ghidra local (in_EAX / unaff_ESI / ...) to a trailing
    parameter regEax / regEsi / ...
  * at every call site, insert the site's expression as the LAST argument --
    but ONLY if the site currently passes exactly the declared number of
    arguments.  A short call site means the fix is a re-slot, which this tool
    refuses to guess at; such functions are reported and skipped whole.
  * give functions.h a real prototype (and any private prototype in a .cpp)

It edits nothing for a function unless every one of its sites can be applied,
because a function with some sites filled and some not is worse than one with
none: the real prototype then rejects the short sites, or the K&R one accepts
them silently.

The compile and promoted_arity_audit are NOT run here -- the caller does that
and commits only on a clean result.
"""
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
import callsites

REGP = {'eax': 'regEax', 'ebx': 'regEbx', 'ecx': 'regEcx', 'edx': 'regEdx',
        'esi': 'regEsi', 'edi': 'regEdi', 'ebp': 'regEbp'}
LOCALS = {'eax': ['in_EAX', 'unaff_EAX', 'extraout_EAX'], 'ebx': ['unaff_EBX', 'in_EBX'],
          'ecx': ['unaff_ECX', 'in_ECX'], 'edx': ['unaff_EDX', 'in_EDX'],
          'esi': ['unaff_ESI', 'in_ESI'], 'edi': ['unaff_EDI', 'in_EDI'], 'ebp': ['unaff_EBP']}


def find_def_file(func):
    for b, _, fs in os.walk(os.path.join(ROOT, 'src')):
        for f in fs:
            if f in (func + '.c', func + '.cpp'):
                return os.path.join(b, f)
    return None


def arity(argstr):
    a = callsites.split_args(argstr)
    return 0 if (not a or (len(a) == 1 and a[0].strip() in ('void', ''))) else len(a)


def apply_one(rec, dry):
    p = rec['proposal']
    func, reg = p['func'], p['reg']
    log = []
    if rec['verdict']['overall'] != 'CONFIRMED' or not p.get('all_resolved'):
        return False, ['%s/%s: not confirmed' % (func, reg)]
    if p.get('is_argument') == 'PHANTOM':
        return False, ['%s/%s: phantom -- nothing to promote' % (func, reg)]
    if any(s['confidence'] != 'CERTAIN' or s['expr'] == 'UNRESOLVED' for s in p['sites']):
        return False, ['%s/%s: a site is not CERTAIN' % (func, reg)]
    # An analyst sometimes writes the expression as PROSE -- "iVar1 (the
    # CURRENT list node, i.e. ...)" -- and a text applier would paste that
    # into a call.  Accept only something that parses as a C expression.
    for s in p['sites']:
        e = s['expr']
        if len(e) > 90 or re.search(r'\b(the|i\.e|currently|own|before|after|which)\b', e) \
                or re.search(r'[A-Za-z]\s+[A-Za-z]', re.sub(r'\(\s*[A-Za-z_][\w ]*\*?\s*\)', '', e)):
            return False, ['%s/%s: expr is prose, not C: %r' % (func, reg, e[:70])]
    dp = find_def_file(func)
    if not dp:
        return False, ['%s: definition file not found' % func]
    src = open(dp, errors='replace').read()
    local = None
    for cand in LOCALS[reg]:
        m = re.search(r'^[ \t]*([A-Za-z_][A-Za-z0-9_ ]*?[ \t*]+)%s[ \t]*;[ \t]*\n' % cand, src, re.M)
        if m:
            local, decl = cand, m
            break
    if not local:
        return False, ['%s/%s: no open local (already done?)' % (func, reg)]
    ctype = decl.group(1).strip()
    pname = REGP[reg]
    new = src[:decl.start()] + src[decl.end():]
    d = [c for c in callsites.find(new, func, callsites.blank_comments(new)) if c['kind'] == 'definition']
    if len(d) != 1:
        return False, ['%s: %d definitions found' % (func, len(d))]
    args = new[d[0]['open']:d[0]['close']]
    declared = arity(args)
    ptype = ctype if ctype.endswith('*') else ctype + ' '
    newargs = ptype + pname if args.strip() in ('', 'void') else args.rstrip() + ',' + ptype + pname
    new = new[:d[0]['open']] + newargs + new[d[0]['close']:]
    new = re.sub(r'\b%s\b' % local, pname, new)
    files = {dp: new}

    # gather every source call site tree-wide and match to proposal sites by file
    by_file = {}
    for s in p['sites']:
        by_file.setdefault(s.get('caller_file', ''), []).append(s)
    total_sites = 0
    for b, _, fs in os.walk(os.path.join(ROOT, 'src')):
        for f in fs:
            if not f.endswith(('.c', '.cpp')):
                continue
            fp = os.path.join(b, f)
            t = files.get(fp) or open(fp, errors='replace').read()
            if re.search(r'\b%s\s*\(' % func, t) is None:
                continue
            bl = callsites.blank_comments(t)
            cs = [c for c in callsites.find(t, func, bl) if c['kind'] == 'call']
            if not cs:
                continue
            rel = os.path.relpath(fp, ROOT)
            props = [s for s in p['sites'] if s.get('caller_file', '').endswith(rel) or rel.endswith(s.get('caller_file', '\x00'))]
            if len(props) != len(cs):
                return False, ['%s/%s: %s has %d call sites but proposal covers %d'
                               % (func, reg, rel, len(cs), len(props))]
            # order: by source_line if given, else require a single site
            if len(cs) > 1:
                if any(not s.get('source_line') for s in props):
                    return False, ['%s/%s: %s has %d sites and the proposal does not give source lines'
                                   % (func, reg, rel, len(cs))]
                props = sorted(props, key=lambda s: s['source_line'])
            for c, s in zip(sorted(cs, key=lambda x: x['start']), props):
                line = t[:c['start']].count('\n') + 1
                if s.get('source_line') and abs(s['source_line'] - line) > 3:
                    return False, ['%s/%s: %s site at line %d but proposal says %d'
                                   % (func, reg, rel, line, s['source_line'])]
                have = arity(t[c['open']:c['close']])
                if have != declared and not s.get('full_args'):
                    return False, ['%s/%s: %s:%d passes %d args for %d declared -- re-slot needed'
                                   % (func, reg, rel, line, have, declared)]
                if s.get('full_args'):
                    # A re-slot: the analyst supplied the COMPLETE argument list
                    # (declared slots in order, recovered register last).  It
                    # must contain exactly declared+1 expressions, none prose.
                    fa = callsites.split_args(s['full_args'])
                    if len(fa) != declared + 1:
                        return False, ['%s/%s: %s:%d full_args has %d slots, need %d'
                                       % (func, reg, rel, line, len(fa), declared + 1)]
                    for e in fa:
                        if re.search(r'\b(the|i\.e|currently|own|before|after|which)\b', e):
                            return False, ['%s/%s: full_args slot is prose: %r' % (func, reg, e[:60])]
                    if fa[-1].strip() != s['expr'].strip():
                        return False, ['%s/%s: full_args last slot %r != expr %r'
                                       % (func, reg, fa[-1][:40], s['expr'][:40])]
            # apply from the end so offsets stay valid
            for c, s in sorted(zip(sorted(cs, key=lambda x: x['start']), props), key=lambda z: -z[0]['start']):
                inner = t[c['open']:c['close']]
                if s.get('full_args') and arity(inner) != declared:
                    repl = s['full_args'].strip()            # whole-list rewrite
                else:
                    repl = s['expr'] if inner.strip() == '' else inner.rstrip() + ',' + s['expr']
                t = t[:c['open']] + repl + t[c['close']:]
                total_sites += 1
            files[fp] = t
    if total_sites != len(p['sites']):
        return False, ['%s/%s: proposal has %d sites, source has %d' % (func, reg, len(p['sites']), total_sites)]
    # prototypes
    hp = os.path.join(ROOT, 'include/functions.h')
    h = files.get(hp) or open(hp, errors='replace').read()
    hb = callsites.blank_comments(h)
    decls = [c for c in callsites.find(h, func, hb) if c['kind'] == 'declaration']
    for c in sorted(decls, key=lambda x: -x['start']):
        h = h[:c['open']] + newargs + h[c['close']:]
    if not decls:
        h = h.replace('void FUN_00543210(void);', '%s %s(%s);\n\nvoid FUN_00543210(void);'
                      % (re.search(r'^([^\n]*?)\b%s\s*\(' % func, new, re.M).group(1).strip().replace('__thiscall', '').replace('__fastcall', '').strip() or 'void', func, newargs), 1)
    files[hp] = h
    for b, _, fs in os.walk(os.path.join(ROOT, 'src')):
        for f in fs:
            if not f.endswith('.cpp'):
                continue
            fp = os.path.join(b, f)
            t = files.get(fp) or open(fp, errors='replace').read()
            bl = callsites.blank_comments(t)
            ds = [c for c in callsites.find(t, func, bl) if c['kind'] == 'declaration']
            if not ds:
                continue
            for c in sorted(ds, key=lambda x: -x['start']):
                t = t[:c['open']] + newargs + t[c['close']:]
            files[fp] = t
            log.append('  private prototype updated: %s' % os.path.relpath(fp, ROOT))
    if not dry:
        for fp, t in files.items():
            open(fp, 'w').write(t)
    log.insert(0, '%-26s %s  %d sites  (%s)' % (func, reg, total_sites, ', '.join(sorted({s['expr'] for s in p['sites']}))[:80]))
    return True, log, sorted(os.path.relpath(f, ROOT) for f in files)


def main():
    dry = '--apply' not in sys.argv
    recs = json.load(open([a for a in sys.argv[1:] if a != '--apply'][0]))
    touched, skipped, n = set(), [], 0
    for r in recs:
        res = apply_one(r, dry)
        if res[0]:
            n += 1
            for l in res[1]:
                print(l)
            touched.update(res[2])
        else:
            skipped.extend(res[1])
    print('\n%s: %d functions, %d files' % ('APPLIED' if not dry else 'DRY RUN', n, len(touched)))
    for s in skipped:
        print('  SKIP ' + s)
    if not dry:
        open('/tmp/proposals_touched.txt', 'w').write('\n'.join(sorted(touched)) + '\n')


if __name__ == '__main__':
    main()
