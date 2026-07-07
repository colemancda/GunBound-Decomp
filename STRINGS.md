# Embedded Strings Reference

A categorized extraction of every defined string in `GunBound.gme`, pulled
from the Ghidra project's analyzed data (1,410 strings total — deduplicated
by address, not a raw `strings`-on-bytes dump, so this reflects what Ghidra's
analysis actually resolved as string data). Complements
[FILEFORMATS.md](FILEFORMATS.md) (asset naming conventions),
[ARCHITECTURE.md](ARCHITECTURE.md) (the widget/texture systems that consume
many of these), and [PROTOCOL.md](PROTOCOL.md).

Large, mechanical categories (asset filenames, button names) are collapsed
into `<details>` blocks so this document stays scannable — click to expand.
Generic Microsoft Visual C++ runtime library strings (locale data, `R60xx`
runtime-error messages, exception text, math-library symbol names — none of
it GunBound-specific) are summarized by count rather than listed in full, to
keep the signal-to-noise ratio high.

## Table of contents

- [Developer credits (embedded in the binary)](#developer-credits-embedded-in-the-binary)
- [Chat commands and mode strings](#chat-commands-and-mode-strings)
- [Registry paths](#registry-paths)
- [Data/config files referenced by name](#dataconfig-files-referenced-by-name)
- [Audio files — music (`.mp3`/`.wav`)](#audio-files--music-mp3wav)
- [Audio files — sound effects (`.xes`)](#audio-files--sound-effects-xes)
- [Texture identifiers (non-file symbolic names)](#texture-identifiers-non-file-symbolic-names)
- [UI button images (`b_*.img`)](#ui-button-images-b_img)
- [Non-button sprite/texture images (`.img`)](#non-button-spritetexture-images-img)
- [Windows DLLs referenced](#windows-dlls-referenced)
- [Notable format strings](#notable-format-strings)
- [System/CRT boilerplate (summarized, not itemized)](#systemcrt-boilerplate-summarized-not-itemized)

---

## Developer credits (embedded in the binary)

Found while tracing the Ready Room/Loading chat-input handlers (see
`State09_ReadyRoom_HandleChatInput` in [ARCHITECTURE.md](ARCHITECTURE.md)).
Reads as an embedded team credits list, likely surfaced via a chat command
(`guide`, `message`, `mutelist`, `loudall` appear in the same string cluster
— see "Chat commands" below) rather than a traditional splash-screen credits
roll. Each developer has a role/title paired with their handle, and `CozY`
gets a distinct personalized greeting rather than a role string:

| Address | String |
|---|---|
| `00553220` | `designer` |
| `0055322c` | `Server & Game buddy Programmer - reddragon` |
| `00553273` | ` - reddragon` |
| `00553280` | `reddragon` |
| `005532d8` | `jchlee75` |
| `00553318` | `yaong2` |
| `0055333f` | ` - jaeyong` |
| `0055334c` | `jaeyong` |
| `0055337d` | ` - oorusa` |
| `00553388` | `oorusa` |
| `005533bb` | ` - yESOOrI` |
| `005533c8` | `yesoori` |
| `0055347e` | ` - enddream` |
| `0055348c` | `enddream` |
| `00553498` | `Oh~! It's CozY here ^-^*` |
| `00553538` | `Game Programmer - comsik` |
| `00553563` | ` - comsik` |
| `00553578` | `comsik` |
| `00553580` | `loudall` |
| `00553590` | `%-15s` |
| `00553598` | `mutelist` |
| `005535d0` | `message` |
| `005535e0` | `guide` |
| `005535f8` | `teleport1` |
| `00553604` | `tnormal` |
| `0055360c` | `twnormal` |
| `00553618` | `wnormal` |

## Chat commands and mode strings

Found interleaved with the developer credits above, at nearby addresses —
likely all part of one chat-command dispatch table:

| Address | String | Likely meaning |
|---|---|---|
| `00553580` | `loudall` | Broadcast/shout chat command (as opposed to the confirmed proximity-filtered normal chat — see Channel 2 action `0x4002` in PROTOCOL.md). |
| `00553598` | `mutelist` | Opens/references a mute list command — checked in the same `/`-command parser as `message` below but not traced further this pass. |
| `005535d0` | `message` | **Confirmed — the `/message <player> <text>` whisper/direct-message command.** Fully traced in PROTOCOL.md's new "Channel 3" section: parses a target name and body, then either relays through the main game connection (opcode `0x1020`) or, if the target is resolved locally, sends directly over a separate TCP connection (opcode `0xa110`, via a genuine Winsock `send()` call) distinct from the UDP game-server socket used everywhere else in this project — most likely a "buddy"/messenger service, given the neighboring `Software\Softnyx\GameBuddy` registry key below. Has several `stricmp`-checked aliases at nearby addresses (`0x5535cc`-`0x5535e8`, exact text not individually catalogued here). |
| `005535e0` | `guide` | Help/guide command — has aliases at `0x5535e8`/`0x5535f0`, same `stricmp` chain, not traced further this pass. |
| `005535f8` | `teleport1` | **Corrected — not a chat command.** Its placement next to real chat-command strings in the data segment was coincidental. Decompiling its actual xrefs (`FUN_004cc5c0`) shows it's a **sound-effect name**, played via `FUN_004372f0(playerSlot, x, y, 0x14b5, "teleport1")` at both endpoints when two players' positions get swapped — this is the client-side implementation of `stage.dat`'s confirmed `귀환` ("Return") stage gimmick found via `Shinji.exe`'s editor dialog (see FILEFORMATS.md). Genuinely reachable in normal play whenever a stage has that gimmick enabled, not a hidden GM command. |
| `00553604` | `tnormal` | Sound-profile name (t-prefix variant of the confirmed `normal`/`wnormal` character audio profiles). |
| `0055360c` | `twnormal` | Sound-profile name (t-prefix variant of `wnormal`). |
| `00553618` | `wnormal` | Confirmed character audio profile — "weighted"/heavy character sound variant, referenced throughout the battle code. |

## Registry paths

| Address | String |
|---|---|
| `0056d3a0` | `Software\Softnyx\GunBound` |
| `0056d3bc` | `Software\Softnyx\GameBuddy` |
| `00552040` | `System\CurrentControlSet\Services\Class\%s` |

## Data/config files referenced by name

| Address | String |
|---|---|
| `005570ac` | `%s%s - %s.sv` |
| `00553660` | `Avatar.xfs` |
| `00551fcc` | `ChooseEvent.txt` |
| `00552c3c` | `FourWord.txt` |
| `00554008` | `Language.txt` |
| `00557218` | `Sound.txt` |
| `00552778` | `c:\comsik.txt` |
| `0055364c` | `characterdata.dat` |
| `00552cb4` | `fb.dat` |
| `00552ca4` | `fg.dat` |
| `00552cac` | `fh.dat` |
| `00551fdc` | `graphics.xfs` |
| `0055362c` | `itemdata.dat` |
| `00552c9c` | `mb.dat` |
| `00552c84` | `mf.dat` |
| `00552c8c` | `mg.dat` |
| `00552c94` | `mh.dat` |
| `005526fc` | `sound.xfs` |
| `0055363c` | `stage.dat` |
| `00552c30` | `test.txt` |

Notes:
- `mf.dat`/`mg.dat`/`mh.dat`/`mb.dat` and `fg.dat`/`fh.dat`/`fb.dat` —
  **confirmed** (by extracting and inspecting the real files from
  `avatar.xfs`): these are **per-gender avatar costume catalogs**, not
  color-channel tables as an earlier pass had guessed. `mb.dat` ("male,
  body"?) contains readable costume name strings like `"STANDARD"`,
  `"Standard clothing"`, `"Space Marine"` — a text-and-metadata catalog of
  wearable avatar items, parallel in spirit to `itemdata.dat`'s battle-item
  catalog. See [FILEFORMATS.md](FILEFORMATS.md)'s `avatar.xfs` section.
- `c:\comsik.txt` is a hardcoded **absolute debug path** referencing the
  `comsik` developer from the credits list above — almost certainly a
  leftover debug-logging file path from development, not something that
  executes in a shipped/normal environment (this exact string was also seen
  referenced early in `WinMain`, alongside `test.txt`).
- `Language.txt` and `Sound.txt` are now **confirmed** (see
  [FILEFORMATS.md](FILEFORMATS.md)) to live inside `graphics.xfs`, loaded
  the same way as `ChooseEvent.txt` via `OpenXFSArchive`/`FindXFSEntry`.
  `FourWord.txt`'s consumer function wasn't located, so it remains
  unconfirmed.

## Audio files — music (`.mp3`/`.wav`)

| Address | String |
|---|---|
| `005536c4` | `channel.mp3` |
| `005555d8` | `logo.mp3` |
| `00555570` | `logo2.mp3` |
| `00556af0` | `ready.mp3` |
| `00556924` | `slot-con.wav` |
| `005569c0` | `stage%d.mp3` |
| `005569cc` | `sudden.mp3` |
| `005572c0` | `title.mp3` |

## Audio files — sound effects (`.xes`)

91 confirmed `.xes` sound-effect filenames — a file extension not previously
documented in [FILEFORMATS.md](FILEFORMATS.md) prior to this pass. Naming
patterns observed: `<n>blast.xes` and `<n>fire.xes` (numbered weapon
impact/fire sounds, `n` likely a weapon or map-tile id), `<n>move.xes`/
`<n>nmove.xes` (movement sounds, `n`-prefixed variant distinct from plain),
plus a handful of named one-offs (`turn.xes`, `gold.xes`, `jblast.xes`).

<details>
<summary>Click to expand all 91 <code>.xes</code> filenames</summary>

| Address | String |
|---|---|
| `0055674c` | `%dmoon.xes` |
| `00552944` | `101blast.xes` |
| `00552a44` | `102fire.xes` |
| `00552bac` | `10move.xes` |
| `00552af8` | `10nmove.xes` |
| `00556140` | `10s1fire.xes` |
| `00556130` | `10s2fire.xes` |
| `00556150` | `10s3fire.xes` |
| `00552934` | `111blast.xes` |
| `00552a38` | `111fire.xes` |
| `005528a8` | `112blast.xes` |
| `005529b4` | `11blast.xes` |
| `00552ab0` | `11fire.xes` |
| `00552ba0` | `11move.xes` |
| `00552aec` | `11nmove.xes` |
| `00552924` | `121blast.xes` |
| `00552a2c` | `121fire.xes` |
| `005528e8` | `12blast.xes` |
| `005529f0` | `12fire.xes` |
| `00552b94` | `12move.xes` |
| `00552ae0` | `12nmove.xes` |
| `00552a20` | `131fire.xes` |
| `00552914` | `132blast.xes` |
| `00552b88` | `13move.xes` |
| `00552ad4` | `13nmove.xes` |
| `00552a14` | `141fire.xes` |
| `00552904` | `142blast.xes` |
| `00552b7c` | `14move.xes` |
| `00552ac8` | `14nmove.xes` |
| `005528f4` | `151blast.xes` |
| `00552a08` | `151fire.xes` |
| `00552b70` | `15move.xes` |
| `00552abc` | `15nmove.xes` |
| `00556028` | `15s1fire.xes` |
| `005529fc` | `161fire.xes` |
| `005529c0` | `162fire.xes` |
| `00552c18` | `1move.xes` |
| `00552b64` | `1nmove.xes` |
| `00552aa4` | `21fire.xes` |
| `005529a8` | `22blast.xes` |
| `0055289c` | `23blast.xes` |
| `00552c0c` | `2move.xes` |
| `00552b58` | `2nmove.xes` |
| `0055299c` | `31blast.xes` |
| `00552a98` | `31fire.xes` |
| `005528dc` | `32blast.xes` |
| `005529e4` | `32fire.xes` |
| `00552c00` | `3move.xes` |
| `00552b4c` | `3nmove.xes` |
| `00552990` | `42blast.xes` |
| `00552a8c` | `42fire.xes` |
| `00552bf4` | `4move.xes` |
| `00552b40` | `4nmove.xes` |
| `00552984` | `51blast.xes` |
| `00552a80` | `51fire.xes` |
| `005528d0` | `52blast.xes` |
| `005529d8` | `52fire.xes` |
| `00552be8` | `5move.xes` |
| `00552b34` | `5nmove.xes` |
| `00552978` | `62blast.xes` |
| `00552a74` | `62fire.xes` |
| `00552bdc` | `6move.xes` |
| `00552b28` | `6nmove.xes` |
| `0055296c` | `71blast.xes` |
| `00552a68` | `71fire.xes` |
| `00556418` | `71move.xes` |
| `005528c4` | `72blast.xes` |
| `005529cc` | `72fire.xes` |
| `00552bd0` | `7move.xes` |
| `00552b1c` | `7nmove.xes` |
| `00552960` | `82blast.xes` |
| `00552a5c` | `82fire.xes` |
| `00552bc4` | `8move.xes` |
| `00552b10` | `8nmove.xes` |
| `00552954` | `91blast.xes` |
| `00552a50` | `91fire.xes` |
| `005528b8` | `92blast.xes` |
| `00552bb8` | `9move.xes` |
| `00552b04` | `9nmove.xes` |
| `00553cb8` | `bombblast.xes` |
| `00551ea8` | `bpush1.xes` |
| `00551eb4` | `bselect1.xes` |
| `00551e98` | `bselect2.xes` |
| `00553c68` | `caseblast.xes` |
| `00556974` | `gold.xes` |
| `00553cf8` | `itemblast.xes` |
| `00555ffc` | `jblast.xes` |
| `00553c44` | `lightningblast.xes` |
| `00556758` | `turn.xes` |
| `00556764` | `turn2.xes` |
| `00554068` | `turnwa.xes` |

</details>

## Texture identifiers (non-file symbolic names)

These are not filenames — they're symbolic texture-slot identifiers passed
to the texture-cache lookup functions (`FindPreloadedTextureByName`/
`FindTextureCacheEntryByName`, see [ARCHITECTURE.md](ARCHITECTURE.md)),
resolved to actual loaded texture data at runtime rather than referring
directly to a file on disk. `ThorTexture1`/`ThorTexture2` are notable —
confirming the "Thor" mobile/character directly matches the game's subtitle
("Thor's Hammer"). `YesooriTexture`/`TagTexture` correspond to the confirmed
special game modes referenced elsewhere in the render code.

| Address | String |
|---|---|
| `00556900` | `AvataEffectTexture1` |
| `005568ec` | `AvataEffectTexture2` |
| `0055565c` | `AvataTexture1` |
| `00556914` | `AvataTexture2` |
| `00556880` | `BulletTexture1` |
| `00556870` | `BulletTexture2` |
| `005568a4` | `CharEffectTexture1` |
| `00556890` | `CharEffectTexture2` |
| `005568d8` | `CharacterTexture1` |
| `005568c4` | `CharacterTexture2` |
| `00555b80` | `CrashTexture` |
| `00555bb0` | `FirewallTexture` |
| `00556860` | `FlameTexture1` |
| `00556850` | `FlameTexture2` |
| `00556840` | `FlameTexture3` |
| `00556830` | `FlameTexture4` |
| `005567c0` | `JewelTexture` |
| `00555b9c` | `LightningTexture` |
| `00556820` | `RayonTexture1` |
| `00556810` | `RayonTexture2` |
| `005567e0` | `RiderTexture` |
| `00556800` | `SpecialTexture1` |
| `005567f0` | `SpecialTexture2` |
| `005568b8` | `TagTexture` |
| `005567b0` | `ThorTexture1` |
| `005567a0` | `ThorTexture2` |
| `00555bc0` | `TornadoTexture` |
| `00557224` | `WeaterTexture` |
| `005567d0` | `YesooriTexture` |

## UI button images (`b_*.img`)

252 confirmed `.img` filenames with the `b_` prefix, referenced by the
generic UI widget system (`LoadButtonDefinitionFromXFS` /
`CreateButtonWidget`, see [ARCHITECTURE.md](ARCHITECTURE.md)). Prefix
distribution shows which screens have the most interactive elements:

| Prefix | Count | Likely screen |
|---|---|---|
| `b_ready` | 61 | Ready Room |
| `b_gamelist` | 34 | Game/room list |
| `b_store` | 31 | Item store |
| `b_play` | 22 | Play/battle UI |
| `b_storewindow` | 14 | Item store window |
| `b_gamecreate` | 10 | Create-game dialog |
| `b_server` | 8 | Server select |
| `b_gamechat` | 8 | In-game chat |
| `b_buddy` | 8 | Buddy list |
| `b_slot` | 6 | Slot/loadout |
| `b_scroll` | 6 | Scrollbar controls |
| `b_poption` / `b_option` | 6 | Options dialogs |
| `b_report` | 5 | Report-player dialog |
| `b_buddywindow` | 5 | Buddy-list window |
| `b_myavatar` | 4 | Avatar/customization |
| `b_result` / `b_password` / `b_error` / `b_directgo` | 2 each | Misc dialogs |

<details>
<summary>Click to expand all 252 <code>b_*.img</code> filenames</summary>

| Address | String |
|---|---|
| `005523c0` | `b_buddy2_addfriend1.img` |
| `00552338` | `b_buddy2_addfriend2.img` |
| `005523ac` | `b_buddy2_close.img` |
| `0055231c` | `b_buddy2_deletefriend.img` |
| `00552350` | `b_buddy2_down.img` |
| `00552374` | `b_buddy2_exit.img` |
| `00552308` | `b_buddy2_exit2.img` |
| `00552388` | `b_buddy2_no.img` |
| `00552364` | `b_buddy2_up.img` |
| `00552398` | `b_buddy2_yes.img` |
| `00552648` | `b_buddy_del.img` |
| `00552258` | `b_buddy_down` |
| `00552404` | `b_buddy_down.img` |
| `00552248` | `b_buddy_exit` |
| `00552634` | `b_buddy_exit.img` |
| `00552658` | `b_buddy_plus.img` |
| `00552268` | `b_buddy_up` |
| `00552418` | `b_buddy_up.img` |
| `0055258c` | `b_buddywindow_delno.img` |
| `005525a4` | `b_buddywindow_delyes.img` |
| `00552600` | `b_buddywindow_exittalk.img` |
| `005525c0` | `b_buddywindow_friendclose.img` |
| `005525e0` | `b_buddywindow_friendplus.img` |
| `005537d4` | `b_directgo_cancel.img` |
| `005537ec` | `b_directgo_ok.img` |
| `00552238` | `b_error_confirm` |
| `00552518` | `b_error_confirm.img` |
| `005539a8` | `b_gamechat_ch1.img` |
| `00553994` | `b_gamechat_ch2.img` |
| `00553980` | `b_gamechat_ch3.img` |
| `0055396c` | `b_gamechat_ch4.img` |
| `00553958` | `b_gamechat_ch5.img` |
| `00553944` | `b_gamechat_ch6.img` |
| `00553930` | `b_gamechat_ch7.img` |
| `0055391c` | `b_gamechat_ch8.img` |
| `005538a4` | `b_gamecreate_1vs1.img` |
| `0055388c` | `b_gamecreate_2vs2.img` |
| `00553874` | `b_gamecreate_3vs3.img` |
| `0055385c` | `b_gamecreate_4vs4.img` |
| `0055382c` | `b_gamecreate_cancel.img` |
| `00553844` | `b_gamecreate_create.img` |
| `005538bc` | `b_gamecreate_jewel.img` |
| `005538d4` | `b_gamecreate_score.img` |
| `00553904` | `b_gamecreate_solo.img` |
| `005538ec` | `b_gamecreate_tag.img` |
| `00553760` | `b_gamelist_avatar` |
| `00553a6c` | `b_gamelist_avatar.img` |
| `00553788` | `b_gamelist_buddy` |
| `00553a9c` | `b_gamelist_buddy.img` |
| `005522a4` | `b_gamelist_buddydown` |
| `00552460` | `b_gamelist_buddydown.img` |
| `005522bc` | `b_gamelist_buddyup` |
| `0055247c` | `b_gamelist_buddyup.img` |
| `00552274` | `b_gamelist_channeldown` |
| `00552428` | `b_gamelist_channeldown.img` |
| `0055228c` | `b_gamelist_channelup` |
| `00552444` | `b_gamelist_channelup.img` |
| `0055374c` | `b_gamelist_create` |
| `00553a54` | `b_gamelist_create.img` |
| `005536d0` | `b_gamelist_directgo` |
| `005539bc` | `b_gamelist_directgo.img` |
| `0055379c` | `b_gamelist_exit` |
| `00553ab4` | `b_gamelist_exit.img` |
| `005536e4` | `b_gamelist_friend` |
| `005539d4` | `b_gamelist_friend.img` |
| `0055373c` | `b_gamelist_join` |
| `00553a40` | `b_gamelist_join.img` |
| `005536f8` | `b_gamelist_next` |
| `005539ec` | `b_gamelist_next.img` |
| `005537ac` | `b_gamelist_no.img` |
| `00553708` | `b_gamelist_prev` |
| `00553a00` | `b_gamelist_prev.img` |
| `00553774` | `b_gamelist_ranking` |
| `00553a84` | `b_gamelist_ranking.img` |
| `00553728` | `b_gamelist_viewall` |
| `00553a28` | `b_gamelist_viewall.img` |
| `00553718` | `b_gamelist_wait` |
| `00553a14` | `b_gamelist_wait.img` |
| `005537c0` | `b_gamelist_yes.img` |
| `0055586c` | `b_myavatar_dry.img` |
| `00555858` | `b_myavatar_gift.img` |
| `00555840` | `b_myavatar_leave.img` |
| `00555880` | `b_myavatar_sell.img` |
| `005569b0` | `b_option_cancel` |
| `00556a84` | `b_option_cancel.img` |
| `00556988` | `b_option_confirm` |
| `00556a54` | `b_option_confirm.img` |
| `0055699c` | `b_option_exitgame` |
| `00556a6c` | `b_option_exitgame.img` |
| `00553800` | `b_password_cancel.img` |
| `00553818` | `b_password_ok.img` |
| `0055412c` | `b_play_all` |
| `00554290` | `b_play_all.img` |
| `005540fc` | `b_play_down` |
| `00554260` | `b_play_down.img` |
| `00554174` | `b_play_option` |
| `005542d8` | `b_play_option.img` |
| `00554138` | `b_play_skip` |
| `005542a0` | `b_play_skip.img` |
| `00554088` | `b_play_ss` |
| `005541c0` | `b_play_ss.img` |
| `00554120` | `b_play_tag` |
| `00554198` | `b_play_tag.img` |
| `00554114` | `b_play_team` |
| `00554280` | `b_play_team.img` |
| `00554108` | `b_play_up` |
| `00554270` | `b_play_up.img` |
| `00554164` | `b_play_weapon1` |
| `005542c4` | `b_play_weapon1.img` |
| `00554154` | `b_play_weapon2` |
| `005542b0` | `b_play_weapon2.img` |
| `00554144` | `b_play_weapon3` |
| `00554184` | `b_play_weapon3.img` |
| `005540bc` | `b_poption_cancel` |
| `00554200` | `b_poption_cancel.img` |
| `00554094` | `b_poption_confirm` |
| `005541d0` | `b_poption_confirm.img` |
| `005540a8` | `b_poption_exitgame` |
| `005541e8` | `b_poption_exitgame.img` |
| `00556ecc` | `b_ready_1vs1.img` |
| `00556eb8` | `b_ready_2vs2.img` |
| `00556ea4` | `b_ready_3vs3.img` |
| `00556e90` | `b_ready_4vs4.img` |
| `00556d40` | `b_ready_aside.img` |
| `00556d54` | `b_ready_attackbomb.img` |
| `00556d6c` | `b_ready_basicbomb.img` |
| `00556e48` | `b_ready_bigbombdeath.img` |
| `00556d2c` | `b_ready_bside.img` |
| `00556b40` | `b_ready_buddy` |
| `00556b8c` | `b_ready_buddy.img` |
| `00556afc` | `b_ready_button` |
| `00556e1c` | `b_ready_campbatch.img` |
| `00556bb0` | `b_ready_cancel.img` |
| `00556b60` | `b_ready_changeteam` |
| `00556fac` | `b_ready_changeteam.img` |
| `00556b1c` | `b_ready_character` |
| `00556b74` | `b_ready_chatting.img` |
| `00556dd8` | `b_ready_death24.img` |
| `00556dc4` | `b_ready_death40.img` |
| `00556db0` | `b_ready_death56.img` |
| `00556d9c` | `b_ready_death72.img` |
| `00556e64` | `b_ready_doubledeath.img` |
| `00556b50` | `b_ready_exit` |
| `00556f98` | `b_ready_exit.img` |
| `00556f44` | `b_ready_itemdown.img` |
| `00556f5c` | `b_ready_itemup.img` |
| `00556ee0` | `b_ready_jewel.img` |
| `00556e04` | `b_ready_mixbatch.img` |
| `00556d14` | `b_ready_mobile01.img` |
| `00556cfc` | `b_ready_mobile02.img` |
| `00556ce4` | `b_ready_mobile03.img` |
| `00556ccc` | `b_ready_mobile04.img` |
| `00556cb4` | `b_ready_mobile05.img` |
| `00556c9c` | `b_ready_mobile06.img` |
| `00556c84` | `b_ready_mobile07.img` |
| `00556c6c` | `b_ready_mobile08.img` |
| `00556c54` | `b_ready_mobile09.img` |
| `00556c3c` | `b_ready_mobile10.img` |
| `00556c24` | `b_ready_mobile11.img` |
| `00556c0c` | `b_ready_mobile12.img` |
| `00556bf4` | `b_ready_mobile13.img` |
| `00556bdc` | `b_ready_mobile14.img` |
| `00556bc4` | `b_ready_mobile15.img` |
| `00556f70` | `b_ready_nextmap.img` |
| `00556d84` | `b_ready_nobombing.img` |
| `00556e7c` | `b_ready_nodeath.img` |
| `00556ba0` | `b_ready_ok.img` |
| `00556b30` | `b_ready_option` |
| `00556f84` | `b_ready_prevmap.img` |
| `00556dec` | `b_ready_randombatch.img` |
| `005570c8` | `b_ready_ready` |
| `00556fdc` | `b_ready_ready.img` |
| `00556f04` | `b_ready_score.img` |
| `00556b0c` | `b_ready_scroll` |
| `00556f18` | `b_ready_solo.img` |
| `00556e34` | `b_ready_ssdeath.img` |
| `005570d8` | `b_ready_startgame` |
| `00556fc4` | `b_ready_startgame.img` |
| `00556ef4` | `b_ready_tag.img` |
| `00556f2c` | `b_ready_writetitle.img` |
| `005522d0` | `b_report_cancel.img` |
| `0055253c` | `b_report_close.img` |
| `00552564` | `b_report_confirm.img` |
| `00552550` | `b_report_exit.img` |
| `005522e4` | `b_report_report.img` |
| `00554074` | `b_result_confirm` |
| `005541a8` | `b_result_confirm.img` |
| `005526dc` | `b_scroll_bar.img` |
| `005526a4` | `b_scroll_bar2.img` |
| `005526b8` | `b_scroll_down.img` |
| `0055267c` | `b_scroll_down2.img` |
| `005526cc` | `b_scroll_up.img` |
| `00552690` | `b_scroll_up2.img` |
| `00557198` | `b_server_all.img` |
| `00557170` | `b_server_buddygame` |
| `005571c8` | `b_server_buddygame.img` |
| `00557158` | `b_server_choiceserver` |
| `005571ac` | `b_server_choiceserver.img` |
| `00557144` | `b_server_exitgame` |
| `005571e0` | `b_server_exitgame.img` |
| `00557184` | `b_server_friend.img` |
| `005540d0` | `b_slot_cancel` |
| `00554228` | `b_slot_cancel.img` |
| `005540ec` | `b_slot_retry` |
| `0055424c` | `b_slot_retry.img` |
| `005540e0` | `b_slot_use` |
| `0055423c` | `b_slot_use.img` |
| `00555764` | `b_store_buddygame` |
| `0055597c` | `b_store_buddygame.img` |
| `005556fc` | `b_store_buy` |
| `005558f8` | `b_store_buy.img` |
| `00555758` | `b_store_cap` |
| `0055596c` | `b_store_cap.img` |
| `005556cc` | `b_store_cashcharge` |
| `005558bc` | `b_store_cashcharge.img` |
| `00555748` | `b_store_cloth` |
| `00555958` | `b_store_cloth.img` |
| `005556e0` | `b_store_down` |
| `005558d4` | `b_store_down.img` |
| `00555690` | `b_store_dry` |
| `005556bc` | `b_store_event01` |
| `005558a8` | `b_store_event01.img` |
| `005556ac` | `b_store_event02` |
| `00555894` | `b_store_event02.img` |
| `00555778` | `b_store_exit` |
| `00555994` | `b_store_exit.img` |
| `00555718` | `b_store_exitem` |
| `0055591c` | `b_store_exitem.img` |
| `00555728` | `b_store_flag` |
| `00555930` | `b_store_flag.img` |
| `00555680` | `b_store_gift` |
| `00555738` | `b_store_glasse` |
| `00555944` | `b_store_glasse.img` |
| `00555708` | `b_store_puton` |
| `00555908` | `b_store_puton.img` |
| `0055569c` | `b_store_sell` |
| `005556f0` | `b_store_up` |
| `005558e8` | `b_store_up.img` |
| `00555a30` | `b_storewindow_cancel` |
| `005557d8` | `b_storewindow_cancel.img` |
| `00555a48` | `b_storewindow_cash` |
| `00555788` | `b_storewindow_cash.img` |
| `00555a70` | `b_storewindow_cashcharge` |
| `005557b8` | `b_storewindow_cashcharge.img` |
| `00555a8c` | `b_storewindow_confirm` |
| `005557f4` | `b_storewindow_confirm.img` |
| `00555a5c` | `b_storewindow_gold` |
| `005557a0` | `b_storewindow_gold.img` |
| `0055566c` | `b_storewindow_no` |
| `00555810` | `b_storewindow_no.img` |
| `00555a1c` | `b_storewindow_yes` |
| `00555828` | `b_storewindow_yes.img` |

</details>

## Non-button sprite/texture images (`.img`)

315 confirmed `.img` filenames that are not UI buttons — battle-effect
sprites, gameplay assets, and misc screen graphics. Prefix distribution:

| Prefix | Count | Likely content |
|---|---|---|
| `bullet` | 100 | Per-weapon projectile sprites |
| `flame` | 48 | Explosion/fire animation frames |
| `tank` | 32 | Mobile/vehicle sprites |
| `ssflame` | 16 | Special-weapon explosion variants |
| `jewel` | 8 | Jewel/gem mode pickups |
| `jflame` | 4 | Jewel-mode explosion variants |

Plus misc singles: `thor.img`/`thorl.img` (Thor mobile), `yesoori.img`
(Yesoori mobile), `titlemode.img`, `store_*.img`, `server_*.img`,
`slot.img`, `textballoon.img`, `waitmessage.img`.

<details>
<summary>Click to expand all 315 non-button <code>.img</code> filenames</summary>

| Address | String |
|---|---|
| `00555a08` | `%05d.img` |
| `00552200` | `%cb%05d.img` |
| `005521cc` | `%cb%05dl.img` |
| `005521f4` | `%cg%05d.img` |
| `005521bc` | `%cg%05dl.img` |
| `005521e8` | `%ch%05d.img` |
| `005521ac` | `%ch%05dl.img` |
| `0055723c` | `%s%d.img` |
| `005523f4` | `avataimsi.img` |
| `005544e8` | `bombflame.img` |
| `005523d8` | `buddy2.img` |
| `0055266c` | `buddy_back.img` |
| `0055261c` | `buddy_window_back.img` |
| `005524b8` | `buddymode.img` |
| `00554cb4` | `bullet10n.img` |
| `00554c94` | `bullet10nl.img` |
| `00554c74` | `bullet10p.img` |
| `00554c64` | `bullet10pl.img` |
| `00554ca4` | `bullet10s.img` |
| `00554c84` | `bullet10sl.img` |
| `00554ba4` | `bullet11n.img` |
| `00554b84` | `bullet11nl.img` |
| `00554b64` | `bullet11p.img` |
| `00554b54` | `bullet11pl.img` |
| `00554b94` | `bullet11s.img` |
| `00554b74` | `bullet11sl.img` |
| `00554a54` | `bullet12c.img` |
| `00554a44` | `bullet12cl.img` |
| `00554ab4` | `bullet12n.img` |
| `00554a94` | `bullet12nl.img` |
| `00554a74` | `bullet12p.img` |
| `00554a64` | `bullet12pl.img` |
| `00554aa4` | `bullet12s.img` |
| `00554a84` | `bullet12sl.img` |
| `00554998` | `bullet13n.img` |
| `00554978` | `bullet13nl.img` |
| `00554958` | `bullet13p.img` |
| `00554948` | `bullet13pl.img` |
| `00554988` | `bullet13s.img` |
| `00554968` | `bullet13sl.img` |
| `00554848` | `bullet14c.img` |
| `00554838` | `bullet14cl.img` |
| `005548a8` | `bullet14n.img` |
| `00554888` | `bullet14nl.img` |
| `00554868` | `bullet14p.img` |
| `00554858` | `bullet14pl.img` |
| `00554898` | `bullet14s.img` |
| `00554878` | `bullet14sl.img` |
| `0055478c` | `bullet15n.img` |
| `0055476c` | `bullet15nl.img` |
| `0055474c` | `bullet15p.img` |
| `0055473c` | `bullet15pl.img` |
| `0055477c` | `bullet15s.img` |
| `0055475c` | `bullet15sl.img` |
| `00554644` | `bullet16n.img` |
| `00554624` | `bullet16nl.img` |
| `00554604` | `bullet16p.img` |
| `005545f4` | `bullet16pl.img` |
| `00554634` | `bullet16s.img` |
| `00554614` | `bullet16sl.img` |
| `005554b8` | `bullet1n.img` |
| `00555498` | `bullet1nl.img` |
| `00555478` | `bullet1p.img` |
| `00555468` | `bullet1pl.img` |
| `005554a8` | `bullet1s.img` |
| `00555488` | `bullet1sl.img` |
| `005553e0` | `bullet2n.img` |
| `005553c0` | `bullet2nl.img` |
| `005553a0` | `bullet2p.img` |
| `00555390` | `bullet2pl.img` |
| `005553d0` | `bullet2s.img` |
| `005553b0` | `bullet2sl.img` |
| `005552f0` | `bullet3n.img` |
| `005552d0` | `bullet3nl.img` |
| `005552b0` | `bullet3p.img` |
| `005552a0` | `bullet3pl.img` |
| `005552e0` | `bullet3s.img` |
| `005552c0` | `bullet3sl.img` |
| `00555218` | `bullet4n.img` |
| `005551f8` | `bullet4nl.img` |
| `005551d8` | `bullet4p.img` |
| `005551c8` | `bullet4pl.img` |
| `00555208` | `bullet4s.img` |
| `005551e8` | `bullet4sl.img` |
| `00555140` | `bullet5n.img` |
| `00555120` | `bullet5nl.img` |
| `00555100` | `bullet5p.img` |
| `005550f0` | `bullet5pl.img` |
| `00555130` | `bullet5s.img` |
| `00555110` | `bullet5sl.img` |
| `00555068` | `bullet6n.img` |
| `00555048` | `bullet6nl.img` |
| `00555028` | `bullet6p.img` |
| `00555018` | `bullet6pl.img` |
| `00555058` | `bullet6s.img` |
| `00555038` | `bullet6sl.img` |
| `00554f90` | `bullet7n.img` |
| `00554f70` | `bullet7nl.img` |
| `00554f50` | `bullet7p.img` |
| `00554f40` | `bullet7pl.img` |
| `00554f80` | `bullet7s.img` |
| `00554f60` | `bullet7sl.img` |
| `00554e64` | `bullet8n.img` |
| `00554e44` | `bullet8nl.img` |
| `00554e24` | `bullet8p.img` |
| `00554e14` | `bullet8pl.img` |
| `00554e54` | `bullet8s.img` |
| `00554e34` | `bullet8sl.img` |
| `00554da0` | `bullet9n.img` |
| `00554d80` | `bullet9nl.img` |
| `00554d60` | `bullet9p.img` |
| `00554d50` | `bullet9pl.img` |
| `00554d90` | `bullet9s.img` |
| `00554d70` | `bullet9sl.img` |
| `0055453c` | `bulletevent1.img` |
| `00554528` | `bulletevent1l.img` |
| `00554458` | `bulletitem.img` |
| `00554448` | `bulletiteml.img` |
| `00554498` | `caseflame.img` |
| `00554d24` | `crystal.img` |
| `00554d14` | `crystall.img` |
| `005524f0` | `cursor.img` |
| `00554508` | `dropbomb.img` |
| `005544f8` | `dropbombl.img` |
| `005544a8` | `dropcase.img` |
| `005544d8` | `drophammer.img` |
| `005544c8` | `drophammerl.img` |
| `0055252c` | `error_back.img` |
| `005524d8` | `errordialog.img` |
| `00557248` | `event%d1800.img` |
| `005554e8` | `event14-%d.img` |
| `00554c54` | `flame101.img` |
| `00554c44` | `flame102.img` |
| `00554c1c` | `flame103.img` |
| `0055545c` | `flame11.img` |
| `00554b44` | `flame111.img` |
| `00554b34` | `flame112.img` |
| `00554b0c` | `flame113.img` |
| `00555450` | `flame12.img` |
| `00554a1c` | `flame121.img` |
| `00554a0c` | `flame122.img` |
| `005549e4` | `flame123.img` |
| `00555434` | `flame13.img` |
| `00554938` | `flame131.img` |
| `00554928` | `flame132.img` |
| `00554900` | `flame133.img` |
| `00554810` | `flame141.img` |
| `00554800` | `flame142.img` |
| `005547d8` | `flame143.img` |
| `00554704` | `flame151.img` |
| `005546f4` | `flame152.img` |
| `005546bc` | `flame153.img` |
| `005545e4` | `flame161.img` |
| `005545d4` | `flame162.img` |
| `005545ac` | `flame163.img` |
| `0055536c` | `flame21.img` |
| `00555360` | `flame22.img` |
| `00555344` | `flame23.img` |
| `00555294` | `flame31.img` |
| `00555288` | `flame32.img` |
| `0055526c` | `flame33.img` |
| `005551bc` | `flame41.img` |
| `005551b0` | `flame42.img` |
| `00555194` | `flame43.img` |
| `005550e4` | `flame51.img` |
| `005550d8` | `flame52.img` |
| `005550bc` | `flame53.img` |
| `0055500c` | `flame61.img` |
| `00555000` | `flame62.img` |
| `00554fe4` | `flame63.img` |
| `00554ed0` | `flame71.img` |
| `00554ec4` | `flame72.img` |
| `00554eb0` | `flame73.img` |
| `0055440c` | `flame81.img` |
| `00554e08` | `flame82.img` |
| `00554df4` | `flame83.img` |
| `00554d44` | `flame91.img` |
| `00554d38` | `flame92.img` |
| `00554d08` | `flame93.img` |
| `00554518` | `flameevent1.img` |
| `00554438` | `flameitem.img` |
| `00553b4c` | `gamelist_back.img` |
| `00553b20` | `gamelist_channel.img` |
| `00553b38` | `gamelist_chat.img` |
| `00553b0c` | `gamelist_create.img` |
| `00553adc` | `gamelist_directgo.img` |
| `00553af4` | `gamelist_password.img` |
| `00553ac8` | `gameliststage.img` |
| `005544b8` | `hammerflame.img` |
| `005524ac` | `icon.img` |
| `0055250c` | `info.img` |
| `00554568` | `item1.img` |
| `0055455c` | `item2.img` |
| `00554488` | `itemcase.img` |
| `005543b0` | `jewel1.img` |
| `00554380` | `jewel1l.img` |
| `005543a4` | `jewel2.img` |
| `00554374` | `jewel2l.img` |
| `00554398` | `jewel3.img` |
| `00554368` | `jewel3l.img` |
| `0055438c` | `jewel4.img` |
| `0055435c` | `jewel4l.img` |
| `00554350` | `jflame1.img` |
| `00554344` | `jflame2.img` |
| `00554338` | `jflame3.img` |
| `0055432c` | `jflame4.img` |
| `00554728` | `knightbullet.img` |
| `00554714` | `knightbulletl.img` |
| `005546cc` | `knightflame.img` |
| `00554684` | `knightion.img` |
| `00554674` | `knightionl.img` |
| `00554be4` | `laserion.img` |
| `00554bd4` | `laserionl.img` |
| `00554474` | `lightningflame.img` |
| `00557000` | `load_back.img` |
| `00557098` | `load_stage%02d.img` |
| `00555514` | `loadmode.img` |
| `00555504` | `loadstage.img` |
| `005555e4` | `logomode.img` |
| `0055557c` | `logomode2.img` |
| `0055220c` | `mf%05d.img` |
| `005521dc` | `mf%05dl.img` |
| `005524c8` | `numberfont.img` |
| `005526f0` | `numfont.img` |
| `00556ad0` | `play_back.img` |
| `00556a98` | `play_option.img` |
| `00556ac0` | `play_slot.img` |
| `00554574` | `playmode.img` |
| `00554218` | `playoption.img` |
| `005523e4` | `presentmode.img` |
| `005524a0` | `rank1.img` |
| `00552494` | `rank2.img` |
| `00554ef0` | `rayonevent1.img` |
| `00554edc` | `rayonevent1l.img` |
| `00554f30` | `rayonmine.img` |
| `00554f20` | `rayonminel.img` |
| `00557088` | `ready_back.img` |
| `00557020` | `ready_item1.img` |
| `00557010` | `ready_item2.img` |
| `00557044` | `ready_itemshop1.img` |
| `00557030` | `ready_itemshop2.img` |
| `00557058` | `ready_selectcharacter.img` |
| `00557074` | `ready_selectmap.img` |
| `0055257c` | `report_back.img` |
| `005522f8` | `reportmode.img` |
| `005543bc` | `result_back.img` |
| `005543f8` | `rider.img` |
| `00557208` | `server_back.img` |
| `005571f8` | `server_list.img` |
| `00554468` | `slot.img` |
| `00554f10` | `srayonmine.img` |
| `00554f00` | `srayonminel.img` |
| `00554424` | `ss1.img` |
| `00554418` | `ss1l.img` |
| `0055541c` | `ssflame1.img` |
| `00554c00` | `ssflame10.img` |
| `00554af0` | `ssflame11.img` |
| `005549d4` | `ssflame12.img` |
| `005548e4` | `ssflame13.img` |
| `005547c8` | `ssflame14.img` |
| `005546a0` | `ssflame15.img` |
| `00554590` | `ssflame16.img` |
| `0055532c` | `ssflame2.img` |
| `00555254` | `ssflame3.img` |
| `0055517c` | `ssflame4.img` |
| `005550a4` | `ssflame5.img` |
| `00554fcc` | `ssflame6.img` |
| `00554ea0` | `ssflame7.img` |
| `00554ddc` | `ssflame8.img` |
| `00554cf0` | `ssflame9.img` |
| `005559e4` | `store_avatar.img` |
| `005559f8` | `store_back.img` |
| `005559c0` | `store_icon.img` |
| `005559d0` | `store_myavatar.img` |
| `005559a8` | `store_window_back.img` |
| `005554dc` | `tank1.img` |
| `00554cd8` | `tank10.img` |
| `00554ccc` | `tank10l.img` |
| `00554bc8` | `tank11.img` |
| `00554bbc` | `tank11l.img` |
| `00554ad8` | `tank12.img` |
| `00554acc` | `tank12l.img` |
| `005549bc` | `tank13.img` |
| `005549b0` | `tank13l.img` |
| `005548cc` | `tank14.img` |
| `005548c0` | `tank14l.img` |
| `005547b0` | `tank15.img` |
| `005547a4` | `tank15l.img` |
| `00554668` | `tank16.img` |
| `0055465c` | `tank16l.img` |
| `005554d0` | `tank1l.img` |
| `00555404` | `tank2.img` |
| `005553f8` | `tank2l.img` |
| `00555314` | `tank3.img` |
| `00555308` | `tank3l.img` |
| `0055523c` | `tank4.img` |
| `00555230` | `tank4l.img` |
| `00555164` | `tank5.img` |
| `00555158` | `tank5l.img` |
| `0055508c` | `tank6.img` |
| `00555080` | `tank6l.img` |
| `00554fb4` | `tank7.img` |
| `00554fa8` | `tank7l.img` |
| `00554e88` | `tank8.img` |
| `00554e7c` | `tank8l.img` |
| `00554dc4` | `tank9.img` |
| `00554db8` | `tank9l.img` |
| `005543e8` | `teleport1.img` |
| `005543d8` | `teleport2.img` |
| `00556ff0` | `textballoon.img` |
| `00556ab4` | `thor.img` |
| `00556aa8` | `thorl.img` |
| `005572cc` | `titlemode.img` |
| `005524fc` | `waitmessage.img` |
| `00554550` | `yesoori.img` |

</details>

## Windows DLLs referenced

15 unique DLL names appear as strings (import-table module names and/or
runtime `LoadLibrary` targets):

- `advapi32.dll`
- `ddraw.dll`
- `dinput8.dll`
- `dsound.dll`
- `gdi32.dll`
- `imm32.dll`
- `kernel32.dll` (one raw occurrence has a leading `|kernel32.dll` — likely
  a string-table/import-descriptor artifact, not a real filename variant)
- `mscoree.dll`
- `ntdll.dll`
- `ole32.dll`
- `oleaut32.dll`
- `shell32.dll`
- `user32.dll`
- `winmm.dll`
- `ws2_32.dll`

This confirms the stack already identified in [ARCHITECTURE.md](ARCHITECTURE.md):
DirectDraw + DirectSound8 + DirectInput8 + Winsock, no Direct3D DLL
(`d3d8.dll`/`d3d9.dll`) is referenced directly — the Direct3D7 COM interfaces
documented in the rendering section are obtained via `ddraw.dll`'s
`DirectDrawCreateEx`/QueryInterface chain, not a separate d3d DLL, which
matches DirectX 7's unified `ddraw.dll` packaging.

## Notable format strings

Format strings that are neither CRT boilerplate nor asset filenames,
found via targeted grep excluding the CRT string range (`0x544xxx`-`0x549xxx`):

| Format string | Likely use |
|---|---|
| `modes\%d\%d,%d` | Registry-relative mode/config path |
| `System\CurrentControlSet\Services\Class\%s` | Registry service-class lookup (see Registry paths above) |
| `%s%s%07d.bmp` | Screenshot filename generator |
| `%sADB.exe` | External helper executable path (ADB = likely an anti-debug/anti-cheat helper, name coincidental with Android Debug Bridge) |
| `%-15s` | Left-padded column formatting (chat/list rendering) |
| `%s[%3d/%3d]` | Scoreboard/room-label format — confirmed used by both `State03_GameRoomList_RenderRoomLabel` and the in-battle scoreboard |
| `ani_%02d` | Animation-frame filename/key generator |
| `jewel%d`, `flame10%d`, `flame%d3`, `flame%d%d`, `tank%d`, `jflame%d`, `FlameTexture%d`, `emotion%d` | Runtime-generated asset/texture keys, paralleling the static `.img` filenames above |
| `%04d-%02d-%02d` | Date formatting (year-month-day) |
| `[%d/%d]` | Generic counter display (e.g. round X/Y) |
| `%d %s` | Generic count + label |
| `%s%s - %s.sv` | Replay filename generator (see [FILEFORMATS.md](FILEFORMATS.md)) |
| `%Y%m%d %H%M` | `strftime` pattern used to build the replay filename timestamp |
| `%d.%d.%d.%d` | IP address formatting |
| `i5 %lu` | Unresolved — reads like a developer debug-log format string (address `0x569f4c`) |
| `g6, gg ret: %d` | Unresolved — reads like a developer debug-log format string, possibly "good game" related (address `0x56a178`) |

## System/CRT boilerplate (summarized, not itemized)

Roughly 700 of the 1,410 total defined strings — about half the entire
string table — are standard Microsoft Visual C++ 2003 runtime and Win32
API boilerplate, not GunBound-specific content. These are concentrated in
the address range `0x544xxx`-`0x549xxx` with a few scattered elsewhere.
Categories, with representative examples rather than a full listing:

- **Locale/date-format strings**: `HH:mm:ss`, `dddd, MMMM dd, yyyy`, full
  month and day names, `AM`/`PM`.
- **VC++ Runtime Library error messages**: `R6002` through `R6029`
  (e.g. "floating point not loaded", "not enough space for arguments"),
  `TLOSS error`, `SING error`, `DOMAIN error`, buffer-overrun and
  security-check failure messages.
- **Math library symbol names**: `floor`, `log10`, `exp10`, `_nextafter`.
- **COM/C++ exception boilerplate**: `invalid string position`,
  `bad allocation`, `Unknown exception`, `bad exception`.
- **Win32 API/feature-detection strings**: `GAIsProcessorFeaturePresent`,
  `AuthenticAMD`, `GenuineIntel`, `InitializeCriticalSectionAndSpinCount`,
  `GetProcessWindowStation`, `IsDebuggerPresent`.

None of this reflects GunBound game logic — it's linked in automatically
by the VC++ 2003 static runtime and standard Win32 feature-detection
idioms used at startup.
