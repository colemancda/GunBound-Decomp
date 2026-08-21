/* FUN_004ac260 - 0x004ac260 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard flip prep): both guard cells
 * recovered.  The first peek (0x4ac2aa) reads the return value of the
 * EncodeChecksumDeltaSub above it -- the delta helpers RETURN THEIR SECOND
 * ARGUMENT, so the cell is this function's own stack scratch, local_230.
 * Its RESULT was discarded by Ghidra but the original scales it by 0x224
 * (`imul eax,eax,0x224`) to index the six-cell guard table at 0xe9da08,
 * which is the second peek's cell -- so it is captured here into uIndex.
 * That table had no declaration in the tree until now; it is defined in
 * globals_sized.c as 6 * 0x224 bytes (the four sibling tables are 0xcd8
 * apart, which is exactly six cells).
 */
#include "ghidra_types.h"


undefined4 __fastcall FUN_004ac260(int param_1)

{
  undefined4 uVar1;
  uint uIndex;
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_238 [8];
  undefined1 local_230 [548];
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053df6b;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  EncodeChecksumDeltaSub(param_1 + 0x4c,local_230,1);
  local_4 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uIndex = PeekPacketChecksumState((void *)(local_230));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState((void *)(&DAT_00e9da08 + uIndex * 0x224));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = 0xffffffff;
  if ((*(int *)(local_230 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(local_230 + 0x14),&DAT_0079376c);
    TreeLowerBound(local_238,&DAT_00793770);
  }
  *unaff_FS_OFFSET = local_c;
  return uVar1;
}

