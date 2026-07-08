/* LoadClientSettingsFromRegistry - 0x0040d370 in the original binary.
 *
 * Loads persisted client settings from the registry at
 * HKEY_CURRENT_USER\Software\Softnyx\GunBound (and ...\GameBuddy). This is
 * where the externally-configured server-broker address enters the client:
 * the "IP" value -> DAT_005b2ad0 (128-byte hostname string) and "Port" ->
 * DAT_005b33e8, which State02 ServerSelect's OnEnter then connects to. Also
 * reads LastServer, Location, Screen, Version, ShootingMode, MouseSpeed,
 * MidiMode, Music/EffectVolume, AutoRefresh, Effect3D, Background, GameName,
 * ChannelName, Language, BuddyIP/BuddyPort (default port 0x20a0), and ShopURL
 * (default "http://shop.gunbound.com/avatar/"); and from the GameBuddy key,
 * an Executable path and a port. The game binary hardcodes no broker address
 * of its own - it is entirely provisioned here (presumably by the installer
 * or the .NET launcher stub).
 *
 * Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void LoadClientSettingsFromRegistry(void)

{
  undefined4 uVar1;
  LSTATUS LVar2;
  int iVar3;
  char *pcVar4;
  undefined4 *puVar5;
  BYTE local_15;
  DWORD local_14;
  HKEY local_10;
  DWORD local_c;
  HKEY local_8;
  undefined4 local_4;
  
  local_10 = (HKEY)0x0;
  local_8 = (HKEY)0x0;
  LVar2 = RegOpenKeyExA(HKEY_CURRENT_USER,s_Software_Softnyx_GunBound_0056d3a0,0,0xf003f,&local_10
                       );
  if (LVar2 == 0) {
    local_14 = 0x80;
    RegQueryValueExA(local_10,&DAT_00552898,(LPDWORD)0x0,&local_c,&DAT_005b2ad0,&local_14);
    local_14 = 4;
    RegQueryValueExA(local_10,&DAT_00552890,(LPDWORD)0x0,&local_c,(LPBYTE)&DAT_005b33e8,&local_14);
    RegQueryValueExA(local_10,s_LastServer_00552884,(LPDWORD)0x0,&local_c,(LPBYTE)&DAT_005b2b64,
                     &local_14);
    local_14 = 0x400;
    RegQueryValueExA(local_10,s_Location_00552878,(LPDWORD)0x0,&local_c,&DAT_005b1ed0,&local_14);
    LVar2 = RegQueryValueExA(local_10,s_Screen_00552870,(LPDWORD)0x0,&local_c,&DAT_005b2f68,
                             &local_14);
    if (LVar2 != 0) {
      iVar3 = 0;
      do {
        pcVar4 = &DAT_005b1ed0 + iVar3;
        (&DAT_005b2f68)[iVar3] = *pcVar4;
        iVar3 = iVar3 + 1;
      } while (*pcVar4 != '\0');
    }
    local_14 = 4;
    RegQueryValueExA(local_10,s_Version_00552868,(LPDWORD)0x0,&local_c,(LPBYTE)&local_4,&local_14);
    uVar1 = local_4;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(uVar1);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_14 = 1;
    RegQueryValueExA(local_10,s_ShootingMode_00552858,(LPDWORD)0x0,&local_c,&DAT_00d9aa20,&local_14)
    ;
    local_14 = 4;
    RegQueryValueExA(local_10,s_MouseSpeed_0055284c,(LPDWORD)0x0,&local_c,&DAT_00d9aa24,&local_14);
    local_14 = 1;
    RegQueryValueExA(local_10,s_MidiMode_00552840,(LPDWORD)0x0,&local_c,&local_15,&local_14);
    DAT_00d9aa28 = local_15 == '\0';
    local_14 = 4;
    RegQueryValueExA(local_10,s_MusicVolume_00552834,(LPDWORD)0x0,&local_c,&DAT_00d9aa2c,&local_14);
    RegQueryValueExA(local_10,s_EffectVolume_00552824,(LPDWORD)0x0,&local_c,&DAT_00d9aa30,&local_14)
    ;
    LVar2 = RegQueryValueExA(local_10,s_AutoRefresh_00552818,(LPDWORD)0x0,&local_c,
                             (LPBYTE)&DAT_005b33f0,&local_14);
    if (LVar2 != 0) {
      DAT_005b33f0 = 1;
    }
    local_14 = 1;
    RegQueryValueExA(local_10,s_Effect3D_0055280c,(LPDWORD)0x0,&local_c,&DAT_00d9aa34,&local_14);
    RegQueryValueExA(local_10,s_Background_00552800,(LPDWORD)0x0,&local_c,&DAT_00d9aa35,&local_14);
    local_14 = 0x80;
    RegQueryValueExA(local_10,s_GameName_005527f4,(LPDWORD)0x0,&local_c,&DAT_005b3368,&local_14);
    RegQueryValueExA(local_10,s_ChannelName_005527e8,(LPDWORD)0x0,&local_c,&DAT_005b1cf0,&local_14);
    local_14 = 4;
    RegQueryValueExA(local_10,s_Language_005527dc,(LPDWORD)0x0,&local_c,(LPBYTE)&DAT_005b3438,
                     &local_14);
    DAT_005b3438 = 1;
    local_14 = 0x80;
    RegQueryValueExA(local_10,s_BuddyIP_005527d4,(LPDWORD)0x0,&local_c,&DAT_005b1c70,&local_14);
    local_14 = 4;
    LVar2 = RegQueryValueExA(local_10,s_BuddyPort_005527c8,(LPDWORD)0x0,&local_c,(LPBYTE)&local_4,
                             &local_14);
    if (LVar2 == 0) {
      DAT_005b33f4 = (undefined2)local_4;
    }
    else {
      DAT_005b33f4 = 0x20a0;
    }
    local_14 = 0x80;
    LVar2 = RegQueryValueExA(local_10,s_ShopURL_005527c0,(LPDWORD)0x0,&local_c,(LPBYTE)&DAT_005b2b68
                             ,&local_14);
    if (LVar2 != 0) {
      pcVar4 = s_http___shop_gunbound_com_avatar__00552798;
      puVar5 = &DAT_005b2b68;
      for (iVar3 = 10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar5 = *(undefined4 *)pcVar4;
        pcVar4 = pcVar4 + 4;
        puVar5 = puVar5 + 1;
      }
    }
    RegCloseKey(local_10);
  }
  LVar2 = RegOpenKeyExA(HKEY_CURRENT_USER,s_Software_Softnyx_GameBuddy_0056d3bc,0,0xf003f,&local_8
                       );
  if (LVar2 == 0) {
    local_14 = 0x400;
    RegQueryValueExA(local_8,s_Executable_0055278c,(LPDWORD)0x0,&local_c,&DAT_005b26d0,&local_14);
    local_14 = 4;
    RegQueryValueExA(local_8,(LPCSTR)&PTR_DAT_00552788,(LPDWORD)0x0,&local_c,&DAT_005b2b50,&local_14
                    );
    RegCloseKey(local_8);
  }
  return;
}

