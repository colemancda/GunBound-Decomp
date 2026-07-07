/* FUN_00423bf0 - 0x00423bf0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


undefined4 FUN_00423bf0(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_4;
  
  iVar2 = FUN_004f1390(0);
  if (iVar2 != 0) {
    ReadXFSEntryByte(iVar2,&local_4);
    uVar1 = local_4;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(uVar1);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_004f1460();
    iVar2 = FUN_004f1390(0);
    if (iVar2 != 0) {
      ReadXFSEntryByte(iVar2,&local_4);
      uVar1 = local_4;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(uVar1);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      FUN_004f1460();
      iVar2 = FUN_004f1390(0);
      if (iVar2 != 0) {
        ReadXFSEntryByte(iVar2,&local_4);
        QueueOutgoingPacketField(local_4);
        FUN_004f1460();
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField(0);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar2 = FUN_004f1390(0);
        if (iVar2 != 0) {
          ReadXFSEntryByte(iVar2,&local_4);
          QueueOutgoingPacketField(local_4);
          FUN_004f1460();
          iVar2 = FUN_004f1390(0);
          if (iVar2 != 0) {
            ReadXFSEntryByte(iVar2,&local_4);
            QueueOutgoingPacketField(local_4);
            FUN_004f1460();
            iVar2 = FUN_004f1390(0);
            if (iVar2 != 0) {
              ReadXFSEntryByte(iVar2,&local_4);
              QueueOutgoingPacketField(local_4);
              FUN_004f1460();
              iVar2 = FUN_004f1390(0);
              if (iVar2 != 0) {
                ReadXFSEntryByte(iVar2,&local_4);
                QueueOutgoingPacketField(local_4);
                FUN_004f1460();
                return 1;
              }
            }
          }
        }
      }
    }
  }
  return 0;
}

