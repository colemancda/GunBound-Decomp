/* FUN_00529486 - 0x00529486 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    ___sbh_alloc_new_region
   
   Library: Visual Studio 2003 Release */

undefined4 * ___sbh_alloc_new_region(void)

{
  undefined4 *puVar1;
  LPVOID pvVar2;
  
  if (DAT_00f29694 == DAT_00f296a4) {
    pvVar2 = HeapReAlloc(DAT_00f296ac,0,DAT_00f29698,(DAT_00f296a4 * 5 + 0x50) * 4);
    if (pvVar2 == (LPVOID)0x0) {
      return (undefined4 *)0x0;
    }
    DAT_00f296a4 = DAT_00f296a4 + 0x10;
    DAT_00f29698 = pvVar2;
  }
  puVar1 = (undefined4 *)((int)DAT_00f29698 + DAT_00f29694 * 0x14);
  pvVar2 = HeapAlloc(DAT_00f296ac,8,0x41c4);
  puVar1[4] = pvVar2;
  if (pvVar2 != (LPVOID)0x0) {
    pvVar2 = VirtualAlloc((LPVOID)0x0,0x100000,0x2000,4);
    puVar1[3] = pvVar2;
    if (pvVar2 != (LPVOID)0x0) {
      puVar1[2] = 0xffffffff;
      *puVar1 = 0;
      puVar1[1] = 0;
      DAT_00f29694 = DAT_00f29694 + 1;
      *(undefined4 *)puVar1[4] = 0xffffffff;
      return puVar1;
    }
    HeapFree(DAT_00f296ac,0,(LPVOID)puVar1[4]);
  }
  return (undefined4 *)0x0;
}

