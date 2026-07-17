/* FUN_004e4010 - 0x004e4010 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004e4010(undefined4 param_1)

{
  PreloadTexture(&g_textureCache,s_CharacterTexture1_005568d8);
  PreloadTexture(&g_textureCache,s_CharacterTexture2_005568c4);
  PreloadTexture(&g_textureCache,s_CharEffectTexture1_005568a4);
  PreloadTexture(&g_textureCache,s_CharEffectTexture2_00556890);
  PreloadTexture(&g_textureCache,s_TagTexture_005568b8);
  PreloadTexture(&g_textureCache,s_BulletTexture1_00556880);
  PreloadTexture(&g_textureCache,s_BulletTexture2_00556870);
  PreloadTexture(&g_textureCache,s_FlameTexture1_00556860);
  PreloadTexture(&g_textureCache,s_FlameTexture2_00556850);
  PreloadTexture(&g_textureCache,s_FlameTexture3_00556840);
  PreloadTexture(&g_textureCache,s_FlameTexture4_00556830);
  PreloadTexture(&g_textureCache,s_RayonTexture1_00556820);
  PreloadTexture(&g_textureCache,s_RayonTexture2_00556810);
  PreloadTexture(&g_textureCache,s_SpecialTexture1_00556800);
  PreloadTexture(&g_textureCache,s_SpecialTexture2_005567f0);
  PreloadTexture(&g_textureCache,s_AvataTexture1_0055565c);
  PreloadTexture(&g_textureCache,s_AvataTexture2_00556914);
  PreloadTexture(&g_textureCache,s_AvataEffectTexture1_00556900);
  PreloadTexture(&g_textureCache,s_AvataEffectTexture2_005568ec);
  PreloadTexture(&g_textureCache,s_RiderTexture_005567e0);
  PreloadTexture(&g_textureCache,s_WeaterTexture_00557224);
  PreloadTexture(&g_textureCache,s_TornadoTexture_00555bc0);
  PreloadTexture(&g_textureCache,s_FirewallTexture_00555bb0);
  PreloadTexture(&g_textureCache,s_LightningTexture_00555b9c);
  PreloadTexture(&g_textureCache,s_Lightning_00555b90);
  PreloadTexture(&g_textureCache,s_CrashTexture_00555b80);
  PreloadTexture(&g_textureCache,s_LaserEffect_00556794);
  PreloadTexture(&g_textureCache,s_WaterEffect_00556788);
  PreloadTexture(&g_textureCache,&DAT_00554060);
  PreloadTexture(&g_textureCache,s_YesooriTexture_005567d0);
  PreloadTexture(&g_textureCache,s_JewelTexture_005567c0);
  PreloadTexture(&g_textureCache,param_1);
  PreloadTexture(&g_textureCache,s_ThorTexture1_005567b0);
  PreloadTexture(&g_textureCache,s_ThorTexture2_005567a0);
  return;
}

