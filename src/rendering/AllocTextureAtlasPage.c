/* AllocTextureAtlasPage - 0x004f4350 in the original binary.
 *
 * Allocates a 0x118-byte texture-atlas page node (operator_new) and
 * links it onto the texture cache's page list (head/tail at
 * cache+0x114/+0x118). NAMED (2026-07-18); called by PreloadTexture.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-ESI + DROPPED-RETURN FIX (2026-08-06), two bugs (orig
 * 0x4f4350-0x4f439e):
 *   - The cache arrives in ESI (`mov esi,ebp` at the PreloadTexture call
 *     site 0x4f4481, ebp = its param_1) and was read here as an
 *     uninitialised `unaff_ESI`, so the new page was linked onto a wild
 *     list - live fault reading [0+0x118].
 *   - The original RETURNS the new page in EAX: both `ret` paths leave
 *     EAX holding the operator_new result (or 0 on failure), and the
 *     caller does `mov esi,eax` right after to use it. This port
 *     returned a literal 0 on both paths, with a comment claiming the
 *     result was unused by callers - that was wrong, PreloadTexture
 *     assigns it straight into its page variable.
 */
#include "ghidra_types.h"


undefined4 AllocTextureAtlasPage(int cache)

{
  undefined1 *puVar1;
  int unaff_ESI = cache;
  
  puVar1 = operator_new(0x118);
  if (puVar1 == (undefined1 *)0x0) {
    puVar1 = (undefined1 *)0x0;
  }
  else {
    *puVar1 = 0;
    *(undefined4 *)(puVar1 + 0x110) = 0;
  }
  if (*(int *)(unaff_ESI + 0x118) == 0) {
    *(undefined1 **)(unaff_ESI + 0x114) = puVar1;
    *(undefined4 *)(puVar1 + 0x114) = 0;
    *(undefined1 **)(unaff_ESI + 0x118) = puVar1;
    return (undefined4)puVar1;   /* EAX = the new page */
  }
  *(undefined1 **)(*(int *)(unaff_ESI + 0x118) + 0x114) = puVar1;
  *(undefined4 *)(puVar1 + 0x114) = 0;
  *(undefined1 **)(unaff_ESI + 0x118) = puVar1;
  return (undefined4)puVar1;     /* EAX = the new page */
}

