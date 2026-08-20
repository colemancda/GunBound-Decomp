"""Fill in render-call arguments from the other calls in the SAME block.

A render block is

    if (FindSpriteFrame(ctx, KEY, FRAME)) {
      if (rec->flags == 1) BlitSprite16bpp(FRAME, x, y, KEY);
      else                 BlitSpriteClipped(FRAME, x, y, KEY);
    }

so all three calls share FRAME and KEY and the two blits share x and y.
Whatever one of them already carries, the others can be filled from - no
call-site-to-source pairing, no disassembly, and immune to the block
reordering that defeats position matching.

THE BLOCK IS DELIMITED BY BRACES, NOT BY A CHARACTER WINDOW. An earlier
version used a 600-character window and spilled into neighbouring blocks,
producing values that were confident, compiling and wrong - it claimed one
frame three times in State10_Loading_Render where the binary uses it once.
Comments are masked out for the same class of reason: scanning raw source
rewrites the example code inside header comments, including the paragraphs
documenting these sweeps.

Three further guards, each of which exists because its absence is unsafe:
blocks longer than 1200 characters are not leaf render blocks; a block
containing a nested FindSpriteFrame is ambiguous about which lookup owns
which blit; and x/y are only taken from a completed sibling INSIDE the same
block.

Run tools/render_args_audit.py afterwards - it checks the result against the
registers scanned from the original, which is evidence this script never
sees.
"""
import glob,re,sys
def comment_mask(src):
    mask=bytearray(len(src))
    for m in re.finditer(r'/\*.*?\*/',src,re.S): mask[m.start():m.end()]=b'\1'*(m.end()-m.start())
    for m in re.finditer(r'//[^\n]*',src): mask[m.start():m.end()]=b'\1'*(m.end()-m.start())
    return mask
def split_top(s):
    out=[];d=0;cur=''
    for ch in s:
        if ch=='(':d+=1
        elif ch==')':d-=1
        if ch==',' and d==0: out.append(cur.strip()); cur=''
        else: cur+=ch
    if cur.strip() or out: out.append(cur.strip())
    return [a for a in out if a]
def call_at(src,start):
    i=src.index('(',start); d=1; j=i+1
    while d and j<len(src):
        if src[j]=='(':d+=1
        elif src[j]==')':d-=1
        j+=1
    return i+1,j-1
def brace_block(src,frm):
    """span of the { ... } that follows position frm"""
    i=src.find('{',frm)
    if i<0: return None
    d=1; j=i+1
    while d and j<len(src):
        if src[j]=='{':d+=1
        elif src[j]=='}':d-=1
        j+=1
    return (i,j) if d==0 else None
def run(src):
    mask=comment_mask(src); edits=[]
    for m in re.finditer(r'\bFindSpriteFrame\s*\(',src):
        if mask[m.start()]: continue
        a0,a1=call_at(src,m.start())
        if src[a1+1:].lstrip().startswith('{'): continue          # definition
        args=split_top(src[a0:a1])
        if len(args)!=3: continue                                  # need it recovered
        KEY,FRAME=args[1],args[2]
        blk=brace_block(src,a1)
        if not blk: continue
        b0,b1=blk
        if b1-b0>1200: continue                                    # not a leaf render block
        body=src[b0:b1]
        if 'FindSpriteFrame' in body: continue                     # nested lookup: ambiguous
        for nm in ('BlitSprite16bpp','BlitSpriteClipped'):
            for bm in re.finditer(r'\b%s\s*\('%nm,body):
                gs=b0+bm.start()
                if mask[gs]: continue
                c0,c1=call_at(src,gs)
                ba=split_top(src[c0:c1])
                if len(ba)==4: continue
                # x and y must come from a completed sibling in the SAME block
                X=Y=None
                for om in re.finditer(r'\b(BlitSprite16bpp|BlitSpriteClipped)\s*\(',body):
                    os_=b0+om.start()
                    if mask[os_] or os_==gs: continue
                    o0,o1=call_at(src,os_)
                    oa=split_top(src[o0:o1])
                    if len(oa)==4: X,Y=oa[1],oa[2]; break
                if len(ba)==2: x,y=ba[0],ba[1]
                elif X and Y: x,y=X,Y
                else: continue
                edits.append((gs,c1+1,'%s(%s,%s,%s,%s)'%(nm,FRAME,x,y,KEY)))
    for s0,s1,new in sorted(edits,reverse=True): src=src[:s0]+new+src[s1:]
    return src,len(edits)
total=0
for p in sorted(glob.glob('src/**/*.c',recursive=True)):
    src=open(p,errors='replace').read()
    if 'FindSpriteFrame' not in src: continue
    new,n=run(src)
    if n: open(p,'w').write(new); total+=n; print('  %-52s %d'%(p,n))
print('applied',total)
