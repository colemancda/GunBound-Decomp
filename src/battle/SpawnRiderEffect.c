/* SpawnRiderEffect - 0x0042bb10 in the original binary.
 *
 * RENAMED (2026-08-17, from FUN_0042bb10): allocates a 0x48 effect object with the "rider" texture (s_rider_00553f98), clamps its Y to g_nCameraBoundY-0x26 and picks facing from the screen half; gated by the effects flag.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall SpawnRiderEffect(int param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  void *pvVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int unaff_ESI;
  
  /* guard-cell: proven.  This helper receives the effects-guard block
   * ctx+0x6a7f70 in EAX (a register arg Ghidra dropped); every call
   * site in the binary was audited 2026-08-17 and passes exactly that
   * value, so the +4 peek is the global flag, not a per-object cell. */
  cVar1 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
  if (cVar1 == '\0') {
    pvVar2 = operator_new(0x48);
    if (pvVar2 == (void *)0x0) {
      piVar3 = (int *)0x0;
    }
    else {
      piVar3 = (int *)FUN_004a2780();
    }
    iVar5 = g_clientContext;
    piVar3[0xe] = unaff_ESI;
    iVar4 = *(int *)(&g_nCameraBoundY + iVar5) + -0x26;
    if (param_1 <= *(int *)(&g_nCameraBoundY + iVar5) + -0x26) {
      iVar4 = param_1;
    }
    piVar3[0xf] = iVar4;
    piVar3[0x11] = param_3;
    *(bool *)(piVar3 + 0x10) = *(int *)(&g_nCameraBoundX + iVar5) / 2 < unaff_ESI;
    iVar5 = FindPreloadedTextureByName(s_rider_00553f98);
    piVar3[7] = iVar5;
    (**(code **)(*piVar3 + 4))(&DAT_00553f90);
    RegisterActiveObject(0, 0, (undefined4 *)0);
  }
  return;
}

