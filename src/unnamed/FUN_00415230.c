/* FUN_00415230 - 0x00415230 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_00415230(char *param_1)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  /* EBX (param_1) is the chat text: both strstr calls at 0x41529b and
   * 0x4152ad push it as the haystack (needles: blob2 at [esp+0x88], then its
   * reverse at [esp+8]). Callers load it into EBX at 0x43e7b7, 0x4b9dbe,
   * 0x4d6778, 0x505b7a, 0x50775a. */
  char local_188;
  undefined4 local_187;
  char local_108 [128];
  undefined1 local_88 [132];

  local_188 = '\0';
  puVar5 = &local_187;
  for (iVar3 = 0x1f; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  *(undefined2 *)puVar5 = 0;
  *(undefined1 *)((int)puVar5 + 2) = 0;
  pcVar2 = local_108;
  /* Orig 0x41525a-0x415262: arg 1 = [esp+0x108], ESI = [esp+0x88] (the
   * second output) which is the buffer strlen'd at 0x41526c - Ghidra's
   * local_108 - so the second output goes straight into local_108. */
  BuildSystemInfoBlob(local_88, (undefined4 *)local_108);
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  iVar3 = (int)pcVar2 - (int)(local_108 + 1);
  iVar4 = 0;
  if (0 < iVar3) {
    pcVar2 = local_108 + iVar3 + -1;
    do {
      (&local_188)[iVar4] = *pcVar2;
      iVar4 = iVar4 + 1;
      pcVar2 = pcVar2 + -1;
    } while (iVar4 < iVar3);
  }
  iVar3 = FUN_00525ea0(param_1,local_108);
  if (iVar3 == 0) {
    iVar3 = FUN_00525ea0(param_1,&local_188);
    if (iVar3 == 0) {
      return 0;
    }
  }
  return 1;
}

