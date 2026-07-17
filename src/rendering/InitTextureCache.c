/* InitTextureCache - 0x004f42b0 in the original binary.
 *
 * NAMED (2026-07-16): the named-texture-cache constructor - zeroes the
 * name string at +0, the parent D3D interface slot +0x110, the loaded-
 * texture list head/tail +0x114/+0x118, the name-record list +0x1b4,
 * the count +0x401b8 and the 15-entry table +0x401bc. Called from the
 * CRT static-initializer 0x5429b0 with EDX = &g_textureCache (was
 * DAT_00eb1bd8) to construct the singleton; paired with
 * DestroyTextureCache via atexit. See FlushTextureCache.c's header for
 * the family/identity evidence. The cache object is 0x40200 bytes -
 * see globals_sized.c.
 */
#include "ghidra_types.h"


undefined1 * __fastcall InitTextureCache(undefined4 param_1,undefined1 *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  *param_2 = 0;
  *(undefined4 *)(param_2 + 0x110) = 0;
  *(undefined4 *)(param_2 + 0x114) = 0;
  *(undefined4 *)(param_2 + 0x118) = 0;
  *(undefined4 *)(param_2 + 0x1b4) = 0;
  *(undefined4 *)(param_2 + 0x401b8) = 0;
  puVar2 = (undefined4 *)(param_2 + 0x401bc);
  for (iVar1 = 0xf; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  return param_2;
}

