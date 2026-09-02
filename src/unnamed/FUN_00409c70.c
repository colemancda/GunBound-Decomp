/* FUN_00409c70 - 0x00409c70 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * PROMOTED (2026-09-01): was `(void)` but the original is `ret 4` with one
 * stack param (the hash table - EAX=[esp+0x10]=entry+4 at 0x409c78 feeds
 * FUN_00426780's table register) plus EBX live-in (the key string). The
 * interior FUN_00426780 call gains both as its promoted trailing args.
 */
#include "ghidra_types.h"


undefined4 FUN_00409c70(int *param_1,uchar *regEbx)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0x00000004;
  int iVar1;
  undefined1 local_8 [4];
  undefined1 local_4 [4];
  
  iVar1 = FUN_00426780(local_4,local_8,&stack0x00000004,param_1,regEbx);
  if (iVar1 != 0) {
    return *(undefined4 *)(iVar1 + 4);
  }
  return 0xffffffff;
}

