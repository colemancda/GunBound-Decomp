/* FindSpriteFrame - 0x004f30c0 in the original binary.
 *
 * Loaded-sprite/frame resolver for the software blitter (the project's
 * hottest render primitive - ~181 call sites across 43 files, and the thing
 * loosely called "the texture-cache lookup" elsewhere in the docs). It is a
 * two-level keyed lookup over a nested linked-list resource container:
 *   - outer list: nodes chained via +0x1c, keyed at +4 (the resource/image
 *     group); walked until the key matches, bailing out (return 0) once the
 *     list passes the requested key.
 *   - inner list: from the matched outer node's +0x10, nodes chained via +0x10
 *     and keyed at +8 (the frame/sub index); returns the matching frame node.
 * Returns the frame record, or 0 if either key isn't found.
 *
 * DROPPED REGISTER ARGUMENTS (pattern #1) - investigated, NOT fixed here:
 * Ghidra's signature - __fastcall(param_1, param_2) - is incomplete.
 * Disassembly at the real entry (objdump -Mintel --start-address=0x4f30c0
 * --stop-address=0x4f30f5) shows the three real inputs are EAX=container,
 * EDX=outer key (Ghidra's param_2 - that part happened to be right), and
 * ESI=inner key, e.g.:
 *     mov ecx,[eax+0x4]   ; container read straight from EAX; ecx is pure
 *                         ; scratch (written before ever being read)
 *     ...
 *     cmp ecx,edx         ; outer key compared against EDX
 *     ...
 *     cmp ecx,esi         ; inner key compared against ESI
 * Cross-checked against two call sites' disassembly (DrawSprite.c @0x4eb890,
 * DrawButtonWidget.c @0x405ea0): both load EAX with the same fixed global
 * (0xea0e18, i.e. &DAT_00ea0e18, the sprite registry already referenced by
 * that name elsewhere in src/rendering/LoadAvatarSprites.c etc.) and set up
 * EDX/ESI from their own locals immediately before `call 0x4f30c0` - matching
 * this function's in_EAX/param_2/unaff_ESI reads exactly.
 *
 * Caller fan-out: this is the project's hottest render primitive, ~181 call
 * sites across 57 caller functions in ~43 files. Every call site still
 * invokes FindSpriteFrame() with zero arguments and is itself an independent,
 * unfixed dropped-register-argument stub (e.g. DrawSprite.c/BlitSprite16bpp.c
 * read their own in_EAX/unaff_ESI locals with no real parameters of their own
 * yet), so each one still needs its own disassembly-based register recovery.
 *
 * 2026-07-13 angr batch-scan: ran an angr CFG backward-scan + whole-function
 * backward register-taint (tools/scan_findspriteframe.py,
 * tools/scan_findspriteframe2.py) over all 181 call sites; results cached
 * in tools/findspriteframe_sites.json. Findings:
 *   - EAX (container) fully resolved at 179/181 sites: 168 use the fixed
 *     literal &DAT_00ea0e18 (confirming the 2-site spot-check above), 8 use
 *     g_clientContext (DAT_005b3484's value, not its address), 2 use a
 *     caller's own existing parameter (FUN_0040d020's `param_2`/EBP). Only
 *     2 sites (inside FUN_004cee30) need a one-more-step trace (`add
 *     eax,0x6a7f88` off an unresolved base).
 *   - ESI (inner key) resolved at 153/181 sites as either a literal or a
 *     caller-local already visible in that file's own decompiled source
 *     (e.g. `movzx esi,word ptr [ebp+0x23344]`, `add esi,0xa` off an
 *     existing loop index) - these map directly onto locals the ported C
 *     already declares. 28 sites remain genuinely per-call-site work.
 *   - Decompiling several of the larger caller functions (e.g.
 *     State09_ReadyRoom_RenderRosterAndItems, State09_ReadyRoom_
 *     RenderStatusOverlay - each 100-250+ lines with a dozen+ FindSpriteFrame
 *     call sites) confirms the SAME callers independently drop arguments to
 *     BlitSprite16bpp/BlitSpriteClipped/DrawFontString/BlitRLESprite too -
 *     this is not a single-function fix, it's a whole render-call-chain
 *     family fix, same class as this file's own header already flagged for
 *     BlitSpriteText.c/DrawFontString.c/BlitSprite16bpp.c. The cached JSON is
 *     the expensive part (CFG construction + backward taint over a ~1.3MB
 *     binary) and should let a dedicated follow-up skip straight to the
 *     file-by-file fixes.
 *
 * FIXED (2026-07-13): promoted to real explicit parameters
 * (container, outerKey, innerKey) so the render path can actually call it.
 * Declared plain __cdecl (all args stack-passed) rather than __fastcall,
 * deliberately: __fastcall's symbol decoration counts STACK-passed bytes
 * (@FindSpriteFrame@N), so adding params would rename the symbol and break
 * every not-yet-fixed caller at link time. __cdecl keeps the symbol as
 * _FindSpriteFrame and, with functions.h's K&R-empty declaration, lets the
 * ~175 still-argless call sites keep compiling unchanged - they read garbage
 * off the stack exactly as they already read garbage off registers today,
 * so this is strictly no worse for them and unblocks the callers that ARE
 * fixed. This is why the promotion is NOT all-or-nothing across the caller
 * fan-out: a partial promotion is safe, so callers can be recovered
 * incrementally as each render path is brought up. This also matches
 * src/cxx/State03_GameRoomList.cpp's own existing `extern int
 * FindSpriteFrame(void)` (plain cdecl) declaration.
 *
 * CALLER SWEEP (2026-08-20): 42 of the 150 argless call sites recovered,
 * in two rounds of 34 and 8; 108 remain.
 *
 * COUNT CORRECTION: round 1's commit message said "162 argless, leaving 128".
 * Both figures were inflated - they came from a plain grep for
 * "FindSpriteFrame()", which also counts the prose in headers like this one,
 * including my own. Counting only code (comments stripped) the real
 * progression is 150 -> 116 -> 108. All 181 direct call sites were re-scanned from the binary
 * (byte-scan for E8 rel32 targeting 0x4f30c0; results cached in
 * tools/findspriteframe_regs.json, which supersedes the older angr-derived
 * findspriteframe_sites.json for EDX - that one carried EAX and ESI only).
 * The register picture is much more uniform than expected:
 *     EAX  0xea0e18 at 168 of 181 - the sprite registry, as the 2-site
 *          spot-check above had already suggested
 *     EDX  a literal at 164 of 181
 *     ESI  a literal or xor-zero at roughly half; the rest come from a
 *          caller local and still need per-site recovery
 *
 * THE TRAP, and why this is not a bulk sed: VA ORDER IS NOT SOURCE ORDER.
 * Pairing the Nth call in the binary with the Nth FindSpriteFrame() in the
 * file is wrong often enough to matter, and it fails silently.
 *
 * What makes it checkable is that ESI - the frame index - is ALSO passed to
 * the BlitSpriteClipped call inside the same block, where Ghidra DID model it
 * as an argument. So `BlitSpriteClipped(<n>)` a few lines below a
 * FindSpriteFrame() is an independent witness for that site's ESI, and any
 * pairing can be tested rather than trusted. Watch two things when using it:
 * Ghidra prints values >= 10 in hex, so a decimal-only regex silently reports
 * "no witness" for exactly the sites you most want checked; and
 * BlitSprite16bpp's first argument is an X coordinate, NOT the frame - only
 * BlitSpriteClipped's is.
 *
 * Applied in round 1 to the two files where the witness agreed on every
 * site: FUN_0050ae40.c and FUN_0050be20.c, 17 of 17 each, zero mismatches.
 *
 * ROUND 2 replaced position-matching with a CALL-SEQUENCE FINGERPRINT: from
 * each call site, the next three call targets in the binary (resolved to
 * names through PROGRESS.csv) versus the next three function calls in the
 * source block. Grouping both sides by that fingerprint and pairing within
 * each group is order-independent, so it survives the block reordering that
 * defeats position-matching. Where the ESI witness was also present it agreed
 * every time, with zero contradictions across all files - the two methods are
 * independent, so that is a real cross-check rather than a restatement.
 * It added 8 sites: State09_ReadyRoom_RenderStatusOverlay.c (7, by
 * fingerprint, 6 witness agreements) and DarkenTerrainScorchRow.c (1, the
 * only site in its file and therefore unambiguous).
 *
 * ROUND 3 (2026-08-20) came from the opposite direction and needed no
 * disassembly. Once BlitSpriteClipped's own call sites carry (frame, x, y,
 * outerKey), a completed sibling in the same block states this call's two
 * arguments outright: the outerKey is the same key, and the frame is the very
 * frame the block looks up before blitting it. 18 more sites - including all
 * 10 in FUN_0044a000.c, the file whose block reordering defeated
 * position-matching in round 1 and which I had held back rather than guess.
 *
 * Cross-checked against the independent binary scan: every (outerKey, frame)
 * pair derived this way in FUN_0044a000.c appears in the literal EDX/ESI
 * pairs scanned from that function, with no pair appearing in the source that
 * the binary does not use. The two routes - source-level via the sibling, and
 * disassembly via the registers - agree completely.
 *
 * 101 of 192 call sites now carry their arguments. THE TWO FUNCTIONS UNLOCK
 * EACH OTHER, so the productive loop is: recover BlitSpriteClipped where its
 * block's lookup is known, then recover lookups where their block's blit is
 * known, and repeat.
 *
 * WHAT ACTUALLY BLOCKS THE REST: not the pairing problem at all. Of the 27
 * files still holding argless calls, most fail on 'register not literal' -
 * their ESI, and sometimes EDX, comes from a caller local rather than an
 * immediate. Those need the same caller-side dropped-register recovery one
 * level up, which is why the render primitives (BlitSprite16bpp,
 * BlitSpriteClipped, QueueSpriteFrameSpans, Widget_DrawSelf) are all in the
 * held list: they are themselves stubs waiting on their own callers.
 *
 * Held back, with the evidence, for a follow-up:
 *   - FUN_0044a000.c (26 sites) is the proof that the trap is real. Its
 *     witnesses run 13,12,15,14,17,16,19,18,21,20 against a binary that runs
 *     11..20 in VA order. The transformation is systematic - each if/else
 *     pair is emitted in the opposite order from the code layout - and it
 *     accounts for 23 of the 26, but three sites (ESI 11, 22, 23) cannot be
 *     placed without reading the blocks, so none of it was applied.
 *   - State11_InBattle_RenderHud.c (18) and the other 32 files hold sites
 *     whose ESI comes from a caller local, which is the same
 *     dropped-register recovery this file's header describes for
 *     BlitSpriteText/DrawFontString/BlitSprite16bpp - a caller-side job, not
 *     a callee-side one.
 *
 * Not renamed in-tree yet: a rename would touch all 43 caller files.
 * Raw/near-verbatim port of Ghidra's decompiler output, not hand-verified.
 * See src/README.md's "Raw/verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FindSpriteFrame(int container,uint outerKey,uint innerKey)

{
  uint uVar1;
  int in_EAX = container;
  uint param_2 = outerKey;
  int iVar2;
  uint unaff_ESI = innerKey;

  iVar2 = *(int *)(*(int *)(in_EAX + 4) + 0x1c);
  uVar1 = *(uint *)(iVar2 + 4);
  if (uVar1 <= param_2) {
    while (uVar1 != param_2) {
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar1 = *(uint *)(iVar2 + 4);
      if (param_2 < uVar1) {
        return 0;
      }
    }
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar1 = *(uint *)(iVar2 + 8);
    while (uVar1 <= unaff_ESI) {
      if (uVar1 == unaff_ESI) {
        return iVar2;
      }
      iVar2 = *(int *)(iVar2 + 0x10);
      uVar1 = *(uint *)(iVar2 + 8);
    }
  }
  return 0;
}

