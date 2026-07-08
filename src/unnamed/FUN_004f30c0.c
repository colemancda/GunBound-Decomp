/* FUN_004f30c0 - 0x004f30c0 in the original binary.
 *
 * Loaded-sprite/frame resolver for the software blitter (the project's
 * hottest render primitive - 173 call sites across 43 files, and the thing
 * loosely called "the texture-cache lookup" elsewhere in the docs). It is a
 * two-level keyed lookup over a nested linked-list resource container:
 *   - outer list: nodes chained via +0x1c, keyed at +4 (the resource/image
 *     group); walked until the key matches, bailing out (return 0) once the
 *     list passes the requested key.
 *   - inner list: from the matched outer node's +0x10, nodes chained via +0x10
 *     and keyed at +8 (the frame/sub index); returns the matching frame node.
 * Returns the frame record, or 0 if either key isn't found.
 *
 * The container and both keys arrive in registers (EAX = container, plus the
 * outer/inner keys), so Ghidra's __fastcall(param_1, param_2) signature is
 * incomplete - the real inputs aren't all visible here. Typical caller: a
 * draw routine reads the widget/object's frame index (e.g. ButtonWidget +0x30)
 * and calls this; on a hit it inspects the record's +0x18 flag to pick the
 * blit path - +0x18==1 -> BlitSprite16bpp (full), else BlitSpriteClipped. A
 * few callers use the returned record without drawing (e.g. to read a frame's
 * bounds), but the dominant use is "resolve the sprite frame to blit."
 *
 * Not renamed in-tree yet: a rename would touch all 43 caller files.
 * Raw/near-verbatim port of Ghidra's decompiler output, not hand-verified.
 * See src/README.md's "Raw/verbatim ports" section for status.
 */
#include "ghidra_types.h"


int __fastcall FUN_004f30c0(undefined4 param_1,uint param_2)

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

