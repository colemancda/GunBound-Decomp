/* FUN_0040d760 - 0x0040d760 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0040d760(void)

{
  char *pcVar1;
  LSTATUS LVar2;
  char *pcVar3;
  BYTE local_5;
  HKEY local_4;
  
  local_4 = (HKEY)0x0;
  LVar2 = RegOpenKeyExA((HKEY)&DAT_80000002,s_Software_Softnyx_GunBound_0056d3a0,0,0xf003f,&local_4)
  ;
  if (LVar2 == 0) {
    RegSetValueExA(local_4,s_LastServer_00552884,0,4,(BYTE *)(DAT_005b3484 + 0x3f804),4);
    RegSetValueExA(local_4,s_ShootingMode_00552858,0,3,&DAT_00d9aa20,1);
    RegSetValueExA(local_4,s_MouseSpeed_0055284c,0,4,&DAT_00d9aa24,4);
    local_5 = DAT_00d9aa28 == '\0';
    RegSetValueExA(local_4,s_MidiMode_00552840,0,3,&local_5,1);
    RegSetValueExA(local_4,s_MusicVolume_00552834,0,4,&DAT_00d9aa2c,4);
    RegSetValueExA(local_4,s_EffectVolume_00552824,0,4,&DAT_00d9aa30,4);
    RegSetValueExA(local_4,s_AutoRefresh_00552818,0,4,(BYTE *)&DAT_005b33f0,4);
    RegSetValueExA(local_4,s_Effect3D_0055280c,0,3,&DAT_00d9aa34,1);
    RegSetValueExA(local_4,s_Background_00552800,0,3,&DAT_00d9aa35,1);
    pcVar1 = &DAT_005b3368;
    do {
      pcVar3 = pcVar1;
      pcVar1 = pcVar3 + 1;
    } while (*pcVar3 != '\0');
    RegSetValueExA(local_4,s_GameName_005527f4,0,3,&DAT_005b3368,(DWORD)(pcVar3 + -0x5b3367));
    pcVar1 = &DAT_005b1cf0;
    do {
      pcVar3 = pcVar1;
      pcVar1 = pcVar3 + 1;
    } while (*pcVar3 != '\0');
    RegSetValueExA(local_4,s_ChannelName_005527e8,0,3,&DAT_005b1cf0,(DWORD)(pcVar3 + -0x5b1cef));
    RegCloseKey(local_4);
  }
  return;
}

