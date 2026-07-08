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
