/* FUN_004d0a10 - 0x004d0a10 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-12, CValueGuard sweep): recovered the guard
 * cell at all 13 argless PeekPacketChecksumState() and all 6 one-arg
 * EncodeOutgoingPacketField() calls (both lists "clean").  Cells from
 * tools/guard_cell_resolve.py over 0x4d0a10-0x4d0dd7; the two families
 * interleave 1:1 with the original in address order (19 C : 19 orig).
 * All cells are g_clientContext-relative globals.
 *
 * One site needed reconstruction rather than just an argument.  The
 * Peek at 0x4d0c7c reads a cell out of the per-category array at
 * g_clientContext+0x595d8, stride 0x224, and the index is computed at
 * 0x4d0c42-0x4d0c5d as `(a / b) % 8` from the results of the two Peeks
 * immediately above it - both of which the decompile DISCARDED
 * (0x4d0c09 -> EDI, 0x4d0c32 -> frame[0x10], consumed by the `idiv` at
 * 0x4d0c45).  Those results are now captured into iVar7/iVar8 so the
 * index can be written out.  MSVC's truncating `%` matches the
 * `and 0x80000007 / jns / dec / or 0xfffffff8 / inc` sequence exactly.
 *
 * frame[0x10] is a one-slot scratch that is REWRITTEN before nearly
 * every use (0x4d0b3c, 0x4d0b95, 0x4d0c28, 0x4d0c74, 0x4d0cc6,
 * 0x4d0d68), and it alternates between holding a cell pointer and
 * holding a Peek RESULT, so each read was matched to its own most
 * recent writer.
 */
#include "ghidra_types.h"


void FUN_004d0a10(int *param_1,undefined2 *param_2)

{
  undefined1 uVar1;
  undefined2 uVar2;
  short sVar3;
  uint in_EAX;
  int iVar4;
  int iVar5;
  char *_Format;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  char local_80 [128];
  
  param_1[0x428] = in_EAX & 0xff;
  uVar2 = *param_2;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField((void *)(g_clientContext + 0xeba98), uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState((void *)(g_clientContext + 0xeba98));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar4 == 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState((void *)(g_clientContext + 0x45354));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_00438360();
  }
  if (*(char *)(g_clientContext + 0x45127) != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState((void *)(g_clientContext + 0x4512c));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState((void *)(g_clientContext + 0xeba98));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar4 - iVar5 == 10) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = PeekPacketChecksumState((void *)(g_clientContext + 0x4512c));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState((void *)(g_clientContext + 0xeba98));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = iVar4 - iVar5;
      _Format = (char *)GetLocalizedString(&g_localizedStringTable,0x261);
      _sprintf(local_80,_Format,iVar4);
      (**(code **)(*param_1 + 0x28))(local_80,2,6);
    }
  }
  SpawnWeatherHazards(g_clientContext);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar7 = PeekPacketChecksumState((void *)(g_clientContext + 0xeba98));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar8 = PeekPacketChecksumState((void *)(g_clientContext + 0x473a0));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar6 = PeekPacketChecksumState((void *)(g_clientContext + 0x595d8 + (iVar7 / iVar8) % 8 * 0x224));
  EncodeOutgoingPacketField((void *)(g_clientContext + 0xebcbc), uVar6);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState((void *)(g_clientContext + 0xeba98));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState((void *)(g_clientContext + 0x473a0));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar4 % iVar5 == 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState((void *)(g_clientContext + 0xeb854));
    EncodeOutgoingPacketField((void *)(g_clientContext + 0xeb854), iVar4 + 3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  iVar4 = *(int *)(g_clientContext + 0x621e0);
  if ((iVar4 != 0) && (*(int *)(iVar4 + 0x24) != 0xd)) {
    *(undefined4 *)(iVar4 + 0xb0b0) = 4;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState((void *)(g_clientContext + 0xeba98));
  EncodeOutgoingPacketField((void *)(g_clientContext + 0xeba98), iVar4 + 1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = *(undefined1 *)(param_2 + 1);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField((void *)(g_clientContext + 0x5af88), uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  sVar3 = *(short *)((int)param_2 + 3);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField((void *)(g_clientContext + 0x5b1ac), (int)sVar3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  param_1[0x42e] = 1;
  FUN_004cf310();
  return;
}

