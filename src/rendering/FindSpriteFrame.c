/* FindSpriteFrame - 0x004f30c0 in the original binary.
 *
 * Loaded-sprite/frame resolver for the software blitter (the project's
 * hottest render primitive - ~179 call sites across 43 files, and the thing
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
 * Left unfixed: this is the project's hottest render primitive, ~181 call
 * sites across 57 caller functions in ~43 files. Every single call site
 * currently invokes FindSpriteFrame() with zero arguments and is itself an
 * independent, unfixed dropped-register-argument stub (e.g. DrawSprite.c/
 * BlitSprite16bpp.c read their own in_EAX/unaff_ESI locals with no real
 * parameters of their own yet) - promoting this function's signature would
 * require its own disassembly-based register recovery in all 43 callers to
 * keep behavior correct, which is a separate, much larger undertaking
 * outside this pass's scope.
 *
 * 2026-07-13 angr batch-scan update: ran an angr CFG backward-scan +
 * whole-function backward register-taint (tools/scan_findspriteframe.py,
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
 *   - Crucially, decompiling several of the larger caller functions (e.g.
 *     State09_ReadyRoom_RenderRosterAndItems, State09_ReadyRoom_
 *     RenderStatusOverlay - each 100-250+ lines with a dozen+ FindSpriteFrame
 *     call sites) confirms the SAME callers independently drop arguments to
 *     BlitSprite16bpp/BlitSpriteClipped/DrawFontString/BlitRLESprite too -
 *     this is not a single-function fix, it's a whole render-call-chain
 *     family fix, same class as this file's own header already flagged for
 *     BlitSpriteText.c/DrawFontString.c/BlitSprite16bpp.c. Promoting
 *     FindSpriteFrame's signature is all-or-nothing across every caller (a
 *     partial promotion breaks every not-yet-fixed call site's compile) -
 *     not attempted in this pass. The cached JSON is the expensive part
 *     (CFG construction + backward taint over a ~1.3MB binary) and should
 *     let a dedicated follow-up skip straight to the file-by-file fixes.
 *
 * Not renamed in-tree yet: a rename would touch all 43 caller files.
 * Raw/near-verbatim port of Ghidra's decompiler output, not hand-verified.
 * See src/README.md's "Raw/verbatim ports" section for status.
 */
#include "ghidra_types.h"


int __fastcall FindSpriteFrame(undefined4 param_1,uint param_2)

{
  uint uVar1;
  int in_EAX;
  int iVar2;
  uint unaff_ESI;

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

