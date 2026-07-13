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
 * Left unfixed: this is the project's hottest render primitive, ~179 call
 * sites across 43 files. Every single call site currently invokes
 * FindSpriteFrame() with zero arguments and is itself an independent,
 * unfixed dropped-register-argument stub (e.g. DrawSprite.c/BlitSprite16bpp.c
 * read their own in_EAX/unaff_ESI locals with no real parameters of their
 * own yet) - promoting this function's signature would require its own
 * disassembly-based register recovery in all 43 callers to keep behavior
 * correct, which is a separate, much larger undertaking outside this pass's
 * scope. The current in_EAX/param_2/unaff_ESI reads below are confirmed
 * correct against the disassembly, so behavior is preserved as-is; only
 * promote the signature once the caller fan-out can be fixed in the same
 * pass (see src/README.md's "Raw/verbatim ports" section).
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

