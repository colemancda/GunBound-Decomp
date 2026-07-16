/* FUN_00436070 - 0x00436070 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00436070(undefined4 param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  void *pvVar2;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053ca9b;
  *unaff_FS_OFFSET = &local_c;
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 == '\0') {
    pvVar2 = operator_new(0x4a8);
    local_4 = 0;
    if (pvVar2 != (void *)0x0) {
      FUN_00481fb0(pvVar2);
    }
    local_4 = 0xffffffff;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
     * 0x4360dd (`lea edi,[esi + 0x38]`, esi = the object just
     * constructed above via FUN_00481fb0(pvVar2), not this function's
     * own (unused) param_1): cell is pvVar2+0x38, the same checksum-cell
     * offset FUN_00481fb0.c/InitTornadoHazard.c zero-init/use for their own
     * `this`. `pvVar2` is `void *`, so byte offsets use
     * `(int)pvVar2 + N`. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((int)pvVar2 + 0x38, param_2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (*(int *)(&g_nCameraBoundY + g_clientContext) <= param_3) {
      param_3 = *(int *)(&g_nCameraBoundY + g_clientContext);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
     * 0x436113 (`lea edi,[esi + 0x25c]`, esi = pvVar2, same object as
     * above): cell is pvVar2+0x25c, matching FUN_00481fb0.c's second
     * cell offset. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((int)pvVar2 + 0x25c, param_3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    RegisterActiveObject(0, 0, (undefined4 *)0);
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

