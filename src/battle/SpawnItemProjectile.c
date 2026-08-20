/* SpawnItemProjectile - 0x004317b0 in the original binary.
 *
 * SIGNATURE FIX (2026-08-19) - the third instance of the SpawnPrimaryShot /
 * SpawnSuperShot defect, and the worst of them: this signature declared THREE
 * parameters where the original is `ret 0x1c` = SEVEN stack arguments, and all
 * 27 full-form call sites pass seven.  Ghidra's whole parameter frame was
 * shifted one slot, so every declared parameter named the wrong argument.
 *
 * Proved by tracking esp from the entry frame ([esp+0] = return address,
 * [esp+4] = param_1, ...) to each read:
 *     0x431877 `mov ecx,[esp+0x2c]` = entry+0xc  -> the value encoded into the
 *              X cell (obj+0xf54).  entry+0xc is the THIRD argument, but the
 *              old signature called it param_2.
 *     0x4318b6 `mov edx,[esp+0x30]` = entry+0x10 -> the Y cell (obj+0x1178);
 *              the fourth argument, called param_3.
 *     0x431814 `mov ax,[esp+0x3c]`  = entry+0x1c -> obj+0x3f9c; the seventh
 *              argument, which Ghidra named `in_stack_0000001c`.
 *     0x431849 `movzx eax,[esp+0x24]` -> `& 7` into obj+0x3c; the owner byte,
 *              i.e. the FIRST argument, which Ghidra named `unaff_retaddr`.
 * The old param_1 was declared but never referenced - it is the real second
 * argument, which this function genuinely ignores.
 *
 * Runtime impact of the shift: the item projectile took its X from the
 * caller's 2nd argument and its Y from the 3rd, one slot early in both cases,
 * so every item shot was positioned from the wrong values.
 *
 * No caller changes were needed - all 27 already passed seven arguments in
 * the right order; only the callee's view of them was wrong.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-12, CValueGuard sweep): recovered the guard
 * cell at all 12 argless PeekPacketChecksumState() calls (peek status
 * "clean", 12 C : 12 orig).  Cells from tools/guard_cell_resolve.py over
 * 0x4317b0-0x431d30; straight-line, so the sites order-zip, and the two
 * object-relative cells land next to Encode sites the 2026-07-15 sweep
 * had already resolved to the same base by a separate trace.
 *
 * The object is EBP = the FUN_00476510 return at 0x4317eb, i.e. piVar6.
 * guard_cell_resolve.py cannot see through that and reports every
 * EBP-based cell as `<clobbered by call at 0x4317eb>`; the offsets are
 * the ones the existing in-file Encode notes already document.
 *
 * The remaining ten cells are globals: &DAT_00e9ba40 three times,
 * &DAT_00796aa0 three times, and g_clientContext+0x5b1ac / +0x5af88 in
 * two matched rounds.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x00431855) */

void SpawnItemProjectile(byte param_1,undefined4 param_2,int param_3,int param_4,
                 undefined4 param_5,undefined4 param_6,undefined2 param_7)

{
  void *pvVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  byte bVar5;
  int *piVar6;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053795b;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  pvVar1 = operator_new(0x3fa8);
  piVar6 = (int *)0x0;
  local_4 = 0;
  if (pvVar1 != (void *)0x0) {
    piVar6 = (int *)FUN_00476510();
  }
  local_4 = 0xffffffff;
  ComputeShotViewBounds();
  piVar6[6] = -1;
  piVar6[0xe25] = -1;
  *(undefined2 *)(piVar6 + 0xfe7) = param_7;
  iVar2 = FindPreloadedTextureByName(s_bulletitem_00553d14);
  piVar6[7] = iVar2;
  (**(code **)(*piVar6 + 4))(s_normal_00552230);
  *(byte *)(piVar6 + 0xf) = param_1 & 7;
  piVar6[0xe] = 0x1965;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` args - angr-confirmed at
   * 0x43187c/0x4318a3/0x4318c1/0x4318df/0x431900 (a run of
   * `lea edi,[ebp+N]`, ebp = this function's own piVar6 - the freshly-
   * allocated item-projectile object) 5 distinct CValueGuard cells at
   * (int)piVar6+0xf54/0x3b48/0x1178/0x40/0x264. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)piVar6 + 0xf54, param_3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState((void *)((int)piVar6 + 0xf54));
  EncodeOutgoingPacketField((int)piVar6 + 0x3b48, uVar3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField((int)piVar6 + 0x1178, param_4);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField((int)piVar6 + 0x40, param_3 << 8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField((int)piVar6 + 0x264, param_4 << 8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState((void *)&DAT_00e9ba40);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = FloatToInt64();
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x431971
   * (`lea edi,[ebp+0x488]`) the cell is (int)piVar6+0x488. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)piVar6 + 0x488, (iVar4 << 8) / iVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState((void *)&DAT_00e9ba40);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = FloatToInt64();
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4319d0
   * (`lea edi,[ebp+0x8d0]`) the cell is (int)piVar6+0x8d0. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)piVar6 + 0x8d0, (iVar4 << 8) / iVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState((void *)&DAT_00e9ba40);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = FloatToInt64();
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x431a36
   * (`lea edi,[ebp+0x6ac]`) the cell is (int)piVar6+0x6ac. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)piVar6 + 0x6ac, -((iVar4 << 8) / iVar2));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState((void *)(g_clientContext + 0x5b1ac));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState((void *)(g_clientContext + 0x5af88));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState((void *)&DAT_00796aa0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = FloatToInt64();
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x431ae1
   * (`lea edi,[ebp+0xaf4]`) the cell is (int)piVar6+0xaf4. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)piVar6 + 0xaf4, (iVar4 << 8) / iVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState((void *)(g_clientContext + 0x5b1ac));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState((void *)(g_clientContext + 0x5af88));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState((void *)&DAT_00796aa0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = FloatToInt64();
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x431b94
   * (`lea edi,[ebp+0xd18]`) the cell is (int)piVar6+0xd18. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)piVar6 + 0xd18, ((0x62 - iVar4) * 0x100) / iVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = _rand();
  *(char *)((int)piVar6 + 0xf3f) = (char)iVar2;
  iVar2 = _rand();
  *(byte *)(piVar6 + 0x3d0) = (byte)iVar2;
  bVar5 = *(byte *)((int)piVar6 + 0xf3f) & 7;
  bVar5 = ~('\x01' << bVar5) & (byte)iVar2 | '\0' << bVar5;
  *(byte *)(piVar6 + 0x3d0) = bVar5;
  *(byte *)((int)piVar6 + 0xf41) = bVar5 + *(char *)((int)piVar6 + 0xf3f) + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState((void *)&DAT_00796aa0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x431c40
   * (`lea edi,[ebp+0x17e4]`) the cell is (int)piVar6+0x17e4. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)piVar6 + 0x17e4, uVar3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState((void *)((int)piVar6 + 0x17e4));
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x431c61
   * (`lea edi,[ebp+0x1a08]`) - this Peek re-read the +0x17e4 cell from
   * above (edi unchanged at Peek time), but the Encode targets a fresh
   * cell at (int)piVar6+0x1a08. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)piVar6 + 0x1a08, uVar3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = _rand();
  *(char *)((int)piVar6 + 0x391b) = (char)iVar2;
  iVar2 = _rand();
  *(byte *)(piVar6 + 0xe47) = (byte)iVar2;
  bVar5 = *(byte *)((int)piVar6 + 0x391b) & 7;
  bVar5 = ~('\x01' << bVar5) & (byte)iVar2 | '\0' << bVar5;
  *(byte *)(piVar6 + 0xe47) = bVar5;
  *(byte *)((int)piVar6 + 0x391d) = bVar5 + *(char *)((int)piVar6 + 0x391b) + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x431cf0
   * (`lea edi,[ebp+0x3920]`) the cell is (int)piVar6+0x3920. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)piVar6 + 0x3920, 0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  piVar6[0xfe8] = -1;
  *(undefined2 *)(piVar6 + 0xfe9) = 0xffff;
  piVar6[0xe26] = SUBFIELD(s_itemflame_00553d08,0,undefined4);
  piVar6[0xe27] = SUBFIELD(s_itemflame_00553d08,4,undefined4);
  *(undefined2 *)(piVar6 + 0xe28) = SUBFIELD(s_itemflame_00553d08,8,undefined2);
  *(undefined4 *)((int)piVar6 + 0x3813) = SUBFIELD(s_itemblast_xes_00553cf8,0,undefined4);
  *(undefined4 *)((int)piVar6 + 0x3817) = SUBFIELD(s_itemblast_xes_00553cf8,4,undefined4);
  *(undefined4 *)((int)piVar6 + 0x381b) = SUBFIELD(s_itemblast_xes_00553cf8,8,undefined4);
  *(undefined2 *)((int)piVar6 + 0x381f) = SUBFIELD(s_itemblast_xes_00553cf8,12,undefined2);
  RegisterActiveObject(0, 0, (undefined4 *)0);
  *unaff_FS_OFFSET = pvVar1;
  return;
}

