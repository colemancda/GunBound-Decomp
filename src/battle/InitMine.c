/* InitMine - 0x004977c0 in the original binary.
 *
 * NAMED 2026-08-19 (was FUN_004977c0).  Constructor for the MINE entity -
 * the sole class-100003 constructor in the binary.  It delegates to
 * InitProjectile(param_1, 0x186a3), which stamps the class id at object +0x4
 * and lays out the shared CValueGuard block at +0x40, +0x264, +0x488, ...
 * (0x224 stride), then installs vtable 0x5563f0 and zeroes its own cells at
 * +0x3fd4 / +0x41f8.  Callers: SpawnMine and SpawnSuperMine.
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


undefined4 * InitMine(undefined4 *param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053c0f8;
  *unaff_FS_OFFSET = &local_c;
  InitProjectile(param_1,0x186a3);
  local_4 = 0;
  *param_1 = &PTR_FUN_005563f0;
  *(undefined1 *)(param_1 + 0x107d) = 0;
  param_1[0xffa] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x497803
   * (`lea edi,[esi + 0x3fd4]`, esi = this file's own param_1): cell is
   * param_1+0x3fd4; tableHandle(+0x14)=param_1+0x3fe8 (== param_1[0xffa],
   * `undefined4 *` scales by 4) is zeroed just above. `param_1` is
   * `undefined4 *`, so byte offsets use `(int)param_1 + N`. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)param_1 + 0x3fd4, 0);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),1);
  *(undefined1 *)(param_1 + 0x1106) = 0;
  param_1[0x1083] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x49781d
   * (`lea edi,[esi + 0x41f8]`, esi = param_1): cell is param_1+0x41f8;
   * tableHandle(+0x14)=param_1+0x420c (== param_1[0x1083]) is zeroed
   * just above. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)param_1 + 0x41f8, 0);
  *(undefined1 *)(param_1 + 0xfed) = 0;
  param_1[0xfee] = 0;
  param_1[0xfec] = 0;
  param_1[0xff0] = 0;
  *(undefined1 *)(param_1 + 0xff1) = 0;
  param_1[0xff4] = 0;
  param_1[0xff3] = 0xffffffff;
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

