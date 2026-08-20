/* SpawnDropCaseProjectile - 0x00434ac0 in the original binary.
 *
 * RENAMED (2026-08-17, from FUN_00434ac0): allocates a FULL 0x3f9c projectile textured "dropcase"/"caseflame"/"caseblast_xes" - the falling supply-case event projectile.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at all 8 argless PeekPacketChecksumState() calls (8 C : 8 orig,
 * goto-free zip), from tools/guard_cell_resolve.py over
 * 0x434ac0-0x434fa0.  Another allocate-then-populate spawner in the
 * SpawnDropBombProjectile/SpawnItemCase family: the +0xf54 cell sits beside the
 * already-fixed Encode at the same offset, and the rest are the usual
 * globals - two rounds of g_clientContext+0x5b1ac / +0x5af88 /
 * &DAT_00796aa0 plus one &DAT_00e9ba40.
 */
#include "ghidra_types.h"


void SpawnDropCaseProjectile(undefined4 param_1,int param_2)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  byte bVar6;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053ca9b;
  *unaff_FS_OFFSET = &local_c;
  /* guard-cell: proven.  This helper receives the effects-guard block
   * ctx+0x6a7f70 in EAX (a register arg Ghidra dropped); every call
   * site in the binary was audited 2026-08-17 and passes exactly that
   * value, so the +4 peek is the global flag, not a per-object cell. */
  cVar1 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
  if (cVar1 == '\0') {
    piVar2 = operator_new(0x3f9c);
    local_4 = 0;
    if (piVar2 == (int *)0x0) {
      piVar2 = (int *)0x0;
    }
    else {
      InitProjectile(piVar2,0x186a2);
      *piVar2 = (int)&PTR_FUN_00555dec;
    }
    local_4 = 0xffffffff;
    iVar3 = FindPreloadedTextureByName(s_dropcase_00553c84);
    piVar2[7] = iVar3;
    (**(code **)(*piVar2 + 4))(s_normal_00552230);
    piVar2[6] = 0x183a;
    piVar2[0xe] = 0x189e;
    piVar2[0xe25] = 0x1fa6;
    piVar2[0xe26] = SUBFIELD(s_caseflame_00553c78,0,undefined4);
    piVar2[0xe27] = SUBFIELD(s_caseflame_00553c78,4,undefined4);
    *(undefined2 *)(piVar2 + 0xe28) = SUBFIELD(s_caseflame_00553c78,8,undefined2);
    *(undefined1 *)(piVar2 + 0xf) = 0xff;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` args - angr-confirmed at
     * 0x434ba5/0x434bcc/0x434be7/0x434c05/0x434c20/0x434c3b/0x434c56
     * (a run of `lea edi,[esi+N]`, esi = this function's own piVar2 -
     * the freshly-allocated projectile object) 7 distinct CValueGuard
     * cells at (int)piVar2+0xf54/0x3b48/0x1178/0x40/0x264/0x488/0x8d0.
     * See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((int)piVar2 + 0xf54, param_2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState((void *)((int)piVar2 + 0xf54));
    EncodeOutgoingPacketField((int)piVar2 + 0x3b48, uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((int)piVar2 + 0x1178, 0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((int)piVar2 + 0x40, param_2 << 8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((int)piVar2 + 0x264, 0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((int)piVar2 + 0x488, 0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((int)piVar2 + 0x8d0, 0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState((void *)&DAT_00e9ba40);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
     * 0x434c8a (`lea edi,[esi+0x6ac]`, esi = piVar2) the cell is
     * (int)piVar2+0x6ac. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((int)piVar2 + 0x6ac, uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState((void *)(g_clientContext + 0x5b1ac));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState((void *)(g_clientContext + 0x5af88));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState((void *)&DAT_00796aa0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = FloatToInt64();
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x434d35
     * (`lea edi,[esi+0xaf4]`, esi = piVar2) the cell is
     * (int)piVar2+0xaf4. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((int)piVar2 + 0xaf4, (iVar5 << 8) / iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState((void *)(g_clientContext + 0x5b1ac));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState((void *)(g_clientContext + 0x5af88));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState((void *)&DAT_00796aa0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = FloatToInt64();
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x434de8
     * (`lea edi,[esi+0xd18]`, esi = piVar2) the cell is
     * (int)piVar2+0xd18. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((int)piVar2 + 0xd18, ((0x62 - iVar5) * 0x100) / iVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = _rand();
    *(char *)((int)piVar2 + 0xf3f) = (char)iVar3;
    iVar3 = _rand();
    *(byte *)(piVar2 + 0x3d0) = (byte)iVar3;
    bVar6 = '\x01' << (*(byte *)((int)piVar2 + 0xf3f) & 7);
    bVar6 = ~bVar6 & (byte)iVar3 | bVar6;
    *(byte *)(piVar2 + 0x3d0) = bVar6;
    *(byte *)((int)piVar2 + 0xf41) = bVar6 + *(char *)((int)piVar2 + 0xf3f) + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = _rand();
    *(char *)((int)piVar2 + 0xf45) = (char)iVar3;
    iVar3 = _rand();
    *(byte *)((int)piVar2 + 0xf46) = (byte)iVar3;
    bVar6 = *(byte *)((int)piVar2 + 0xf45) & 7;
    bVar6 = ~('\x01' << bVar6) & (byte)iVar3 | '\0' << bVar6;
    *(byte *)((int)piVar2 + 0xf46) = bVar6;
    *(byte *)((int)piVar2 + 0xf47) = bVar6 + *(char *)((int)piVar2 + 0xf45) + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = _rand();
    *(char *)((int)piVar2 + 0x391b) = (char)iVar3;
    iVar3 = _rand();
    *(byte *)(piVar2 + 0xe47) = (byte)iVar3;
    bVar6 = *(byte *)((int)piVar2 + 0x391b) & 7;
    bVar6 = ~('\x01' << bVar6) & (byte)iVar3 | '\0' << bVar6;
    *(byte *)(piVar2 + 0xe47) = bVar6;
    *(byte *)((int)piVar2 + 0x391d) = bVar6 + *(char *)((int)piVar2 + 0x391b) + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x434f55
     * (`lea edi,[esi+0x3920]`, esi = piVar2) the cell is
     * (int)piVar2+0x3920. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((int)piVar2 + 0x3920, 0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)((int)piVar2 + 0x3813) = SUBFIELD(s_caseblast_xes_00553c68,0,undefined4);
    *(undefined4 *)((int)piVar2 + 0x3817) = SUBFIELD(s_caseblast_xes_00553c68,4,undefined4);
    *(undefined4 *)((int)piVar2 + 0x381b) = SUBFIELD(s_caseblast_xes_00553c68,8,undefined4);
    *(undefined2 *)((int)piVar2 + 0x381f) = SUBFIELD(s_caseblast_xes_00553c68,12,undefined2);
    RegisterActiveObject(0, 0, (undefined4 *)0);
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

