# State 7 — Avatar Store / Shop

The item/avatar shop, reached from the Game Room List. Browses purchasable
items and confirms purchases.

## Identity
- **State ID**: 7
- **vtable**: `vtable_State07_AvatarStore` (`0x5555f8`)
- **Object size**: 0x34818 (~215 KB) — constructed by `FUN_00443c20`, which
  builds an 8×0x224-byte array of per-avatar slots
- **ProcessPacket**: `State07_AvatarStore_ProcessPacket` (`0x4440c0`)
- **OnEnter**: `0x447760` · **OnExit**: `0x448050`

## Resources / images
- **Buttons**: `store_*.img`, `b_store_buy`, `b_store_cap`, `b_store_cloth`,
  `b_store_glasse`, `b_store_flag` (category tabs + buy), created via
  `CreateButtonWidget` in `OnEnter`.

## Rendering
- Uses the software blitter (non-battle screen). The category tabs and buy
  button draw via the generic active-object sweep; the item grid and the
  live avatar preview are drawn by the state's own render slots (the store
  reuses the same `AvataTexture`/`CharacterTexture` family as Ready Room /
  In-Battle for the avatar preview). Exact per-slot render function addresses
  for the store grid were not individually enumerated in this pass — treat the
  Ready Room item-grid renderer (below) as the closest confirmed analogue.

## Avatar parts & the live preview (see FILEFORMATS.md — "Avatar.xfs")
The four category tabs map 1:1 to the avatar part tables in `Avatar.xfs`:
`b_store_cap` → **Head** (`{m,f}h.dat`), `b_store_cloth` → **Body** (`{m,f}b.dat`),
`b_store_glasse` → **Glasses** (`{m,f}g.dat`), `b_store_flag` → **Flag** (`mf.dat`).
Each part table is `u32 count` + 132-byte `{ id, name[0x40], desc[0x40] }` records
(fully decoded — `tools/lzhuf/decode_avatar.py`).

The live preview composes the avatar the same way the lobby/battle does: a set of
per-part **equip codes** (each a `u16`: bit 15 = gender, bits 0–14 = the part id /
record index) is fed to the compositor **`LoadAvatarSprites`** (`0x4141b0`), which
`LoadSpriteSet`s each `{gender}{cat}{id:05d}.img` from `graphics.xfs` and blits the
parts into the **`AvataTexture1/2`** runtime render target. The store's slot
handlers (`EquipAvatarPart` equip-a-code / `UnequipAvatarSlot` clear-slot / `PreviewAvatarPart`)
push the previewed code into the store context (`+0x31488`) and re-run the
compositor. A committed outfit is stored as the packed `avatarEquipped` UInt64
(4 × u16 = Body / Head / Glasses / Flag — word order confirmed from
`ComposeAvatarSprites` (`0x4d1500`); see FILEFORMATS.md; split it with
`decode_avatar.py --equip <hex>`).

## Network (see PROTOCOL.md — "State 7" / Avatar Store)
| Opcode | Dir | Meaning |
|---|---|---|
| `0x600f` | out | request inventory |
| `0x6002` | in | owned-item inventory list (defines `InventoryItem`) |
| `0x6005` | in | store init / price-list population |
| `0x6017` (`payload==0`) | in | purchase-confirmation dialog |
| `0x6017` (`payload==0x6003`) | in | purchase-confirmation response |
| `0x6037` (`payload==0`) | in | purchase commit |
| `0x6027` | — | no-op scheduling checkpoint |

`InventoryItem` structure and the full field layouts are in PROTOCOL.md and
ARCHITECTURE.md ("InventoryItem — confirmed structure").

## Transitions
- **In**: from Game Room List (opcode `0x6001` room→store transition).
- **Out**: back to Game Room List.

## Reimplementation checklist
1. Construct the 8-slot avatar array; load the store button/tab images.
2. On enter: request inventory (`0x600f`), receive store price list (`0x6005`)
   and owned items (`0x6002`).
3. Render category tabs + buy button (widget sweep), the item grid, and a live
   avatar preview (reuse the avatar/character texture family).
4. Purchase flow: buy click → `0x6017` confirm dialog → `0x6037` commit.

## Open items
- The store's own grid-render function addresses and item-slot geometry weren't
  individually decompiled here (unlike Ready Room's item grid, which is fully
  mapped in [09_ready_room.md](09_ready_room.md)). Use that as the template and
  confirm against `store_*.img` when implementing.
