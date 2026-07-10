# Localized strings (`Language.txt`)

Every dialog/message string in the client is looked up by **numeric id** from a
table built at startup by `LoadLocalizedStrings` (`0x43da00`) and read by
`GetLocalizedString` (`0x43dc70`). See ARCHITECTURE.md "Text localization" for
the subsystem and the id-block/caller map. This document is the **string
table itself**.

## What's actually in the shipped asset

- **Source**: the `Language.txt` entry inside `orig/graphics.xfs` — the
  **English** `TestClient` build from
  [jglim/gunbound-launcher](https://github.com/jglim/gunbound-launcher), whose
  `GunBound.gme` is byte-for-byte identical to our decompilation target.
  Extracted and **checksum-verified** (`verify_checksum.py` →
  `stored=0x4441cd69 computed=0x4441cd69 MATCH`). Re-extract with:
  ```
  cd tools/lzhuf
  python3 -c "from extract_toc import read_toc; from decode_img import decode_entry_partial; \
    e=[x for x in read_toc('../../orig/graphics.xfs')[0] if x[0].lower()=='language.txt'][0]; \
    open('/tmp/Language.txt','wb').write(decode_entry_partial('../../orig/graphics.xfs',e[1],e[2],e[3],e[4],e[3]))"
  ```
- **The table is sparse.** This build defines **only ids 200–247** — the
  entire **error/message-dialog family**. Id 247 is present but **truncated**
  (`"Server Connection Terminates\n\nInfor…"` runs straight into ~14 KB of
  binary padding that fills out the entry's 18,211-byte decompressed size).
  Every *other* id the code requests (loading labels `0x320+`, HUD `0x27c+`,
  replay `0x1770+`, avatar-store `0xea6x`, …) is **not defined in this asset** —
  those UI elements are image/bitmap-driven in this build, and only the
  message-box dialogs are text-driven. (The previous Portuguese asset was the
  same shape, defining ids 200–240.)
- **This text is the authentic original English** — extracted verbatim,
  including the original typos (`Server Fuction Error`, `Loging Error`,
  `Selected Server in for guild members only`), the real support address in id
  206, and the dated maintenance notice in id 244.
- **Id ↔ error code**: `ShowErrorDialog(code)` resolves `id = code + 0xc7`
  (199). So the server-sent error code is `id − 199`, given in the first
  column. `<br>` marks a line break inside a message; a doubled `<br><br>` is
  the blank line between an error's title and its body. `%s` is a runtime
  substitution (a player/ID name).

## Error/message-dialog family (ids 200–247)

| id / code | Message (verbatim English) |
|---|---|
| 200 / 1 | Server Access Error<br><br>Can't access to server you required.<br>Please use other servers or try little later. |
| 201 / 2 | Access time has expired.<br><br>Either the problem in network or waiting time were too long.<br>The connection will close automatically.<br>Please try little later. |
| 202 / 3 | Server Fuction Error<br><br>Server isn't working properly.<br>Please try little later. |
| 203 / 4 | Server Function Error<br>There were errors on server functions.<br>Please try little later. |
| 204 / 5 | Login Error<br><br>Unregistered ID.<br>Please make a new ID. |
| 205 / 6 | Login Error<br><br>Wrong password.<br>Please check your password. |
| 206 / 7 | Login Error<br>Your ID can not be used on GIS.<br>Please use your local service.<br>Contact Gunbound for more questions.<br>(gunbound GM : gunbound_int@softnyx.co.kr) |
| 207 / 8 | Must be EMPTY!!! *(placeholder/reserved slot)* |
| 208 / 9 | Internal Data Error<br><br>The Internal data has been changed.<br>Please restart GunBound. |
| 209 / 10 | Channel access Error<br><br>Too many users in the channel.<br>Please try different channels. |
| 210 / 11 | Channel creation Error<br><br>Cannot create a channel.<br>Please use existing channels. |
| 211 / 12 | Channel access Error<br><br>You are already inside the channel. |
| 212 / 13 | Game Room Access Error<br><br>Too many users in the room.<br>Please try different rooms. |
| 213 / 14 | Game Room Creation Error<br><br>Can't create a room.<br>Please use one of the existing rooms. |
| 214 / 15 | Game Room Entry Error<br><br>You are already inside the room. |
| 215 / 16 | Game Room Blocked<br><br>The room is in playing.<br>You cannot enter. |
| 216 / 17 | Game Start Error<br><br><br>Can't start yet. |
| 217 / 18 | Server connection closed<br><br>Other user is trying to login using the same ID.<br>The connection closed. |
| 218 / 19 | Community Error<br><br>Can't communicate or invite others due to community error. |
| 219 / 20 | Access Forbidden<br><br>This is the forbidden ID<br>Connection closed. |
| 220 / 21 | Version Error<br><br>Different version.<br>Connection closed. |
| 221 / 22 | Loging Error<br><br>Unauthorized ID.<br>Please register ID again. |
| 222 / 23 | Server Connection Closed<br><br>%s's game connection is forbidden.<br>Connection closed. |
| 223 / 24 | Server Connection Closed<br><br>%s's guild game connection is forbidden.<br>Connection closed. |
| 224 / 25 | Data Modification<br><br>Important file was modified.<br>Application terminates. |
| 225 / 26 | Program Interfered<br><br>Writing same word repeatedly can harm others.<br>Frequent use of writing same words can result in losing ID.<br>Game shut down. |
| 226 / 27 | Buy Error<br><br>Don't have enough money.<br>Please buy different items. |
| 227 / 28 | Internal Data Error -2<br><br>Internal data has been modified.<br>Please restart GunBound Game. |
| 228 / 29 | Server Access Forbidden<br><br>Selected Server is limited by levels.<br>Please use different servers. |
| 229 / 30 | Server Access Forbidden<br><br>Selected Server in for guild members only.<br>Please use different servers. |
| 230 / 31 | Server Access Forbidden<br><br>Selected server is only for non-guild members.<br>Please use different servers. |
| 231 / 32 | Server Access Forbidden<br><br>Your guild cannot access this server.<br>Please use different servers. |
| 232 / 33 | Gift Error<br><br>The ID does not exist.<br>Please check you ID. |
| 233 / 34 | Sell Error<br><br>Can't Sell bought items. |
| 234 / 35 | Sell Error<br><br>Can't Sell event items. |
| 235 / 36 | Sell Error<br><br>Can't sell gifted items. |
| 236 / 37 | Gift Error<br><br>Can't send gifted items to others as gift. |
| 237 / 38 | Gift Error<br><br>Tried to send non-existing item(s).<br>Please retry. |
| 238 / 39 | Sending Gift<br><br>The gift has been sent. |
| 239 / 40 | Communication Error<br><br>Communication is not done properly.Game closed. |
| 240 / 41 | Communication Error<br><br>Data communication is not done properly.<br>Please restart GunBound.<br>Game closed. |
| 241 / 42 | Buy Error<br>Can't buy any more items due to reaching the closet limit(100).<br>Please sell or throw away some of your avatars and retry. |
| 242 / 43 | Room Creation Restriction<br><br>Cannot create rooms in the chosen server.<br>Please use other. |
| 243 / 44 | Sell/Throw out Error<br><br>This is not a purchased item(s).<br>Please retry. |
| 244 / 45 | Gift Function in Check<br><br>Under maintenance for improved functionality.<br>(Estimated Date : ~ August 13th , Tuesday) |
| 245 / 46 | Surrender Confirm<br><br>Surrender this game and give your team members 100 gold each. |
| 246 / 47 | Shopping Error<br><br>You have purchased too many item(s). <br>Throw out or sell unnecessary item(s).<br>(You can only have under 100 items) |
| 247 / 48 | Server Connection Terminates<br><br>Infor… *(truncated in the asset — message runs into binary padding)* |

## Ids the code requests but this asset does not define

The client's `GetLocalizedString` call sites reference several other id blocks
(see ARCHITECTURE.md "Text localization" → the id-block map): WinMain
`0x12d–0x142`/`0x7530–0x753b`, packet notices `0x19a–0x19e`, battle events
`0x25c–0x274`, HUD `0x27c–0x340`, loading `0x320–0x32f`, room-list
`0x4e20–0x4e23`, replay `0x1770–0x177f`, avatar-store `0xea60–0xea6d`. **None
of these are present** in this build's `Language.txt` — only ids 200–247 are.
Those UI elements are image-driven; their strings are not recoverable from the
assets in this repo.

## Previous (Portuguese) build

Before the asset swap, `orig/graphics.xfs` was the 206 MB Brazilian build,
whose `Language.txt` defined ids 200–240 in Portuguese (id 241 truncated). That
table is preserved in this file's git history if a translation cross-reference
is ever needed.
