/* KnightIon_DtorBody - 0x0047be00 in the original binary.
 *
 * Destructor body behind KnightIon_ScalarDtor (slot 0 of vtable
 * 0x00556078, the vtable SpawnKnightIon installs on its object): it
 * stores that vtable, releases its sound channel slot and then chains to
 * DestroyProjectile; the object arrives as a stack argument (pushed by
 * the wrapper). Reached only from the wrapper. Confidence CERTAIN: the
 * class name is inherited from the spawner's naming.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void KnightIon_DtorBody(undefined4 *param_1)

{
  int iVar1;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  uStack_c = *unaff_FS_OFFSET;
  puStack_8 = &LAB_0053c03a;
  *unaff_FS_OFFSET = &uStack_c;
  *param_1 = &PTR_FUN_00556078;
  local_4 = 0;
  iVar1 = param_1[0xff0];
  if (g_soundAvailable != '\0') {
    if (iVar1 != -1) {
      (**(code **)(**(int **)(g_soundChannels + iVar1 * 4) + 0xc))();
    }
    if (iVar1 == 0) {
      DAT_00793568 = 0;
    }
  }
  param_1[0xff0] = 0xffffffff;
  local_4 = 0xffffffff;
  DestroyProjectile(param_1);
  *unaff_FS_OFFSET = uStack_c;
  return;
}

