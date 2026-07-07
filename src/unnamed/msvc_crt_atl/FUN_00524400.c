/* FUN_00524400 - 0x00524400 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_00524400(void)

{
  char cVar1;
  BOOL BVar2;
  DWORD DVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  DWORD local_8;
  DWORD local_4;
  
  iVar4 = 0;
  local_8 = 0;
  iVar5 = 0;
  do {
    do {
      do {
        while (local_8 != 0) {
LAB_00524507:
          iVar5 = 0;
          BVar2 = ReadFile(DAT_0056adf4,&DAT_005b1618,0x10,&local_4,(LPOVERLAPPED)0x0);
          if (((BVar2 == 0) || (local_4 == 0)) && (cVar1 = FUN_00522570(0x60f,0), cVar1 == '\0'))
          goto LAB_005246af;
          local_8 = local_8 - local_4;
          if (DAT_005b1620 != 0x60e) {
            if (DAT_005b1620 == 0x613) {
              if ((0x80 < DAT_005b1624) ||
                 (((BVar2 = ReadFile(DAT_0056adf4,&DAT_005b15d8,DAT_005b1624,&local_4,
                                     (LPOVERLAPPED)0x0), BVar2 == 0 || (local_4 == 0)) &&
                  (cVar1 = FUN_00522570(0x60f,0), cVar1 == '\0')))) goto LAB_005246af;
              local_8 = local_8 - local_4;
            }
            else if (DAT_005b1618 == 0x8b2) {
              if (DAT_005b1620 == 0) {
                DAT_005b1634 = '\0';
                DAT_005b162c = DAT_005b162c + 1;
              }
              else if (DAT_005b1620 == 0x610) {
                uVar6 = 0x610;
                goto LAB_005244f5;
              }
            }
            else if (DAT_005b1618 == 0x8b0) {
              if (DAT_005b162c == DAT_005b161c) {
                cVar1 = FUN_00523fc0(0x8b2,DAT_005b1620,0);
                if (cVar1 == '\0') {
                  cVar1 = FUN_00522570(0x60f,0);
                  goto joined_r0x0052463c;
                }
              }
              else {
                cVar1 = FUN_00522570(0x60f,0);
joined_r0x0052463c:
                if (cVar1 == '\0') goto LAB_005246af;
              }
              DAT_005b1634 = '\x01';
              DAT_005b162c = DAT_005b162c + 1;
            }
            else if (DAT_005b1618 == 0x8b1) {
              if ((DAT_005b1620 != 0x610) || (cVar1 = FUN_00522570(0x610,0), cVar1 != '\0')) {
                cVar1 = FUN_00523fc0(0x8b2,DAT_005b1620,DAT_005b1624);
                if (cVar1 == '\0') goto LAB_005244ef;
                cVar1 = FUN_00522570(DAT_005b1620,DAT_005b1624);
                goto joined_r0x005246a9;
              }
              goto LAB_005246af;
            }
          }
        }
        BVar2 = PeekNamedPipe(DAT_0056adf4,(LPVOID)0x0,0,(LPDWORD)0x0,&local_8,(LPDWORD)0x0);
        if ((BVar2 == 0) && (cVar1 = FUN_00522570(0x60f,0), cVar1 == '\0')) goto LAB_005246af;
        if (local_8 != 0) goto LAB_00524507;
        DVar3 = WaitForSingleObject(DAT_005b1630,2000);
        if ((DVar3 == 0) ||
           ((iVar5 = iVar5 + 1, 4 < iVar5 &&
            (((cVar1 = FUN_00523fc0(0x8b1,0x60e,0), cVar1 == '\0' &&
              (cVar1 = FUN_00522570(0x60f,0), cVar1 == '\0')) ||
             ((0x13 < iVar5 && (cVar1 = FUN_00522570(0x618,iVar5), cVar1 == '\0'))))))))
        goto LAB_005246af;
      } while ((DAT_005b1634 == '\0') || (iVar4 = iVar4 + 1, iVar4 < 2));
      iVar4 = 0;
      DAT_005b1634 = '\0';
      cVar1 = FUN_00523fc0(0x8b0,0,0);
    } while (cVar1 != '\0');
LAB_005244ef:
    uVar6 = 0x60f;
LAB_005244f5:
    cVar1 = FUN_00522570(uVar6,0);
joined_r0x005246a9:
  } while (cVar1 != '\0');
LAB_005246af:
  if (DAT_0056adf4 != (HANDLE)0xffffffff) {
    CloseHandle(DAT_0056adf4);
    DAT_0056adf4 = (HANDLE)0xffffffff;
  }
  return 0;
}

