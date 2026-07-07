# GunBound Network Protocol — Full Packet Reference

Consolidated, exhaustive reference for every opcode/action confirmed via
static analysis in Ghidra. Every opcode gets its own subheading below —
this document is intentionally verbose; for a compact architectural summary
of *how* the protocol is structured, see [ARCHITECTURE.md](ARCHITECTURE.md).
For the on-disk/file formats (`.xfs`, `.dat`, `.img`, `.sv`), see
[FILEFORMATS.md](FILEFORMATS.md).

**Scope note**: this covers every opcode branch found in the five confirmed
`ProcessPacket` screen handlers and the three confirmed `ProcessBattleAction`
real-time handlers — i.e. every packet-shaped code path reachable from the
`CGameState` object model. It does **not** claim to be the literal complete
protocol; opcodes handled by not-yet-located code (e.g. any handler outside
the `CGameState` hierarchy, if one exists) aren't included. See "Known gaps"
at the end. All branches (every `if`/`switch case`) in all 5 `ProcessPacket`
handlers and all 3 `ProcessBattleAction` handlers have been located and read
at least once — cross-checked handler-by-handler against total branch counts
— so within this scope, coverage is complete.

## Table of contents

- [How the protocol is structured](#how-the-protocol-is-structured)
- [Channel 1 — `ProcessPacket`](#channel-1--processpacket-opcodes-by-screen)
  - [State 1 — Title](#state-1--title-screen)
  - [State 2 — Server/Channel Select](#state-2--serverchannel-select-state02_serverselect_processpacket-0x4e02b0)
  - [State 3 — Game Room List](#state-3--game-room-list--channel-lobby-state03_gameroomlist_processpacket-0x426ad0)
  - [State 7 — Avatar Store](#state-7--avatar-store--shop-state07_avatarstore_processpacket-0x4440c0)
  - [State 9 — Ready Room](#state-9--ready-room-state09_readyroom_processpacket-0x4d38c0)
  - [State 11 — In-Battle](#state-11--in-battle-state11_inbattle_processpacket-0x4b4100)
- [Channel 2 — `ProcessBattleAction`](#channel-2--processbattleaction-by-screen)
  - [State 10 — Loading](#state-10--loading-state10_loading_processbattleaction-0x43e440)
  - [State 9 — Ready Room](#state-9--ready-room-state09_readyroom_processbattleaction-0x4d4ea0)
  - [State 11 — In-Battle](#state-11--in-battle-state11_inbattle_processbattleaction-0x4b5460)
- [Confirmed recurring structures](#confirmed-recurring-structures)
- [Known gaps](#known-gaps)

---

## How the protocol is structured

Two independent dispatch channels exist per game state, both **virtual
methods on the same `CGameState`-derived object** (see ARCHITECTURE.md's
vtable table):

- **Channel 1 — `ProcessPacket(int payloadLen, ushort opcode, ushort *payload)`**
  (vtable slot 1). The reliable, screen-scoped protocol. Each screen has its
  own opcode range and its own handler function; opcode values are reused
  across screens with different meanings since only one screen is ever active
  at a time (the server tracks which screen each client is on, so there's no
  global ambiguity even though, say, `0x2001` and `0x6001` mean different
  things in different handlers).
- **Channel 2 — `ProcessBattleAction(void *packetBuf, int packetLen)`**
  (vtable slot 2). A second protocol, present only on Loading/ReadyRoom/
  InBattle (every other state uses the shared no-op for this vtable slot),
  with a different **fixed 33-byte header** (see below) instead of the
  simple `(len, opcode, payload)` triple. **Now proven at the socket
  level** (previously a working theory only) — see ARCHITECTURE.md's
  "Socket-level proof" writeup: tracing both `recvfrom` callers forward
  shows Channel 2 is dispatched **synchronously, straight from the network
  receive callback**, with only a lightweight length/checksum check, no
  sequence tracking or dedup. Channel 1 goes through a much larger
  reliable-UDP peer layer (per-slot sequencing, duplicate detection, acks,
  RTT tracking) that **queues** validated packets rather than dispatching
  them immediately — they're drained later, not inline with `recvfrom`.
  This confirms the real-time/low-latency-vs-reliable-ordered distinction
  architecturally, not just by inference from which states implement it.

All outgoing packet fields are pushed through a lightweight
**XOR-based encode/checksum** function family (`EncodeOutgoingPacketField`,
`AddToPacketChecksum`, `SubFromPacketChecksum`, `PeekPacketChecksumState`,
`PacketChecksumEquals`/`NotEquals` — see ARCHITECTURE.md) — this is **not
cryptographic encryption**, more an anti-tamper/integrity/sequence measure.

### Channel 1 header

Just the three parameters passed to `ProcessPacket`:

| Field | Type | Notes |
|---|---|---|
| `payloadLen` | `int` | Length of the payload buffer in bytes. |
| `opcode` | `ushort` | Dispatches the big `if`/`switch` chain in each screen's handler. |
| `payload` | `ushort*` | Raw buffer; individual handlers cast sub-fields to `byte`/`ushort`/`int`/`char*` freely at fixed offsets — there is no single universal payload struct, each opcode defines its own layout. |

### Channel 2 header

A fixed 33-byte (`0x21`) header precedes the payload on every action, for
every screen that implements this channel:

```
offset  type    field
+0x00   ?       unidentified (2 bytes, not yet decoded)
+0x02   ushort  action type   (the dispatch value, analogous to Channel 1's opcode)
+0x04   ?       unidentified (1 byte)
+0x05   byte    source player slot (validated 0-7 in State 11's handler — confirms the 8-player cap independently)
+0x06..+0x20  ?  unidentified, 27 bytes, not decoded
+0x21   ...     payload start (action-specific layout begins here)
```

---

## Channel 1 — `ProcessPacket` opcodes, by screen

### State 1 — Title screen

No packet handler — vtable slot 1 is the shared `CGameState_NoOpVirtual_A`
no-op for this state. The Title screen does not process any network data;
it's a purely local, timed splash screen (see ARCHITECTURE.md — its slot-9
"tick" function is a 60-tick counter that auto-transitions to Server Select
after ~3 seconds, and its `OnEnter` only starts background music).

### State 2 — Server/Channel Select (`State02_ServerSelect_ProcessPacket`, `0x4e02b0`)

#### Opcode `0x1001` — Report local P2P address (outgoing)

**Direction**: outgoing, triggered locally (not a direct response to a
specific received opcode within this snippet — the code path builds and
sends this packet as part of connection setup).

**Behavior**: builds a reply with opcode `0x1010` containing this client's
own name/info fields, then calls **`getsockname()` twice** to retrieve the
local socket's bound address, appending both results (address and port) into
the outgoing packet before sending.

**Significance**: this is the **P2P NAT-traversal handshake**. The client is
reporting its own local `IP:port` back to the server so the server can relay
it to other players attempting a direct peer-to-peer connection (used later
for the real-time Channel 2 traffic during battle). This directly connects
to the `CCommP2P<>` notify window discovered during the earliest phase of
this project (a hidden window used for `WSAAsyncSelect` event notification
on the P2P socket).

#### Opcode `0x101f` — Session/server handoff

**Direction**: incoming.

**Payload**: `payload[0]` (a `uint`), `payload[2]` (a `uint`).

**Behavior**: both values are stored into session-scoped globals; two
login/session-handoff flag globals (`DAT_00e55e3c`, `DAT_007934f8`) flip
from `0` to `1`.

**Significance**: likely a session token or server address handed off to the
client right after selecting a channel/server, marking the login sequence
as progressed to the next stage. The exact meaning of the two `uint` fields
(session ID? server IP? both?) is not individually disambiguated.

#### Opcode `0x1012` — Server error code translation

**Direction**: incoming.

**Payload**: `*payload` is a `ushort` server error code.

**Behavior**: a `switch` on `*payload` maps four possible server-side error
codes to internal reason codes, stored at a per-slot array location
(`this + (*(int*)(this+0x68))*4 + 0x28`):

| Server code | Internal reason code |
|---|---|
| `0x5001` | `0x1d` |
| `0x5011` | `0x1e` |
| `0x5012` | `0x1f` |
| `0x5013` | `0x20` |

After the mapping, the handler does further UI-state bookkeeping (clears a
countdown global `DAT_0056d118`, then walks a linked structure at
`DAT_00e9be94` checking room-membership-like fields — this tail section
wasn't decoded in full detail, only the opcode's entry point and the error
mapping table are confirmed) to drive a "can't join: `<reason>`"-style error
dialog.

**Significance**: this is the client's translation layer between raw
numeric server error codes and whatever internal reason-code enum the UI
error-dialog system expects — a classic "protocol code → localized/UI code"
indirection layer.

#### Opcode `0x1102` — Server/channel list population

**Direction**: incoming.

**Behavior**: zeroes a 4 KB buffer (`0x400` dwords at `iVar20 + 0x4004a`),
then parses a list of variable-length entries out of the payload. Each
entry's layout: a 2-byte field, then a 1-byte field, then a length-prefixed
string (the length byte precedes the string bytes), repeated for however
many entries fit. Entries are copied into a table at `+0x3f84a`, indexed by
an incrementing counter (`uStack_f0`).

**Significance**: this is the **server/channel list** shown on the
"choose your server" screen — each entry is presumably one selectable
server/channel with a numeric identifier, a status/flag byte, and a
display name string.

---

### State 3 — Game Room List / channel lobby (`State03_GameRoomList_ProcessPacket`, `0x426ad0`)

This is the busiest single handler in the protocol — the channel lobby
where players browse and join/create game rooms. 6,736 bytes, the function
that was originally identified and named simply `ProcessPacket` before the
per-screen naming convention was adopted.

#### Opcode `0x2001` — Session cleanup / generic ack

**Direction**: incoming.

**Payload**: `payload[0]`, treated as boolean-ish.

**Behavior**: branches to one of two cleanup/notify helper functions
depending on `payload[0]`, then calls `FUN_00507cc0(1, sessionField)`.

**Significance**: a generic session-level cleanup/acknowledgment opcode.
This exact opcode value (`0x2001`) recurs with entirely different meanings
in State 7's and State 9's and State 11's handlers too — it appears to be a
reused "generic housekeeping" opcode number across multiple screens, each
implementing their own version of "something routine just happened, clean
up local state."

#### Opcode `0x201f` — Per-slot record lookup/insert

**Direction**: incoming.

**Payload**: `payload[0]` (a `byte`, treated as a slot id).

**Behavior**: looks up an existing record for the given slot id via
`FUN_004259d0`; on a lookup miss (`-1` returned), inserts a new record via
`FUN_0041b8c0` using several derived offset calculations based on the slot
id (stride patterns of `0xd` and `9` bytes appear in the offset arithmetic,
suggesting small fixed-size per-slot records distinct from the main
0x224-byte player struct).

**Significance**: unconfirmed whether this is a chat-line insert or an
item/inventory-adjacent record insert — the helper function names weren't
resolved to a clear semantic, only the lookup-then-insert-on-miss pattern is
confirmed.

#### Opcode `0x2103` — Room player list update (bulk)

**Direction**: incoming.

**Payload**: `payload[0]` (a `byte`), the number of players in the room.
Followed by that many per-player entries, each containing a name string and
flags/stats fields.

**Behavior**: populates a per-slot array up to `payload[0]` entries. This is
the **bulk** version of a player-record update — six related fields
(display buffer, and five smaller stat fields) all get written for every
slot in one pass. The exact same six fields are individually update-able one
field at a time via opcodes `0x21f2` through `0x21f7` (below) — `0x2103` is
the "sync everything for the whole room" variant, used e.g. right after
joining a room, while the `0x21fX` family are incremental single-field
updates sent as things change during normal room membership.

**Significance**: this is the fundamental **room player list** — what
populates the UI list of who's currently in the game room, with their
names/stats/ready-status. See "Confirmed recurring structures" below for the
exact field offsets, which are shared with the `0x21fX` family.

#### Opcode `0x2105` — Player info/profile broadcast

**Direction**: incoming.

**Payload**: `payload[1]` (a `byte`, a length prefix), followed by a string
of that length, followed by several small additional fields.

**Behavior**: the string and trailing fields are copied into a per-slot
**0x80-byte (128-byte) display buffer** (`base + slot*0x80`), where the
target slot comes from a client-side field at `this+0x124` (a "which slot am
I currently updating" cursor set by a preceding opcode). The same content is
also mirrored into local instance fields (`this+300`, `this+0x1ac`,
`this+0x1b0`).

**Significance**: broadcasts one player's info/profile (name plus a handful
of stat bytes) to be displayed in that player's row of the room list.
Companion opcode `0x21f0` (below) writes to the exact same 0x80-byte buffer
via a slightly different trigger path (a "find my own slot" lookup rather
than a pre-set cursor field) — likely the same underlying data, reached via
two different code paths depending on whether the update is for this client
or another player.

#### Opcode `0x2111` — Invite-based room join (tentative)

**Direction**: incoming.

**Behavior**: first checks two "team full"-style boolean flags on the
handler's own instance (`this+0xd` and `this+0xe`), dispatching to
`FUN_00429fb0`/`FUN_00429f90` respectively if set. Then, on
`payload[0]==0`, performs a player-join-setup sequence that is **near-
identical** to opcode `0x2121`'s join-setup body, but reads its input fields
from different payload offsets (`payload[1]` through `payload[3]`, versus
`0x2121`'s own offset scheme).

**Significance**: given the near-duplicate join-setup logic paired with
distinct team-capacity pre-checks, the most plausible interpretation is that
this is the **invited-join** variant of joining a room (e.g. accepting a
buddy/friend invite directly into a specific team slot, which needs the
team-full check that a normal walk-up join via `0x2121` doesn't), as opposed
to `0x2121`'s regular/browse-and-join path. Not proven — flagged as
tentative in the original analysis.

#### Opcode `0x2121` — Room join confirmation / player-slot initialization

**Direction**: incoming.

**Payload**: `payload[0]`, checked for `== 0`.

**Behavior** (on the `payload[0]==0` path): increments a per-room counter at
`+0x4739c`; sets a status/mode byte at `this+0x115` to `2`; copies this
client's own display name into a persistent buffer; resets several
weapon-slot-related fields to the sentinel value `0xff` (indicating "no
weapon equipped yet" / freshly-initialized slot).

**Significance**: this is the **"you have joined/been assigned to this
room" confirmation** — the moment a client's local player-slot state gets
properly initialized after entering a game room. The weapon-slot sentinel
reset (`0xff`) is notable: it confirms weapon slots are tracked as
byte-sized fields where `0xff` means "empty," a detail useful for future
struct reconstruction.

#### Opcode `0x21f0` — Player display buffer update (companion write path)

**Direction**: incoming.

**Payload**: `payload[1]` (a `byte` length prefix) followed by a string of
that length.

**Behavior**: writes into the **same 0x80-byte per-slot display buffer** as
opcode `0x2105`, but the target slot is resolved via `FUN_0041c290()` (a
"find my own slot index" lookup), gated so the write only happens if that
lookup succeeds (returns something other than `-1`).

**Significance**: a companion write path to `0x2105` for the same buffer,
apparently used when the *client itself* is the subject of the update
(hence looking up "my own slot" rather than using a pre-set target-slot
cursor field). The distinction between `0x2105` and `0x21f0` is one of the
few places in this protocol where the same data has two different opcodes
depending on whose data is being updated (self vs. other).

#### Opcode `0x21f1` — Player left the room

**Direction**: incoming.

**Payload**: `*payload`, a player/entity ID.

**Behavior**: searches the room's player-ID array (at `+0x44664`, sized
according to the room's player-count field at `+0x44648`) for a match
against `*payload`. On a match at index `idx`: if `idx` equals this
client's own cached slot index (`this+4`), that cache is reset to `-1`
(meaning "I am no longer tracked at a known slot" — relevant if the
departing player *was* this client, e.g. self-initiated leave being echoed
back). Regardless, the matched slot's player-count-tracking field
(`+0x4464c + idx*4`) is cleared to `0`.

**Significance**: the **player-left-the-room** notification — removes a
departed player from the local room-membership tracking.

#### Opcode `0x21f2` — Per-field update: display buffer

**Direction**: incoming.

**Payload**: `payload[1..]`, a variable-length byte run of `payloadLen - 2`
bytes.

**Behavior**: resolves the target slot via `FUN_0041c290()` (find-my-slot);
if resolved, first checks whether that slot equals the client's cached slot
index (resetting the cache to `-1` if so — same pattern as `0x21f1`), then
writes the variable-length payload data into the **same 0x80-byte per-slot
display buffer** used by `0x2105`/`0x21f0`.

**Significance**: this is one of a clean family of six near-identical
opcodes (`0x21f2` through `0x21f7`) that each update **one individual field**
of the per-slot player record, as opposed to `0x2103`'s bulk all-at-once
update. All six share the identical slot-resolution and cache-invalidation
prologue, differing only in which field they write and the field's size.
See the note at the end of the `0x21f2`-`0x21f7` group below, and the
"Confirmed recurring structures" table, for how these line up exactly with
`0x2103`'s bulk-update field layout.

#### Opcode `0x21f3` — Per-field update: single byte at `+0x4497c`

**Direction**: incoming.

**Payload**: `payload[1]`, a single `byte`.

**Behavior**: same slot-resolution/cache-invalidation prologue as `0x21f2`,
then writes the byte into a per-slot array at offset `+0x4497c` from the
room base — this is the exact same field that `0x2103`'s bulk update
populates for every slot in one pass.

#### Opcode `0x21f4` — Per-field update: 4-byte value at `+0x44984`

**Direction**: incoming.

**Payload**: `payload[1]`, a `uint` (4 bytes).

**Behavior**: same prologue as `0x21f3`; writes the `uint` into a per-slot
array at `+0x44984` — again, the same field `0x2103` bulk-populates.

#### Opcode `0x21f5` — Per-field update: single byte at `+0x4499c`

**Direction**: incoming.

**Payload**: `payload[1]`, a single `byte`.

**Behavior**: same prologue; writes into per-slot array `+0x4499c`.

#### Opcode `0x21f6` — Per-field update: single byte at `+0x449a2`

**Direction**: incoming.

**Payload**: `payload[1]`, a single `byte`.

**Behavior**: same prologue; writes into per-slot array `+0x449a2`.

#### Opcode `0x21f7` — Per-field update: single byte at `+0x449a8`

**Direction**: incoming.

**Payload**: `payload[1]`, a single `byte`.

**Behavior**: same prologue; writes into per-slot array `+0x449a8`. This is
the last opcode in the systematic `0x21f2`-`0x21f7` family observed in this
handler (there may logically be a corresponding `0x21f8` for the final
`+0x449ae` field that `0x2103` also populates in bulk, but no such opcode
branch was found in this function — that sixth field may only ever be
updated via the bulk `0x2103` path, not incrementally).

**Group note on `0x21f2`–`0x21f7`**: this is a clean, systematic family —
six individual per-field update opcodes, one per stat field that `0x2103`'s
bulk player-list update populates all at once. All six resolve the target
slot identically (`FUN_0041c290()`) and clear the "my slot" cache field
identically before writing, differing only in which field and how many
bytes. This confirms the per-slot player record has (at least) six
independently-syncable fields beyond the display-name buffer, and gives a
concrete anchor for reconstructing the full record layout (see "Confirmed
recurring structures").

#### Opcode `0x6001` — Room → Avatar Store transition

**Direction**: incoming.

**Payload**: `payload[1]` through `payload[5]` — four `uint` fields — followed
by a variable-length section of per-"player" 3-byte tuples, where each
tuple's values are derived using `rand()` calls (a seed or roll-generation
step, not simply copied from the wire).

**Behavior**: unpacks the four `uint` fields (pushed through the outgoing
encode-helper functions — `QueueOutgoingPacketField`/
`EncodeOutgoingPacketField` — meaning this data also gets forwarded/relayed
onward, not just consumed locally), then builds the per-player tuple array,
and finally calls `ChangeGameState(7)`.

**Significance**: `ChangeGameState(7)` transitions to **State 7, the Avatar
Store**. Despite the opcode's numeric proximity to gameplay-sounding codes,
its actual effect is entering the shop screen — earlier analysis passes
initially (incorrectly) guessed this was a "room → game" transition before
the state-identity work (via resource-string matching) confirmed state 7 is
specifically the Avatar Store.

#### (Shared fallthrough, not a single opcode) — Room → Ready Room transition

**Direction**: incoming.

**Behavior**: sums per-slot equipped-item stat bonuses across a 20-element
array with a `0x224`-byte stride (the confirmed player-game-slot size, used
here for a different purpose than the 8-element In-Battle player array —
this loop's 20-element extent suggests it may cover a superset including
non-active/reserve slots), resets the game viewport to `(0, 0, 799, 599)`
(the fixed 800×600 play area confirmed everywhere else in this codebase),
then calls `ChangeGameState(9)`.

**Significance**: `ChangeGameState(9)` transitions to **State 9, the Ready
Room** — this is the actual "room → pre-battle" transition (as opposed to
`0x6001` above, which goes to the store). **Confirmed via a full
re-decompile and exhaustive opcode-comparison trace: there is no single
dedicated opcode value here.** `State03_GameRoomList_ProcessPacket` is a
long if-else-if cascade (plus one `switch(opcode)` block for
`0x21f2`-`0x21f7` that always returns early); every opcode it individually
recognizes (`0x6001`, `0x21f0`-`0x21f7`, `0x2001`, `0x201f`, `0x2103`,
`0x2105`, `0x2111`, `0x2121`) returns from its own branch, and this
Room→Ready-Room code is the **shared fallthrough** reached when none of
those match — labeled `switchD_00428058_default` in the decompiler output.
This isn't a documentation gap where a number was lost; there genuinely
isn't one opcode to cite. Whatever gates this in practice (presumably the
server only sends a not-otherwise-handled opcode at the intended moment)
isn't visible from this function alone — see the "remaining depth" list
below.

---

### State 7 — Avatar Store / Shop (`State07_AvatarStore_ProcessPacket`, `0x4440c0`)

#### Opcode `0x2001` — Room-to-store transition unpack

**Direction**: incoming.

**Payload**: `*payload`, checked `== 0`.

**Behavior**: on the `*payload==0` path, unpacks four `uint` fields via
`FUN_0040a470` (the same outgoing-field-queuing helper seen throughout —
i.e. this data gets forwarded, not just read), and if `payloadLen > 0xe`,
one additional field is unpacked.

**Significance**: mirrors State 3's `0x6001` unpack pattern from the
receiving side — this is the store screen's half of the room→store
transition handshake. Same opcode number (`0x2001`) as State 3's, State 9's,
and State 11's "generic cleanup" opcodes, but implements entirely different
(store-specific) logic here.

#### Opcode `0x600f` — Request inventory (outgoing)

**Direction**: outgoing, triggered locally on entering the store.

**Behavior**: sends opcode `0x6000` with an empty payload.

**Significance**: the client's "give me my inventory" request, sent
immediately upon entering the Avatar Store — the server presumably replies
with one or more `0x6002` packets (below) listing owned items.

#### Opcode `0x6002` — Owned-item inventory list

**Direction**: incoming.

**Payload**: per-entry: four `uint` id fields, a `time_t` (4-byte Unix-style
timestamp, parsed via `localtime()` into day/month/year components — an
**expiration date**), and a variable-length trailing blob.

**Behavior**: each parsed entry is stored into a confirmed **156-byte
(`0x9c`) item struct array** at offset `+0x44be8` from the store object
base.

**Significance**: this is the **owned/purchased item inventory list** shown
in the avatar store — each item has an expiration date (many avatar/cosmetic
items in games like this are time-limited rentals rather than permanent
purchases), confirming the store supports rental-style items. See
[FILEFORMATS.md](FILEFORMATS.md) and "Confirmed recurring structures" for
the 156-byte struct.

#### Opcode `0x6005` — Store init / price-list population

**Direction**: incoming.

**Payload**: `*payload`, checked `== 0`.

**Behavior**: on the `*payload==0` path (further gated on two additional
instance flag bytes at `this+0x30bb8`/`this+0x30bb9`), populates a `short`
array with per-item prices, reading from a global item-data table with a
`0x224`-byte stride, for up to 4 entries (loop bound `0x890 / 0x224 ≈ 4`).
If instead the second flag byte is set, the handler sends a leave packet
(`0x2000`/`0xffff`) rather than populating prices; if the *first* flag byte
is set, it instead sets `g_pendingGameState = 0xf` (quit) directly.
Regardless of which path is taken, the store's price-filter min/max fields
(`this+0x32f94`/`this+0x32f98`) are reset to sentinel values
(`0x80000000`/`0x7fffffff` respectively — i.e. "no filter applied yet," the
widest possible numeric range) and a filter-active flag
(`this+0x32f92`) is cleared.

**Significance**: this looks like a multi-purpose "entering/leaving the
store" bookkeeping opcode: normally populates the price list for display,
but two flag bytes can redirect it into a leave or quit path instead —
likely these flags are set by some other part of the client (e.g. the user
clicked "back" or "exit game" while this packet was in flight) so the
handler can react appropriately to stale/overtaken UI state rather than
blindly populating a screen the user has already navigated away from.

#### Opcode `0x6017` (sub-case `*payload==0`) — Purchase confirmation dialog

**Direction**: incoming.

**Payload**: `*payload`, checked `== 0` for this sub-case.

**Behavior**: loads four localized strings by resource id
(`0xea6a` through `0xea6d`, via the string-table lookup helper
`FUN_0043dc70`), formats an item name and price into them via `sprintf`,
and shows a **`b_storewindow_confirm`** popup image with the formatted text.

**Significance**: the **"are you sure you want to buy this?"** confirmation
dialog that appears before a purchase is committed.

#### Opcode `0x6017` (sub-case `*payload==0x6003`) — Purchase confirmation response

**Direction**: incoming.

**Behavior**: sends an outgoing `0x6000` packet (empty payload) — the same
opcode used for the initial inventory request, reused here as a generic
"acknowledge" response.

**Significance**: the confirmation dialog's "yes, proceed" response being
relayed back to the server.

#### Opcode `0x6027` — No-op scheduling checkpoint

**Direction**: — (present in the dispatch structure but has no executable
handler body).

**Behavior**: the `if (opcode != 0x6027) { ... }` guard means that when
`opcode == 0x6027`, the entire nested branch block is skipped — there is
**zero logic** attached to this opcode value in this function.

**Significance**: this matches the exact same "no-op scheduling checkpoint"
pattern found for Channel 2's `0xc400` in the In-Battle handler — a named
opcode that exists purely as a timing/ordering marker in some broader
sequence, with no payload-processing responsibility of its own in this
particular handler.

#### Opcode `0x6037` (sub-case `*payload==0`) — Purchase commit

**Direction**: incoming.

**Payload**: `*payload`, checked `== 0`.

**Behavior**: reads a target-slot index from `this+0x3054c`, bounds-checks
it against a global slot-count limit (`DAT_005b3484 + 0x44e24`) and
**fatal-errors the process** via `FUN_004010c0(0x80070057)` if the slot
index is out of range (`0x80070057` is the Win32 `E_INVALIDARG` HRESULT
value, used here as a hard-failure/assert code rather than a recoverable
error — suggesting this "should never happen" in normal play and is treated
as a client-side integrity violation if it does). If the bounds check
passes: calls `FUN_0044c370()` (the actual purchase-commit logic — not
traced further), then `FUN_0044c6a0()` (refreshes the store display), then
enters a loop with a `switch` on a local index variable (`local_520`,
values `0`/`1`/`2`/`3` seen) selecting between what appear to be different
purchase-outcome response codes (success / insufficient funds / item
unavailable / etc. — the individual cases' distinguishing logic largely
converges to the same `AddToPacketChecksum`-style relay regardless of case,
so the *distinct* meaning per case number wasn't cleanly isolated).

**Significance**: this is the actual **purchase commit** — the point where
buying an item is finalized against the player's currency/inventory, after
the `0x6017` confirmation dialog has been accepted.

---

### State 9 — Ready Room (`State09_ReadyRoom_ProcessPacket`, `0x4d38c0`)

Opcodes in this handler cluster into `0x30xx`/`0x31xx`/`0x32xx`/`0x34xx`/
`0x44xx` ranges. Most branches record a **replay event** via
`Replay_AppendEvent` alongside their normal effect (see
[ARCHITECTURE.md](ARCHITECTURE.md)'s replay-recording-system section for the
full event-code table and how the replay/live-network paths converge on the
same event codes).

#### Opcode `0x2001` — Leave ready room

**Direction**: incoming.

**Payload**: `payload`, checked `== 0`.

**Behavior**: on `payload==0`, checks a global flag (`DAT_00793522`); if set,
force-exits **State 11 (In-Battle)** by directly invoking its vtable
exit-hook (`g_gameStateObjects[0xb]->vtable[+0x20]()`) — i.e. this opcode
can tear down an in-progress battle from the ready-room handler's context.
Then sets `g_pendingGameState = 3` (back to the Game Room List).

**Significance**: the **"leave the ready room"** action, with a safety net
that also cleans up a lingering battle state if one exists. This is the
opcode that led to discovering that `ChangeGameState` transitions can be
triggered indirectly (calling another state's exit-hook directly rather than
going through the normal `ChangeGameState` dispatcher) as a cleanup
mechanism.

#### Opcode `0x3010` — Match-start replay snapshot + team-based spawn setup (corrected)

**Direction**: incoming.

**Payload**: `payload[0]`, a `byte` (a player slot ID, or `-1` for "this is
the local client").

**Behavior, re-decompiled and corrected — this is not character/team
selection.** `FUN_004dc200(byteValue)` almost entirely ignores its
argument (only checked once, at the very end, to decide `-1` = flush the
replay log immediately vs. a real slot = call `FUN_004e7140()` instead) —
the bulk of the function logs a **replay event `0x8400`**: it peeks the
current packet-checksum state repeatedly and copies a snapshot of fields
at `+0x23320`-`+0x23338` (position/camera-shaped data) plus **the same
20-element, `0x224`-stride double loop already found elsewhere in this
codebase** (the room-list stat-summing loop from the Room→Ready-Room
transition) into the replay buffer. This is a **state-snapshot/logging
step**, not a selection packet.

`FUN_004dc5c0(slot)`, the finalizer, reads a per-slot ushort at
`+0x458bc+slot*8` and tests its high bit (`&0x8000`) to pick between two
sets of coordinate-override fields (a second per-side array, with `-1`
sentinels falling back to the per-slot defaults at `+0x458be`/`+0x458c0`/
`+0x458c2`), then calls `FUN_004141b0(x, y, ..., 0, slot+200000,
slot+300000)` — reads as **team-side-based spawn position/camera setup**
(the high bit is very likely the team-side flag, selecting which of two
coordinate sets a player's camera/position uses), not a UI selection
confirmation.

**Significance**: corrects the earlier "character/team selection"
hypothesis, which came from context (Ready Room screen) rather than
tracing what the handler actually does. The real behavior is a
match-start bookkeeping step: log a full state snapshot to the replay,
then position each player's camera/spawn based on their already-assigned
team side. Actual character/weapon selection is confirmed elsewhere as
action `0x8100`/`0x8400` on Channel 2 (see the `ProcessBattleAction`
section), not this opcode.

#### Opcode `0x3020` — Simple ready/unready toggle

**Direction**: incoming.

**Behavior**: calls `FUN_004db720()` with no further payload processing
beyond that call.

**Significance**: appears to be a simpler variant of a ready-status toggle,
distinguished from `0x3010` by doing no additional per-payload field
handling.

#### Opcode `0x3105` — Player joined ready room

**Direction**: incoming.

**Behavior**: records a replay event — `0x8102` if the joining player is
this client itself, or `0x8000` plus an id and position field if it's
another player — then sends a `SendMessageA(hwnd, 0xc5, ...)` Windows
message, presumably to trigger a UI refresh/notification of the new
arrival.

**Significance**: the **player-joined-the-ready-room** notification,
confirmed to log distinctly different replay events depending on whether
the joining player is the local client or a remote peer.

#### Opcode `0x3151` — Team change (tentative)

**Direction**: incoming.

**Payload**: `payload[2]`, a `byte`.

**Behavior**: records replay event `0x8200` with the byte value.

**Significance**: tentatively a team-change notification — inferred from
the surrounding opcode cluster's apparent theme (character/team/map/ready
selection) rather than proven via an explicit string reference.

#### Opcode `0x3201` — Weapon/character selection change (tentative)

**Direction**: incoming.

**Behavior**: reads two byte fields from the handler's own instance data,
records replay event `0x8100`.

**Significance**: tentatively a weapon-loadout or character-selection
change notification, by the same cluster-context reasoning as `0x3151`.
Note that replay event `0x8100` is also the action code confirmed (with
much higher confidence) on Channel 2 as **"character/mobile model sync"** —
the alignment between this opcode's replay event and that confirmed
Channel 2 action supports the character-selection interpretation.

#### Opcode `0x3211` — Map vote/selection (tentative)

**Direction**: incoming.

**Behavior**: records replay event `0x8101`.

**Significance**: tentatively a map vote or map-selection notification.
Replay event `0x8101` is also confirmed (independently, with higher
confidence) as Channel 2's **"map selection sync"** action, again lending
support to this interpretation via the shared event-code namespace between
the replay log and the live Channel 2 protocol.

#### Opcode `0x3231` — Ready-status toggle confirmation

**Direction**: incoming.

**Behavior**: records replay event `0x8102`.

**Significance**: the confirmed ready-status toggle path (event `0x8102` is
also seen for `0x3105`'s self-join case above, and is confirmed on Channel 2
as part of the ready-status flow too — this event code appears to be
overloaded/reused for more than one "ready room state changed" trigger, not
a single unambiguous meaning).

#### Opcode `0x3233` — Match/session status change

**Direction**: incoming.

**Payload**: `*payload`, checked non-zero vs. zero.

**Behavior**: if `*payload != 0`: sends the leave packet (`0x2000`/`0xffff`)
to the server. If `*payload == 0`: force-exits In-Battle's exit-hook (same
mechanism as opcode `0x2001` above), sets `g_pendingGameState = 9` (i.e.
**stays** in the Ready Room rather than transitioning elsewhere), and
records replay event `0x8103`.

**Significance**: appears to be a **"battle just ended, return to ready
room"** notification — the non-zero payload case looks like an error/abort
path (leave entirely) while the zero-payload case is the normal
"match concluded, come back to the ready room" flow. Compare with State 11's
own `0x3233` handler, which does the analogous transition from the *battle's*
side (see below).

#### Opcode `0x3400` — Ready-status button refresh

**Direction**: incoming.

**Behavior**: checks room-ownership (via `FUN_0040b390`) and shows either the
**`b_ready_ready`** button image (non-owner) or the **`b_ready_startgame`**
button image (room owner) accordingly.

**Significance**: confirms the ready room has **two different primary
action buttons** depending on whether the local client is the room owner —
regular participants see a "Ready" toggle button, while the room owner sees
a "Start Game" button instead (since only the owner can initiate the match
start countdown — see Channel 2's `0x9002` action below, which does exactly
that).

#### Opcode `0x3431` — Ready confirmation (shared tail)

**Direction**: incoming.

**Behavior**: falls through to a shared "confirm ready" call
(`FUN_004da460(this, 1, uVar11)`), the same tail code reached by opcodes
`0x3151`/`0x3201`/`0x3211` above via their own `goto` paths.

**Significance**: functionally another entry point into the same
confirm-ready mechanism used by the character/team/map-selection opcodes —
suggests this opcode may represent a generic "selection confirmed" signal
distinct from the more specific `0x3151`/`0x3201`/`0x3211` triggers, but
converging on the same underlying confirmation logic.

#### Opcode `0x3432` — Stop replay recording

**Direction**: incoming.

**Behavior**: closes the currently-open replay file (`fclose`) if one is
open.

**Significance**: marks the **end of the recorded session** — closes out
the `.sv` replay file. See State 11's `0x3233` handler, which writes a
terminator byte to the replay file and closes it from the battle side; this
`0x3432` handler is the Ready Room's equivalent bookend for sessions that
end while still in (or having returned to) the ready room rather than mid-
battle.

#### Opcode `0x3fff` — Leave/cancel notification (outgoing)

**Direction**: outgoing.

**Behavior**: sends opcode `0x2000` with payload `0xffff`.

**Significance**: a generic **leave/cancel** notification to the server —
this exact `0x2000`/`0xffff` outgoing packet shape recurs across State 9's,
State 11's, and other handlers' leave-related paths, suggesting `0x2000` is
a protocol-wide "I am leaving this context" opcode, parameterized by the
`0xffff` sentinel payload value (as opposed to other values of that same
opcode meaning something else in other contexts — not independently
confirmed, but the repeated identical shape strongly suggests a shared
"leave" convention).

#### Opcode `0x4410` — Server keepalive/ping acknowledgment

**Direction**: incoming, conditionally replied to.

**Behavior**: only acted upon if the client is not already in the process of
leaving (`g_pendingGameState != 3` check at the call site); if so, replies
with outgoing opcode `0x3232`.

**Significance**: a **server keepalive/ping** — the client acknowledges with
`0x3232` unless it's already tearing down its ready-room session, in which
case the ping goes unanswered (a sensible guard against replying to
keepalives during teardown).

---

### State 11 — In-Battle (`State11_InBattle_ProcessPacket`, `0x4b4100`)

This handler is mostly disconnect/leave/end-of-match **administration** —
the actual real-time gameplay actions (movement, aiming, firing, chat, turn
sequencing) live on **Channel 2** (`ProcessBattleAction`, documented further
below), not here. This is one of the clearer illustrations of the two-
channel split: Channel 1 handles the slower, reliable "session state"
concerns even during battle, while Channel 2 handles the fast-moving
real-time action stream.

#### Opcode `0x2001` — Leave battle

**Direction**: incoming.

**Payload**: `payload`, checked `== 0`.

**Behavior**: on `payload==0`, sets `g_pendingGameState = 3` (Game Room
List).

**Significance**: the battle-side **"leave the match"** action.

#### Opcode `0x3020` — Player disconnected mid-match

**Direction**: incoming.

**Behavior**: decompiled in full this pass. Two separate data structures are
touched, in sequence:

1. **Shift-compacts the active-slot arrays**: finds the disconnecting
   player's slot by scanning `this+0xca0` (the same array action `0x8408`
   populates at index `+0x328`) for the player's ID, then — if it's not
   already the last active slot — shifts **three** of the four parallel
   arrays down by one slot in a single combined loop: `+0x8a0` (index
   `+0x228`), `+0xaa0` (index `+0x2a8`), and `+0xca0` (index `+0x328`)
   itself. Notably, the fourth spawn array (`+0xea0`/index `+0x3a8`) is
   **not** touched by this shift loop — either it doesn't need
   compacting for this operation or it's handled elsewhere (not traced).
   The active-slot counter at `this+0x89c` (same counter as `0x8408`'s
   `this+0x227`) is decremented afterward.
2. **Reads that player's packet-checksum state**: `playerId * 0x224 +
   0xebef4`, passed to `FUN_0040a4d0` — traced further this pass:
   `FUN_0040a4d0` is a trivial critical-section wrapper around
   `PeekPacketChecksumState`, and a whole-binary scan for every instruction
   referencing the `0xebef4` constant (34 hits across ~15 functions)
   confirms this array is consistently used the same way everywhere it
   appears — this is an **array of per-player packet-checksum-state
   instances**, not gameplay data. `0x3020` reads the disconnecting
   player's checksum state here, presumably as part of validating/flushing
   its final packets before removal.

Also records a replay event (`0x307`) capturing the departed player's final
stats, and — if the departed player held the currently-active turn —
reassigns the active turn to the next player via `FUN_00413bf0` (tentatively
"AdvanceTurn").

**Significance**: this is the mechanism that keeps the game playable when a
player disconnects mid-match rather than the game hanging waiting for a
turn that will never come. Confirms the active-slot arrays are genuinely a
dense, shift-compacted list (not a sparse array with "empty" markers) —
departed players are physically removed and everyone after them shifts
down. Also clarifies (correcting an earlier pass's speculation) that
GunBound tracks **per-player packet-checksum state as a genuine array**,
one instance per player, alongside the unrelated slot-position arrays used
for battle/spawn data.

#### Opcode `0x3233` — Match ends → return to Ready Room

**Direction**: incoming.

**Behavior**: sets `g_pendingGameState = 9` (Ready Room), writes a
terminator byte (value `2`) to the currently-open replay file, then closes
that file.

**Significance**: the battle-side counterpart to State 9's own `0x3233`
handler (above) — this is the transition that fires when the match
concludes and everyone returns to the ready room, from the perspective of
the code that's actually running *during* the battle. The terminator byte
written to the replay file (`2`) is a concrete anchor for reconstructing the
`.sv` file format's end-of-stream marker convention (see
[FILEFORMATS.md](FILEFORMATS.md)).

#### Opcode `0x3400` — End-of-match scoreboard/ranking sync (tentative)

**Direction**: incoming.

**Behavior**: iterates all **16 slots** (notably *not* just the 8 active
player slots — the extra 8 are presumably reserved/spectator/inactive
slots), logging a replay event `0xc302` for each slot along with a stat
value read from `+0xeba98`; slot index 14 specifically gets one extra field
via a call to `FUN_0045d360`. Also force-advances the turn state if a
"match over" flag is already set, before doing the per-slot loop.

**Significance**: tentatively the **end-of-match scoreboard/ranking sync** —
the 16-slot iteration (double the active player count) is notable and
unexplained; possibly the extra 8 slots represent historical/eliminated
players who need their final stats included in the match summary even
though they're no longer in the active 8-slot array (consistent with
`0x3020`'s disconnect-handling shifting players *out* of the active array —
those departed players' data might be preserved elsewhere for the final
scoreboard).

#### Opcode `0x3fff` — Leave/cancel notification (outgoing)

**Direction**: outgoing.

**Behavior**: identical shape to State 9's `0x3fff` — sends `0x2000` with
payload `0xffff`.

#### Opcode `0x4102` — Companion disconnect-notification path

**Direction**: incoming.

**Behavior**: checks a bitmask (`& 0xf000`) against a value; if the masked
bits are set, logs replay event `0x8500` capturing player stats (a position
field and a cooldown flag) before performing cleanup.

**Significance**: appears to be a second, related disconnect/leave
notification path alongside `0x3020` — possibly distinguishing between
different *reasons* for a player leaving (e.g. a graceful quit vs. a
timeout/AFK-kick, given the bitmask-gated special handling), though the
exact distinction between when `0x3020` fires versus `0x4102` wasn't
independently resolved.

#### Opcode `0x4410` — (fallthrough, no distinct handling)

**Direction**: incoming (in the sense that the dispatch reaches this value,
though no unique logic executes for it specifically in this handler).

**Behavior**: control falls through this opcode value directly into the
`0x4413` check immediately below it — there's no code that runs
specifically and only for `0x4410` in this function; the value is only
meaningful in that it doesn't *prevent* reaching the `0x4413` check.

#### Opcode `0x4413` — End of match / show results screen

**Direction**: incoming.

**Behavior**: clears all 8 player slots (calls a per-slot cleanup helper,
`FUN_00405fb0`, eight times — once per slot), sets a "match over" flag
(`this+0x474 = 1`), and shows the **`b_result_confirm`** results-screen
image.

**Significance**: this is the definitive **end-of-match trigger** — the
point where the battle concludes and the results/scoreboard screen is
displayed to the player, before the eventual transition back to the Ready
Room (via `0x3233` above).

---

## Channel 2 — `ProcessBattleAction`, by screen

Recall from the header section above: every action on this channel is
preceded by the fixed 33-byte header (`+0x02` action type as a `ushort`,
`+0x05` source player slot as a `byte`, `+0x21` payload start).

### State 10 — Loading (`State10_Loading_ProcessBattleAction`, `0x43e440`)

Confirmed as a genuinely-implemented (non-no-op) override — one of only
three states (Loading, Ready Room, In-Battle) that implement this channel at
all; every other state uses the shared no-op for this vtable slot.

#### Action `3` — Generic notification toast

**Direction**: incoming.

**Behavior**: calls the `ShowMessage`-style virtual method (`this`'s own
vtable `+0x28`) with a formatted string built from the packet's data.

**Significance**: this exact action-code-3-means-"show a toast message"
pattern recurs identically across every Channel 2 handler examined
(Loading, Ready Room, In-Battle) — it's effectively a shared/universal
action within this channel, not screen-specific behavior.

#### Action `0xc301` — Turn-timer + battle setup data write

**Direction**: incoming.

**Behavior**: writes the confirmed **turn-timer field** at offset `+0x10a4`
— notably, **on the In-Battle state's object** (`g_gameStateObjects[0xb]`),
even though this code is executing from the *Loading* screen's handler, i.e.
this is a genuine **cross-state data write**, populating battle-setup state
before the In-Battle state object is even the currently-active game state.
The written value is checked against the sentinels `60000` and `0xffff`
(60,000 milliseconds = the classic GunBound 60-second turn time limit).
Also copies an 8-element array (16 bytes, shorts) into `+0x2302` on the same
In-Battle object — likely wind direction and/or spawn-position data for the
upcoming match. Additionally performs a per-player sound-profile selection,
choosing between `"normal"` and `"wnormal"` (weighted/heavy?) character
audio profiles based on a lookup.

**Significance**: this is the mechanism by which the Loading screen
pre-populates battle configuration — confirming the client's state-machine
design allows writing into a not-yet-active state's object fields directly,
rather than requiring the target state to be active first. This same action
code (`0xc301`) and the identical field-writing logic is also implemented in
State 11's own handler (see below) — the two are a shared code path
triggered from whichever screen happens to be active when this action
arrives, which given the confirmed cross-state write is presumably received
at least once during Loading and possibly again during actual battle for
mid-match wind updates (compare action `0xc308` below, which updates the
same array without the turn-timer re-write).

---

### State 9 — Ready Room (`State09_ReadyRoom_ProcessBattleAction`, `0x4d4ea0`)

Fully mapped. This channel handles per-slot **visual/status synchronization**
for everyone currently in the ready room — character/mobile model choices,
ready flags, map selection, and room-owner kicks. This is a genuinely
separate, real-time-ish sync layer distinct from Channel 1's more
event-oriented opcodes for the same screen.

#### Action `1` — Player data buffer load

**Direction**: incoming.

**Behavior**: copies up to 255 bytes of the action's payload into a
per-slot buffer, then sets a "loaded"-style flag at
`this + slot*8 + 0x700 + 0x8c8 = 1`.

**Significance**: likely a generic "this player's data blob has finished
loading/arriving" marker, gating some other logic on the flag being set
before proceeding (e.g. not rendering a character model until its
associated data buffer has actually arrived).

#### Action `3` — Generic notification toast

**Direction**: incoming.

**Behavior**: identical `ShowMessage`-virtual-call pattern as every other
Channel 2 handler's action `3`.

#### Action `0x8000` — Full player-info sync

**Direction**: incoming. Two overlapping code branches handle this: one for
`uVar2 > 0x8000` (a broader numeric range check) and one for the exact
match `uVar2 == 0x8000` (which does additional work on top of the shared
logic).

**Behavior**: reads a per-room byte at `+0x45124` and applies it via
`FUN_004daa60`. The exact-match (`==0x8000`) case additionally copies
weapon-slot byte fields, two viewport-adjacent 4-byte fields
(`+0x457a1`/`+0x457a5`), and this client's own name string, then triggers a
UI refresh via `FUN_004db920()` followed by `FUN_004dbd50(this, 1)`.

**Significance**: this is the Ready Room's **Channel 2 counterpart** to
Channel 1's `0x2121` "you joined this room" sync opcode — a full,
comprehensive push of one player's complete info (name, weapon loadout,
some viewport-related state) rather than an incremental single-field
update.

#### Action `0x8003` — Chat/name buffer update

**Direction**: incoming.

**Behavior**: copies a string from the payload (up to `packetLen - 1` bytes)
into a shared name/chat buffer at offset `+0x44e64`.

**Significance**: likely feeds a shared display buffer used for either chat
text or a currently-displayed player name — the exact usage context (chat
message vs. name label) wasn't independently disambiguated from the write
alone.

#### Action `0x8004` — UI refresh trigger

**Direction**: incoming.

**Behavior**: calls `FUN_004dbd50(this, 1)` and nothing else.

**Significance**: a bare UI-refresh trigger, presumably called after some
other state change (possibly related to the preceding `0x8003` buffer
update) to force the ready-room screen to redraw with current data.

#### Action `0x8100` — Character/mobile model sync

**Direction**: incoming.

**Behavior**: reads a per-slot mobile-type byte at `+0x458fc`. If the value
is invalid (`-1` or greater than `0x10`), applies the default "rider"
(unselected-character) texture. Otherwise, formats the string `tank_%d`
using the mobile-type value and applies the resulting texture to **two
sub-objects per slot** — `this + slot*8 + 0x6fc` and `this + slot*8 + 0x700`
— which most plausibly represent a body sprite and a separate
weapon/turret sprite for the same character model (a common 2D-sprite
technique: torso and turret rendered/rotated as two independent layered
sprites).

**Significance**: this is what makes the character preview in the ready
room actually show the chosen character model, confirmed to use the exact
same texture-naming convention (`tank_%d`, `"rider"` for unselected) as the
in-battle rendering system documented in ARCHITECTURE.md.

#### Action `0x8101` — Map selection sync

**Direction**: incoming.

**Behavior**: writes a byte at `this+0x25b` into a global "current map"
field, normalizing the sentinel value `-1` to `0`. Confirms ready status via
`FUN_004da460(this, 1, 0)`, then re-initializes map-dependent state by
calling `FUN_00415ce0`, `FUN_004db570`, and `FUN_004db720` in sequence.

**Significance**: the mechanism by which selecting/voting for a map in the
ready room actually updates the shared "which map is selected" global and
kicks off whatever map-dependent re-initialization is needed (likely
refreshing a map-preview thumbnail or map-specific UI elements).

#### Action `0x8102` — All-players-ready flag

**Direction**: incoming.

**Behavior**: sets a boolean field at `this+0x4cc` to the result of
`payload[0] == 3`, then confirms ready status via the same
`FUN_004da460(this, 1, 0)` call used by `0x8101`.

**Significance**: tracks whether all players in the room have signaled
ready — the specific comparison against the literal value `3` (rather than
a simple non-zero check) suggests the incoming payload byte is itself a
small status enum where `3` specifically means "all ready," not a plain
boolean.

#### Action `0x8104` — Show match-result confirmation button

**Direction**: incoming.

**Behavior**: calls `CreateButtonWidget` to display the
`b_result_confirm.img` button (via the generic UI widget system documented
in [ARCHITECTURE.md](ARCHITECTURE.md)) — no other state is touched.

**Significance**: this is the trigger for the **end-of-match "confirm
result" button**, confirmed directly from the widget's image filename —
the client shows this button on command from the server rather than
deciding locally when the match has concluded, consistent with the
server-authoritative model already established for turn/battle state.

#### Action `0x8200` — Kick from room

**Direction**: incoming.

**Payload**: `payload[0]`, a target player slot id.

**Behavior**: if the target slot identifies this client itself, sends the
standard leave packet (`0x2000`/`0xffff`) to the server. Otherwise, shows a
`ShowMessage`-style notification that a player was kicked/left.

**Significance**: the **room-owner-initiated kick** mechanism — confirms
that being kicked is delivered to the kicked player as a targeted action
(triggering their own departure) while other room members just see a
notification.

#### Action `0x8400` — Character/mobile model sync (alternate trigger)

**Direction**: incoming.

**Behavior**: performs the **exact same** texture-selection and two-
sub-object application logic as action `0x8100` above, but reached via a
different immediate predecessor call (`FUN_004dc5c0()` is invoked first,
before the shared texture-application logic).

**Significance**: given the identical downstream effect, the most plausible
distinction is that `0x8100` fires on **joining** the room (initial sync of
an already-selected character) while `0x8400` fires when a player **changes**
their character/vehicle selection while already in the room (hence the
extra preliminary call, possibly a "clear previous selection state" step)
— not proven, but a reasonable reading of the two nearly-identical code
paths differing only in that one prologue call.

#### Action `0x9002` — Game-start countdown initiation

**Direction**: incoming.

**Behavior**: gated on two conditions both being true: the all-ready flag
(`this+0x4cc`, set by action `0x8102` above) must currently be `false`, and
a countdown field (`this+0x4d4`) must currently hold the "not started"
sentinel value `-1`. If both hold, and a room-ownership check passes, the
countdown field is set to `0x31` (49 — presumably a countdown unit,
possibly ticks or a fixed pre-countdown delay before the visible countdown
begins).

**Significance**: this is the **room owner's "Start Game" button action**
(confirmed to be the button shown specifically to room owners via Channel
1's `0x3400` opcode, documented above) — the mechanism that actually
initiates the transition sequence toward the Loading screen and eventual
battle start.

---

### State 11 — In-Battle (`State11_InBattle_ProcessBattleAction`, `0x4b5460`)

This is the **largest function in the entire binary** (11,718 bytes),
confirmed as the core battle-action dispatcher via `bsfire`/`bfire1`/
`bfire2`/`bifire`/`ifire`/`sfire` (weapon-firing cursor sound-effect names)
and `sudden.mp3` (sudden-death phase music) string references. Notably,
**this function contains no floating-point instructions whatsoever** —
extensively investigated in [ARCHITECTURE.md](ARCHITECTURE.md)'s physics
section; the working conclusion is that trajectory/ballistics resolution is
**server-authoritative** rather than computed client-side in this function
(or anywhere else found in the client binary during an exhaustive search).

The packet header's action-type field here also overlaps directly with
**replay event codes** — action `0x8500` matches a replay-log event code
exactly, strong evidence this same function processes both **live network
packets and recorded replay-file events** through one shared code path
(i.e. replay playback re-feeds logged events into this dispatcher rather
than using a separate replay-specific execution path).

#### Action `3` — Generic notification toast

**Direction**: incoming.

**Behavior**: the same `ShowMessage`-virtual-call pattern as every other
Channel 2 handler.

#### Action `0x4001` — Status flag toggle

**Direction**: incoming, only processed if the acting player slot is not
this client itself.

**Behavior**: toggles a single-byte flag.

**Significance**: purpose not fully identified — a cheap status flag of
some kind, gated so a player doesn't process their own flag toggle
(consistent with many of these actions being "apply what a *remote* player
did" rather than self-referential).

#### Action `0x4002` — Proximity chat

**Direction**: incoming.

**Behavior**: computes the distance between the sending player's position
and each of the 8 battle-slot positions; the chat message is only delivered
(displayed) to players within approximately **150 units** of the sender.

**Significance**: confirms GunBound's in-battle chat has a **spatial/
proximity filter** — not a simple broadcast-to-everyone chat, but one gated
by in-game distance, presumably to support some gameplay or
immersion-related design intent (e.g. distinguishing "shout" from a more
limited "nearby" chat, though only this one distance-gated variant was
found).

#### Action `0x4003` — Chat/notification variant (unconfirmed exact distinction)

**Direction**: incoming.

**Behavior**: a per-player text-record lookup/insert pattern similar in
shape to action `0x4002`, using the same underlying helper functions.

**Significance**: exact distinction from `0x4002`/`0x4004` (e.g. team chat
vs. all chat vs. system message) not independently confirmed — grouped here
as "part of the same chat/notification family" based on shared
implementation patterns.

#### Action `0x4004` — Chat/notification variant (unconfirmed exact distinction)

**Direction**: incoming.

**Behavior**: same family as `0x4003` — a per-player text-record
lookup/insert.

**Significance**: as with `0x4003`, the precise semantic distinction from
its siblings in this action-code cluster (`0x4002`-`0x4006`) is not
resolved beyond "another chat/notification/status-relay variant."

#### Action `0x4005` — Emote or typing-indicator relay (tentative)

**Direction**: incoming, gated on two conditions: the sender must not be
this client (turn-ownership-style check), and a UI-mode field on the acting
player's record must **not** equal `5`, `6`, `8`, or `10` (i.e. the player
must not currently be in one of those four UI-busy states — the specific
meaning of states 5/6/8/10 wasn't independently decoded, only that they
gate this relay).

**Behavior**: relays a boolean flag plus a byte comparison result.

**Significance**: tentatively an emote selection or a "player is typing"
indicator, grouped with the `0x4002`-`0x4004` chat family by proximity and
shared gating logic, but carrying less payload than the confirmed proximity
chat (`0x4002`).

#### Action `0x4006` — Simple status/value relay (tentative)

**Direction**: incoming, gated on the turn-ownership check only (no UI-mode
check unlike `0x4005`).

**Behavior**: relays a single `short` field, nothing more.

**Significance**: the simplest member of the `0x4002`-`0x4006` cluster —
tentatively a ping/latency value or a camera-position sync field, given its
minimal single-field payload; not confirmed via any string or cross-
reference.

#### Action `0x8005` — Field relay (turn-gated)

**Direction**: incoming, gated on turn-ownership (must not be this
client's own turn) and a UI-mode check (the acting player's mode field must
not equal `5` or `6`).

**Behavior**: relays two fields onward through the outgoing-encode
helpers.

**Significance**: part of the confirmed **turn-start scheduled-event
chain** — this action is one of the events posted (in sequence) by action
`0xc300` below when a new turn begins: `0x8005` → `0x8006` → `0xc306` →
`0xc400` → `0xc401` → `0x8403` (Fire) → `0x8405` → `0xc409`. Its exact
payload semantics weren't independently decoded beyond "two relayed
fields," but its position early in the turn-start sequence (immediately
after `0xc300` itself) suggests some kind of turn-setup announcement.

#### Action `0x8006` — Weapon-fire feedback sound

**Direction**: incoming.

**Behavior**: reads a per-player record via `GetPlayerRecordBySlot`; if
found, relays two fields plus two boolean-derived flags through the
outgoing-encode helpers, then — based on a fire-mode byte and a
special-weapon check — plays one of four possible weapon-cursor sound
effects: `bifire` (special/charged weapon fire cursor), `bfire1`, `bfire2`,
or `bsfire` (a slower/heavier fire variant), selected via a small decision
tree comparing the fire-mode byte against `0`/`1`/`2`.

**Significance**: this is a **UI/audio feedback** action tied to weapon
selection/firing state — confirmed to be part of the same turn-start event
chain as `0x8005` (posted immediately after it by `0xc300`).

#### Action `0x8402` — Aim/angle+power relay (**confirmed**)

**Direction**: incoming, gated on turn-ownership (skip if the acting slot
is this client) and a "player record exists" check via `GetPlayerRecordBySlot`.

**Behavior**: relays two fields plus a boolean flag through the outgoing-
encode helpers — identical payload shape to action `0x8406` below.

**Significance**: **upgraded from tentative to confirmed** by tracing the
send side. Searched the whole binary for every site that pushes the literal
`0x8402` and found the real sender: inside `FUN_00461ca0` (a large,
3,153-byte input/state-update function), right after
`Replay_AppendEvent(0x8402)`, the two relayed fields are read via
`FUN_0040a4d0(param_1 + 0x243)` and `FUN_0040a4d0(param_1 + 0x2cc)` —
**the exact same two struct offsets already independently confirmed as
angle and power** in `State11_InBattle_HandleFireInput`'s Fire (`0x8403`)
payload construction (see ARCHITECTURE.md's physics-investigation
writeup). Same struct, same fields, two different call sites — this is
about as solid a cross-confirmation as static analysis gets without
dynamic tracing. `0x8402`/`0x8406` really are a live aim-angle-and-power
broadcast as another player adjusts their aim mid-turn.

#### Action `0x8403` — Fire (the weapon-firing action)

**Direction**: incoming. The single richest, most carefully examined
payload in the entire Channel 2 protocol.

**Payload layout** (following the shared 33-byte header): two numeric
fields, two boolean flags, two more numeric fields, then **eight
sequential `short` values** occupying header-relative offsets `+0x2c`
through `+0x3a` (16 bytes) — these eight shorts are the single most
information-dense part of any action payload found in this protocol, and
are **hypothesized to be trajectory waypoint samples** (a precomputed
sequence of positions along the fired projectile's arc) though this was
**not confirmed** — see ARCHITECTURE.md's physics-investigation writeup for
the extensive (ultimately inconclusive, but thorough) search for where
these values might be computed or consumed as an actual ballistic
simulation.

**Behavior**: all of the above fields are relayed onward through the
outgoing-encode helper functions (meaning this client re-broadcasts/forwards
the fire data to other clients, rather than only consuming it locally),
and the **`ifire`** sound effect is played (a lighter/normal fire cursor
sound, distinct from the `bsfire`/`bfire1`/`bfire2`/`bifire` cursor-select
sounds played by action `0x8006` above — this is the sound for the actual
firing moment, not the earlier weapon-selection UI feedback).

**Significance**: this is the confirmed **Fire** action — the moment a
player's weapon is actually discharged. Despite exhaustive investigation
(an FPU-instruction-density scan across all 2,300+ functions in the binary,
a full trace of every per-frame render-pipeline call, and a systematic
`operator_new` allocation-site audit specifically looking for a standalone
per-shot "projectile" object), **no gravity/velocity-integration code was
ever found to consume this action's payload as a physics simulation
input** — see ARCHITECTURE.md's physics section for the complete
investigation and the resulting working conclusion that trajectory
resolution is most likely server-authoritative, with this payload's eight
shorts either being a server-computed path handed to the client purely for
animation/interpolation, or serving some other non-ballistic purpose not
yet identified.

#### Action `0x8404` — Hit/damage log entry (tentative)

**Direction**: incoming.

**Behavior**: appends a new entry to a **third, distinct parallel-array
set** at header-relative offsets `+0x27`/`+0xa7`/`+0x127`/`+0x1a7` (a
128-byte, `0x80`, stride between each of the four arrays) — separate from
the primary player-slot parallel arrays used by action `0x8408`'s spawn
logic. The four fields written are: a numeric value, a target/player id, and
two single bytes. A UI-update function (`FUN_004ccbb0`) is called
afterward.

**Significance**: tentatively a **hit/damage event log entry** feeding a
kill-feed or combat-log style UI element, based on the shape of the four
fields (value + target-id + two flag/type bytes reads plausibly as "this
much damage/this event type happened to this target"). No other code in
the binary touches these exact `+0x27`/`+0xa7`/`+0x127`/`+0x1a7` offsets
directly, but **decompiling the follow-up call, `FUN_004ccbb0`, advances
this rather than leaving it a dead end**: it's a generic sort routine —
a selection-sort-style comparison/swap pass over **a different set of
four parallel arrays**, at header-relative `+0x9c`/`+0x29c`/`+0x49c`/
`+0x69c` (`0x200`-byte spacing between arrays, distinct from the `0x80`
spacing of the append arrays above), bounded by a running count at
`+0x98`. Sorting a small (this game caps at 8 players), count-bounded set
of 4 parallel value arrays immediately after logging a hit/damage event
reads strongly as **maintaining a live in-battle damage/score ranking**
(a leaderboard re-sorted after every hit), not a passive log — "UI-update
function" undersold what it does. The exact relationship between the
appended hit-log entry's fields and which of the four sorted arrays they
feed wasn't reconciled (the two array sets have different strides and
don't share an obvious shared base), so this is a genuine advance on the
open question, not a full resolution.

#### Action `0x8405` — Weapon selection sound

**Direction**: incoming.

**Behavior**: plays one of three weapon-selection sound effects —
**`b_play_weapon1`**, **`b_play_weapon2`**, or **`b_play_weapon3`** —
chosen based on which weapon slot was selected.

**Significance**: the UI/audio feedback for **choosing a weapon** (as
distinct from `0x8006`'s fire-cursor feedback and `0x8403`'s actual fire
action) — confirmed as part of the turn-start event chain, posted by
`0xc300` immediately after the Fire action `0x8403`.

#### Action `0x8406` — Aim/angle+power relay (**confirmed**)

**Direction**: incoming.

**Behavior**: identical payload shape and relay behavior to action `0x8402`
above — two fields plus a boolean flag, forwarded via the outgoing-encode
helpers.

**Significance**: **confirmed via the same send-side trace as `0x8402`** —
both `Replay_AppendEvent(0x8402)` and `Replay_AppendEvent(0x8406)` live in
the same function (`FUN_00461ca0`), each immediately preceded by reads of
the identical `param_1+0x243`/`param_1+0x2cc` angle/power fields. The two
opcodes genuinely are the same logical "broadcast my current aim" event,
reached via two different trigger paths inside that one function (their
surrounding guard conditions differ — one is gated by a checksum-state
check, the other by comparing the current angle/power against
last-sent-value fields at `param_1[0x30a9]`/`param_1[0x30aa]`, i.e. one
path is likely an unconditional periodic broadcast and the other an
only-send-on-change optimization) rather than two unrelated events that
happen to share a shape.

#### Action `0x8407` — packet-checksum keepalive (corrected from an earlier pass)

**Direction**: incoming.

**Payload**: `payload[0]`, a value of `1`, `2`, or `3`.

**Behavior, re-decompiled and corrected**: an earlier pass read this as
"select one of three global tables (`DAT_00e9ba40`/`DAT_00e9b818`/
`DAT_00796aa0`) and read a value from it" and left the exact semantics
unresolved. Fully decompiling the shared accessor function all three
cases call (`FUN_0040a4d0`, `0x40a4d0`) shows **it takes no parameter at
all** — its entire body is `EnterCriticalSection`, `PeekPacketChecksumState()`,
`LeaveCriticalSection`, return. Raw disassembly at each `0x8407` call site
confirms `PUSH <address>; CALL FUN_0040a4d0` really is emitted, but that
pushed value is never read inside the callee — it's dead from the
callee's perspective (most likely a compiler/exception-handling-frame
artifact rather than a real argument; this codebase's SEH prologues push
similar-looking constants elsewhere). **All three mode-byte cases reduce
to the identical real effect**: peek the current packet-checksum state
and fold it back into itself via `AddToPacketChecksum`. This reads as a
lightweight keepalive/integrity step, not a real per-mode table lookup or
meaningful gameplay data — the "game-constant table" framing from the
earlier pass doesn't hold up under a full decompile of the accessor.

#### Action `0x8408` — Player spawn into battle

**Direction**: incoming.

**Behavior**: appends a new entry across **four parallel per-slot `uint`
arrays** at header-relative (index, not byte) offsets `+0x228`/`+0x2a8`/
`+0x328`/`+0x3a8`, all indexed by a shared running counter (`this+0x227`,
the active-player count, incremented after the write), calls a
spawn-visual-update function (`FUN_004ccc60`). Confirmed field sources for
each array's new entry, decompiled directly from the action handler:

| Array (index offset) | Value written | Source |
|---|---|---|
| `+0x228` | `(uint)*cursor` | the packet's current parse cursor at this point in the batched-action dispatch loop — value depends on how many prior actions in the same packet were already consumed, so no fixed payload offset can be given |
| `+0x2a8` | `(uint)*(ushort*)(payload+0x23)` | fixed absolute payload offset `0x23` (a 16-bit value) |
| `+0x3a8` | `*(int*)(payload+0x25)` | fixed absolute payload offset `0x25` (a full 32-bit value) |
| `+0x328` | `(uint)teamByte` | the same byte read once at the very start of `ProcessBattleAction` (`*(byte*)(payload+5)`) — likely a team/player-slot identifier shared across every action in this dispatch call, not specific to `0x8408` |

**Significance**: this is the confirmed **player spawn/entry into battle**
action — these are the exact same four parallel arrays that action `0x3020`
(Channel 1, above) shifts down when a player disconnects, confirming a
structure-of-arrays layout for the 8 active battle slots. **Correction to
an earlier assumption**: these are plain 4-byte-per-slot `uint` arrays, not
slices of one combined `0x224`-byte struct — the `0x224` figure documented
elsewhere in this reference belongs to unrelated structures (confirmed to
be an array of per-player packet-checksum-state objects in one case, and a
separate generic engine container in another — see
[ARCHITECTURE.md](ARCHITECTURE.md)'s recurring-structures list for the
full breakdown), not to these four spawn arrays. This mirrors the
`RoomPlayerSlot` finding in ARCHITECTURE.md: GunBound's engine consistently
favors "struct of arrays" layouts for these per-slot broadcasts rather
than one packed struct per slot.

#### Action `0x8500` — Player-position/status relay

**Direction**: incoming.

**Behavior**: guarded on a successful `GetPlayerRecordBySlot` lookup and a
turn/state check (`FUN_004065a0() == 0`); when both pass, relays two
16-bit fields from the payload (`payload+0x22`, `payload+0x24`) as
outgoing packet fields, encoding the checksum state after each, then
queues a boolean derived from `payload+0x26 == 1`.

**Significance**: the relay pattern (read two 16-bit fields + one flag,
re-queue them outgoing with checksum encoding after each) matches the
same shape as actions `0x8402`/`0x8406` (aim/angle+power relay) — likely
another **position or aim-state synchronization** action, though which
specific values these two 16-bit fields represent wasn't decoded further.
Notably, `0x8500` is *also* used elsewhere as a **replay-event code**
(logged by Channel 1 opcode `0x4102`'s disconnect-notification path,
capturing a position field and a cooldown flag) — this confirms `0x8500`
genuinely represents "player position/status" data in both contexts, just
reached via two different code paths (a live relay action here, vs. a
replay-log snapshot there), not a numeric coincidence between two
unrelated meanings.

#### Action `0xc300` — Turn/round start

**Direction**: incoming.

**Behavior**: posts a long, ordered chain of scheduled sub-events via
`PostTurnEvent` (which inserts into a sorted, time-keyed tree structure
rather than dispatching immediately — i.e. these are genuinely *scheduled*
for later processing, not synchronous calls): `0x8005` → `0x8006` →
`0xc306` → `0xc400` → `0xc401` → `0x8403` (Fire) → `0x8405` → `0xc409`, in
that order.

**Significance**: this is the master **turn-sequencing action** — the
single event that kicks off an entire turn's worth of scheduled sub-events,
confirming turn progression in GunBound is driven by a **time-based event
queue** rather than a simple linear state machine. The presence of `0x8403`
(Fire) *within* this chain is notable — it implies firing isn't purely a
free-form player-triggered action but also has a scheduled/automatic
component as part of normal turn progression (though a player-initiated fire
presumably also triggers `0x8403` directly outside this chain — the two
paths aren't mutually exclusive based on what was traced).

#### Action `0xc301` — Turn-timer + battle setup data write

**Direction**: incoming.

**Behavior**: identical to State 10 (Loading)'s handler for this same
action code — writes the turn-timer field (`+0x10a4`, checked against
`60000`/`0xffff`) and the 8-element wind/spawn setup array (`+0x2302`) —
this is a shared code path between the two screens' handlers, not
independently reimplemented.

**Significance**: see State 10's entry above for the full writeup; the
duplication here confirms this action is meant to be receivable/processable
regardless of whether the client is still on the Loading screen or has
already transitioned into active battle (e.g. covering a race condition
where this action arrives slightly late).

#### Action `0xc303` — Turn-phase state machine (sub-switch)

**Direction**: incoming, further dispatched on a payload sub-value.

**Behavior**: an inner `switch` on a byte value drives a small internal
turn-phase state machine:

- Sub-values `0`, `1`, `2` each set a turn-phase field (`this+0x42e`) to a
  corresponding value — `3`, `4`, and `0` respectively.
- Sub-values `0xe` and `0xf` (near-identical implementations) perform a
  fuller turn-advance sequence — refreshing viewport-related data and
  playing a sound — and then **re-post the entire `0xc300` event chain**,
  effectively starting the next turn.

**Significance**: `0xe` and `0xf`'s near-duplicate bodies both triggering
the next turn suggests they represent two slightly different **causes** of
the same "advance to the next turn" outcome — most plausibly a normal
turn-end (weapon fired, turn naturally concludes) versus a forced/timeout-
driven turn-end (player ran out of time or surrendered their turn), though
which sub-value corresponds to which cause wasn't independently confirmed.

#### Action `0xc304` — Movement

**Direction**: incoming, sub-dispatched on a 4-bit direction value with an
additional high bit acting as a "running" modifier flag.

**Behavior**: for each of the three basic direction sub-cases (values `1`,
`2`, `3`) plus their "running" (`|0x10`) variants: looks up a per-player
name/label buffer (confirmed **`0x1120`-byte stride**, a *second* parallel
per-player array distinct from the primary `0x224`-byte player-game-slot
array), plays a direction-specific movement sound effect, and calls a
function (`FUN_004368f0`) that — after investigation — turned out to
construct a small heap object (76 bytes) whose vtable methods call the same
cursor-setting function (`FUN_00461c60`) used elsewhere in the codebase for
setting `"normal"`/`"wnormal"` mouse cursors. **This means the movement
action's downstream call is a sound/cursor-feedback trigger, not velocity
application** — contrary to an earlier working hypothesis during initial
analysis that this might be where movement physics/velocity gets applied.
The actual write of a position delta (`x += velocity`) was never isolated
within this branch despite the search.

**Significance**: confirms the player-movement action exists and is
direction/speed-modified (walk vs. run), and confirms (via ruling it out)
that the *sound and cursor feedback* for movement lives here, while the
actual position-integration logic — if it exists client-side at all —
remains unlocated, consistent with the broader physics investigation's
conclusion that trajectory/movement math is most likely server-side.

#### Action `0xc305` — Turn timeout/expiry

**Direction**: incoming.

**Behavior**: resets the turn-phase-related byte field, sets a duration
constant into a countdown global — the specific constant used
(`0x11`/`0x10`/`0xb5`) depends on a difficulty-flag check — and shows a
"turn's up"-style message via the `ShowMessage` virtual call.

**Significance**: the client-side handling of a **turn timing out** without
the player taking an action — confirms turn duration/countdown behavior can
vary by difficulty setting (three distinct duration constants observed).

#### Action `0xc306` — Aim/direction confirmation

**Direction**: incoming.

**Behavior**: reads a final `ushort` field into the turn-timer slot
(`+0x429`, i.e. the same general area as the turn-timer field referenced
elsewhere, though at a different specific offset than `+0x10a4` — possibly
this offset is relative to a different base/object than the `0xc301`
writes), and clears a per-slot cooldown field.

**Significance**: part of the confirmed turn-start event chain (posted by
`0xc300` in third position, right after `0x8006`) — likely marks the point
where a player's aim/direction input has been finalized/confirmed for the
current turn, clearing whatever cooldown was preventing further input
changes.

#### Action `0xc308` — Mid-turn wind/spawn-data update

**Direction**: incoming.

**Behavior**: reads **eight sequential `short` values** directly from the
payload into the exact same `+0x2302` setup array that action `0xc301`
initializes (see above) — but *without* also re-writing the turn-timer
field, unlike `0xc301`.

**Significance**: this looks like a **mid-turn update** to the wind/spawn
data (e.g. wind direction changing between turns, or a corrective update)
that doesn't require a full turn-timer reset — a lighter-weight sibling to
`0xc301`'s full turn-setup write.

#### Action `0xc400` — No-op scheduling checkpoint

**Direction**: — (present in the dispatch structure but has no executable
logic).

**Behavior**: the guarding `if (uVar1 != 0xc400) { ... }` structure means
that when the action value equals `0xc400` exactly, the entire following
switch block (which handles `0xc300`, `0xc301`, etc.) is skipped entirely —
there is no code that runs specifically for this action value.

**Significance**: matches the same "no-op scheduling checkpoint" pattern
found for Channel 1's `0x6027` in the Avatar Store handler — `0xc400` exists
purely as a named point in the `0xc300` turn-start event chain (it's the
fourth event posted, right after `0xc306` and before `0xc401`), likely used
for timing/ordering purposes by the scheduled-event system itself rather
than carrying any payload-processing responsibility of its own.

#### Action `0xc401` — Turn-timeout weapon-select relay

**Direction**: incoming.

**Behavior**: delegates to a dedicated function
(`HandleTurnTimeoutSlot`, `0x4cc1e0`, originally `FUN_004cc1e0`): if the
action's target belongs to a slot other than this client, relays four
fields (from header-relative offsets `+1`, `+2`, `+3`, `+5`, and `+7`)
through the outgoing-encode helper functions, then triggers a
**`b_play_weapon3`** selection sound/visual.

**Significance**: part of the turn-start weapon-select flow — posted
immediately after `0xc400` in the `0xc300` event chain. The specific
`b_play_weapon3` sound trigger (as opposed to the more general
`0x8405`/`0x8006` weapon-sound actions) suggests this specifically relates
to a timeout-driven default weapon selection (i.e. if a player doesn't
choose a weapon in time, weapon 3 is auto-selected) — inferred from the
function's assigned name during analysis, not proven via an explicit label
in the disassembly.

#### Action `0xc409` — Fire confirmed/committed

**Direction**: incoming.

**Payload**: identical shape to action `0x8403` (Fire) — two fields, two
boolean flags, two more fields, then the same eight sequential shorts at
`+0x2c` through `+0x3a`.

**Behavior**: plays the **`sfire`** sound effect (distinct from `0x8403`'s
`ifire`) and resets two flight-state flag globals
(`DAT_005f3768 = 1`, `DAT_005f376c = 0`) plus a per-player flag.

**Significance**: given the identical payload shape to `0x8403` but a
different sound and the flight-state flag resets, this reads as **"fire
confirmed/committed"** — a follow-up action to the initial `0x8403` Fire
that finalizes the shot (perhaps once the server has acknowledged/validated
the fire attempt), rather than a second independent computation. Confirmed
as part of the `0xc300` turn-start chain, posted last (eighth position).

#### Action `0xc40a` — Final position sync (tentative)

**Direction**: incoming.

**Behavior**: writes two raw `int` values per-slot directly from the packet
payload, with no further processing. Confirmed exact destination this
pass: `this[teamByte*2 + 0x8e1] = *cursor` and `this[teamByte*2 + 0x8e2] =
*(int*)(payload+0x25)` — a 2-`int`-per-slot parallel array (yet another
small structure-of-arrays pair, indexed by the same team/slot byte used
throughout `ProcessBattleAction`, distinct from the `+0x228`/`+0x2a8`/
`+0x328`/`+0x3a8` spawn arrays confirmed for action `0x8408`).

**Significance**: tentatively a **final resting position sync** for a
projectile or player after motion has concluded — inferred purely from the
bare "write two ints, no computation" shape, which is consistent with
receiving an already-computed final position rather than deriving one
locally (again consistent with the broader server-authoritative-physics
conclusion). The `payload+0x25` fixed offset matches the same absolute
offset used by actions `0x8500`/`0x8408` for their own position-ish
fields, suggesting a shared "position field" convention across several
of these Channel 2 actions even though each stores it in its own separate
array.

#### Action `0xc40b` — Turn-timeout bookkeeping across all slots

**Direction**: incoming.

**Behavior**: re-decompiled with more depth this pass. Guarded on a packet-
checksum-state check (`PacketChecksumNotEquals(..., 3)`), then iterates
all 8 player-slot records (`in_ECX + 0x477` onward), filtering each
through a helper (`FUN_0040b300(slot, 2)`) — only slots that pass this
filter get processed further. For each matching slot: queues/encodes
several checksum-protected fields, then plays a **sound/cursor-effect**
via the same `FUN_004368f0` trigger confirmed elsewhere for movement
cues (see action `0xc304`'s writeup in [ARCHITECTURE.md](ARCHITECTURE.md)),
and builds/shows a **formatted notification message** — a localized string
(resource ID `0x274`, looked up via `FUN_0043dc70`, the same localized-
string-table helper used by the `0xc401` weapon-select-sound trigger)
populated via `sprintf` with two values derived from that player's stats
(read from struct offsets `+0xb30`/`+0x90c`), then shown via the same
"show message" virtual call pattern used throughout this codebase
(`(**(vtable+0x28))(message, 4, 3)`).

**Significance**: this is more specific than "generic housekeeping" — it's
a **per-player conditional sound-plus-notification broadcast**, filtered by
some slot-state predicate (plausibly "is this slot still active/hasn't
already been notified this turn"), most likely surfacing a per-player
end-of-turn or timeout-related status message (e.g. "Player X's turn timed
out") rather than pure internal bookkeeping. The exact localized string
content (resource `0x274`) wasn't resolved — this project hasn't
independently traced GunBound's localized-string-table system — but the
sound trigger + formatted-message-with-player-stats pattern strongly
suggests a visible, player-facing notification rather than silent state
maintenance.

#### Action `0xc801` — Periodic status relay

**Direction**: incoming.

**Behavior**: builds and sends an outgoing packet with opcode `0x4100`,
populated with fields read from a status struct at `+0xb0b0`/`+0xb0ac`
(fields that are also written elsewhere as part of turn-status tracking —
values `1`/`2`/`3` were observed being stored into the `+0xb0b0` field across
various other turn-related code paths). Also logs replay data resembling
movement information (adjacent to but not identical in code path to the
confirmed `0x8304`... movement replay logging, hence "movement-adjacent"
rather than a confirmed exact match).

**Significance**: appears to be a **periodic status relay/heartbeat**
specific to in-battle turn/player status, distinct from the generic
keepalive-ping mechanism confirmed in Channel 1 (State 9's `0x4410`
opcode).

#### Action `0xf008` — Direct quit/disconnect

**Direction**: incoming.

**Behavior**: sets `g_pendingGameState = 0xf` (the confirmed **quit** state)
directly, with no intervening leave-packet exchange.

**Significance**: a more abrupt quit trigger than the `0x2001`/`0x3fff`-style
leave packets seen elsewhere — this one skips straight to the quit-state
transition rather than going through any negotiated leave sequence,
suggesting it's used for a harder/more forceful disconnect scenario (e.g. a
kick or a fatal desync, as opposed to a voluntary graceful leave).

#### Action `0xf009` — Per-slot byte value set

**Direction**: incoming.

**Behavior**: delegates to `FUN_004d0fd0(slotOffset, payload[0])` — a
per-slot single-byte value setter. The specific field being set within the
per-slot record wasn't identified.

**Significance**: a generic per-slot single-value setter of otherwise
unconfirmed purpose.

#### Action `0xf00a` — Player record field query/relay

**Direction**: incoming.

**Behavior**: relays a value read from the current player's own record at
field offset `+0x6744`, through the standard outgoing-encode helper
functions.

**Significance**: a simple query-and-relay of an unidentified per-player
field — the field's semantic meaning wasn't independently determined.

#### Action `0xf00b` — Terrain deformation

**Direction**: incoming.

**Behavior**: delegates to a dedicated function
(`LoadTerrainDeformationFrame`, `0x4d1500`, originally `FUN_004d1500`)
which constructs and loads a set of numbered map-frame image filenames:
`mf%05d.img` (the base frame), plus three colored-channel variant filenames
(`%cb%05d.img`, `%cg%05d.img`, `%ch%05d.img` — likely blue/green/hue or
similar tinting-channel variants used for visual damage-state layering), and
correspondingly-suffixed `l`-variant filenames for what's presumably a
second rendering layer (`mf%05dl.img`, `%cb%05dl.img`, etc.), all loaded
into a large (32 KB) local stack buffer.

**Significance**: this is the classic GunBound **post-explosion terrain
crater** mechanic — after a weapon impacts the terrain, the server tells
all clients which pre-baked, numbered deformed-terrain frame image to
display at the impact location, rather than each client independently
computing/rendering a procedural deformation. This confirms terrain
destruction in GunBound is implemented via **pre-rendered frame swapping**,
not runtime procedural mesh/heightmap deformation.

---

## Confirmed recurring structures

A quick-reference table of the byte-level structures independently
confirmed (from multiple, cross-checking opcode implementations) across
this document:

| Struct | Size | Evidence |
|---|---|---|
| Per-player packet-checksum-state | `0x224` (548 bytes) | **Resolved and reclassified this pass** — the array at `playerId * 0x224 + 0xebef4` (touched by `0x3020`'s disconnect handler) is **not** a gameplay struct at all: traced every call site touching this array across the binary (34 total, via a whole-binary immediate-operand scan for `0xebef4`) and found the computed pointer is passed directly into `PeekPacketChecksumState`/`FUN_0040a4d0` (a thin critical-section wrapper around the same function). This is an array of **per-player instances of the packet-checksum-state object** (see the "Packet-checksum utility family" section in [ARCHITECTURE.md](ARCHITECTURE.md)), not a `PlayerGameSlot`. |
| Player game slot (unresolved) | `0x224` (548 bytes) | Separately seen in a 20-element accumulation loop in the room-list's stat-summing (unlabeled) opcode, and the Avatar Store's 8-element per-avatar array (`FUN_00443c20`'s constructor) — these may or may not be the same struct as the checksum-state one above (same size could be coincidence, or the checksum state could be embedded as a sub-object within a larger per-player struct in these other contexts). Not resolved this pass. Action `0x8408` does **not** populate this — that action writes into four separate 4-byte-per-slot `uint` arrays (`+0x228`/`+0x2a8`/`+0x328`/`+0x3a8`, indexed by active-slot position), a completely different structure (see that action's writeup above). |
| Room player display slot | `0x80` (128 bytes) | Room-list opcodes `0x2105`/`0x21f0`/`0x21f2` all write into this exact buffer, indexed as `base + slot*0x80`. |
| Room player stat fields (per-slot, individually syncable) | Six fields: 1 byte / 1 byte / 4 bytes / 1 byte / 1 byte / 1 byte, at fixed offsets `+0x4497c` / `+0x4499c` / `+0x44984` / `+0x449a2` / `+0x449a8` / `+0x449ae` from a per-room base | Opcode `0x2103` (bulk update, all six fields at once) and opcodes `0x21f3`-`0x21f7` (individual per-field updates, one opcode per field — a sixth opcode for the `+0x449ae` field wasn't found, suggesting it may only be bulk-updatable) populate this exact same field set. |
| In-Battle turn-setup array | 8 shorts (16 bytes) at offset `+0x2302` | Channel 2 actions `0xc301` (initial write, paired with the turn-timer field) and `0xc308` (mid-turn update, standalone) both target this array. |
| Inventory item | `0x9c` (156 bytes) | Avatar Store opcode `0x6002` — four `uint` id fields, a `time_t` expiration timestamp, and a variable-length trailing blob. |
| Player name/label buffer | `0x1120` (4,384 bytes) | Channel 2's In-Battle movement action (`0xc304`) looks up per-player entries in an array with this stride — a second, much larger parallel array distinct from the 548-byte player-game-slot array. |
| Hit/damage log entry (tentative) | `0x80` (128 bytes) stride across four parallel arrays at `+0x27`/`+0xa7`/`+0x127`/`+0x1a7` | Channel 2 action `0x8404` — distinct from, and not to be confused with, the primary spawn arrays at `+0x228`/`+0x2a8`/`+0x328`/`+0x3a8` used by action `0x8408`. |

## Known gaps

Coverage of **opcode branches** is complete within this document's stated
scope (every `if`/`switch case` in all 5 `ProcessPacket` handlers and all 3
`ProcessBattleAction` handlers has been located and read at least once).
What remains genuinely open is **depth** on a specific handful of points,
listed here so future work has a concrete starting list rather than a vague
"more research needed":

1. ~~Action `0x8407`'s three underlying tables~~ — **resolved**: they
   aren't real per-mode tables at all. A full decompile of the shared
   accessor (`FUN_0040a4d0`) showed it ignores its argument entirely and
   just peeks the packet-checksum state; see the corrected writeup above.
2. **Action `0x8404`'s exact purpose — advanced, not fully resolved.**
   Decompiling its follow-up call (`FUN_004ccbb0`) showed it's a generic
   sort over a *different* set of four parallel arrays than the ones
   `0x8404` appends to — pointing toward "this maintains a live in-battle
   damage/score ranking" rather than a passive log, but the exact link
   between the appended entry and the sorted arrays wasn't reconciled; see
   the corrected writeup above.
3. **The eight-`short` payload in the Fire action (`0x8403`/`0xc409`)** —
   hypothesized to be trajectory waypoint samples, but this was never
   confirmed; see ARCHITECTURE.md's extensive (ultimately inconclusive)
   physics investigation for the full search that was performed trying to
   locate where these values are computed or consumed as an actual physics
   simulation.
4. **Exact byte-level field boundaries within each payload** are inferred
   from the decompiled access patterns observed (`*(ushort*)(payload+N)`,
   etc.), not from a formal struct/header definition recovered from the
   binary — treat every offset in this document as "confirmed observed in
   this specific code path," not necessarily "the only possible valid
   layout" for that conceptual field.
5. **No opcode or action was found anywhere in this protocol that performs
   continuous position/velocity integration during projectile flight** —
   see ARCHITECTURE.md's physics conclusion (server-authoritative
   resolution is the most likely explanation, based on an exhaustive but
   necessarily circumstantial static-analysis search).
6. ~~The single unlabeled Channel 1 opcode in State 3 that triggers
   `ChangeGameState(9)`~~ — **resolved, and there isn't one.** Fully
   re-decompiled `State03_GameRoomList_ProcessPacket` and traced every
   opcode comparison in the function (it's a long if-else-if cascade, not
   a clean `switch`, apart from one small `switch(opcode)` block for
   `0x21f2`-`0x21f7` that always returns before reaching this code).
   Confirmed by exhaustively listing every `opcode ==`/`opcode !=`/
   `opcode <` comparison in the function: `0x6001` (→ `ChangeGameState(7)`),
   `0x21f1`-`0x21f7`, `0x2001`, `0x201f`, `0x2103`, `0x2105`, `0x2111`,
   `0x2121` are each individually handled and return early. **The
   `ChangeGameState(9)` code is the shared fallthrough (`switchD_00428058_default`)
   reached whenever the opcode matches *none* of those specific values** —
   there is no single dedicated "join room" opcode to name; it's a
   catch-all in this function's control flow, not a documentation gap
   where one number was simply forgotten. (The client-side gate that
   presumably ensures only a genuine "enter room" message reaches this
   fallthrough in practice — e.g. the server only ever sending an
   unhandled-here opcode at the right moment — isn't visible from this
   function alone.)
