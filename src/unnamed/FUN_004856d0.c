/* FUN_004856d0 - 0x004856d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * FUN_004856d0(undefined4 *param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053c218;
  *unaff_FS_OFFSET = &local_c;
  InitProjectile(param_1,0x186a2);
  local_4 = 0;
  *param_1 = &PTR_FUN_0055620c;
  *(undefined1 *)(param_1 + 0x1071) = 0;
  param_1[0xfee] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4856fd
   * (`lea edi,[esi+0x3fa4]`, esi = this file's own param_1) a CValueGuard
   * cell at param_1+0x3fa4; tableHandle(+0x14) = param_1+0x3fb8 =
   * param_1[0xfee] (undefined4 units), matching the zero-write above.
   * Same pattern as FUN_0049e540.c (both CProjectile-subtype
   * constructors). See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)param_1 + 0x3fa4, 0);
  *(undefined1 *)(param_1 + 0xfe8) = 0;
  param_1[0xfe7] = 0xffffffff;
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

