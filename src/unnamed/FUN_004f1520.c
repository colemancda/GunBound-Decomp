/* FUN_004f1520 - 0x004f1520 in the original binary.
 *
 * unaff_EDI (the read-state handle) and unaff_ESI (the sprite/frame
 * object being populated) both arrive via dropped registers - sole
 * caller LoadSpriteSet.c already holds both (readState in EDI, the
 * freshly-allocated puVar3 sprite object in ESI per orig 0x408d5a/
 * 0x408ddb) but was calling this with zero arguments. Promoted to
 * explicit parameters.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_004f1520(void *unaff_EDI, int unaff_ESI)

{
  uint *puVar1;
  int iVar2;
  uint uVar3;
  void *pvVar4;

  iVar2 = ReadXFSEntryByte(unaff_EDI,unaff_ESI + 0x18);
  if ((((iVar2 == -2) || (iVar2 = ReadXFSEntryByte(unaff_EDI,unaff_ESI + 0x1b), iVar2 == -2)) ||
      (iVar2 = ReadXFSEntryByte(unaff_EDI,unaff_ESI + 0x1a), iVar2 == -2)) ||
     (((iVar2 = ReadXFSEntryByte(unaff_EDI,unaff_ESI + 0x19), iVar2 == -2 ||
       (iVar2 = ReadXFSEntryByte(unaff_EDI,unaff_ESI + 0x20), iVar2 == -2)) ||
      ((iVar2 = ReadXFSEntryByte(unaff_EDI,unaff_ESI + 0x24), iVar2 == -2 ||
       ((iVar2 = ReadXFSEntryByte(unaff_EDI,unaff_ESI + 0x28), iVar2 == -2 ||
        (iVar2 = ReadXFSEntryByte(unaff_EDI,unaff_ESI + 0x2c), iVar2 == -2)))))))) {
    return 0xffffffff;
  }
  iVar2 = ReadXFSEntryByte(unaff_EDI,(char *)(unaff_ESI + 0x30));
  if ((iVar2 != -2) &&
     (((iVar2 = ReadXFSEntryByte(unaff_EDI,unaff_ESI + 0x44), iVar2 != -2 &&
       (iVar2 = ReadXFSEntryByte(unaff_EDI,unaff_ESI + 0x48), iVar2 != -2)) &&
      (iVar2 = ReadXFSEntryByte(unaff_EDI,unaff_ESI + 0x4c), iVar2 != -2)))) {
    puVar1 = (uint *)(unaff_ESI + 0x3c);
    iVar2 = ReadXFSEntryByte(unaff_EDI,puVar1);
    if (iVar2 != -2) {
      uVar3 = *puVar1;
      if ((uVar3 & 1) != 0) {
        uVar3 = uVar3 + 1;
      }
      *puVar1 = uVar3;
      if ((*(int *)(unaff_ESI + 4) == 60000) && (*(int *)(unaff_ESI + 8) == 0)) {
        uVar3 = uVar3 * 2;
      }
      else {
        uVar3 = uVar3 & 0xfffffffe;
      }
      pvVar4 = operator_new(uVar3);
      *(void **)(unaff_ESI + 0x34) = pvVar4;
      iVar2 = ReadXFSEntryByte(unaff_EDI,pvVar4);
      if (iVar2 != -2) {
        if (*(char *)(unaff_ESI + 0x30) == '\0') {
          return 0;
        }
        iVar2 = ReadXFSEntryByte(unaff_EDI,(uint *)(unaff_ESI + 0x40));
        if (iVar2 != -2) {
          pvVar4 = operator_new(*(uint *)(unaff_ESI + 0x40) & 0xfffffffe);
          *(void **)(unaff_ESI + 0x38) = pvVar4;
          iVar2 = ReadXFSEntryByte(unaff_EDI,pvVar4);
          if (iVar2 != -2) {
            return 0;
          }
        }
      }
    }
    return 0xffffffff;
  }
  return 0xffffffff;
}

