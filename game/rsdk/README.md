# RSDKv5 legacy-v3 player bridge

The upstream RSDKv5 code defines `RSDK::Legacy::v3::Player` as a legacy player data structure. It is **not** a normal `Entity` subclass and it does not provide a ready-made Sonic 3 player object or Sonic 3 state machine.

## Verified native calls

The bridge targets declarations in the upstream headers:

- `RSDK/Scene/Legacy/v3/PlayerLegacyv3.hpp`: `Legacy::v3::Player` and `ProcessPlayerControl(Player*)`.
- `RSDK/Scene/Legacy/v3/CollisionLegacyv3.hpp`: `ProcessPlayerTileCollisions(Player*)`.

Use `LegacyPlayerRuntime.hpp/.cpp` as the current bridge. It configures the legacy player's tuning fields, samples native controller input, and exposes the engine's native tile/path collision call.

## Required call order inside a game/mod player update

1. Call `sampleLegacyPlayerInput(player)`.
2. Run game-specific movement and state logic (ground, air, roll, jump, hurt, death, character ability).
3. Call `resolveLegacyPlayerCollision(player)` after position/velocity movement.
4. Update animation and camera from the resolved player state.

The movement/state step is intentionally not fabricated here: the RSDK decompilation does not supply Sonic 3's player state machine. The game/mod must own that logic and register its player entity through the supported RSDK mod/object system.

## Build status

The bridge source requires upstream RSDKv5 include paths and must be added to a compatible game/mod target. The current GitHub workflow builds the upstream engine separately; it does not yet compile or load this bridge. No playable game object is claimed at this stage.

The older `RSDKPlayerAdapter.hpp/.cpp` files are retained as the earlier prototype; use `LegacyPlayerRuntime.hpp/.cpp` for new integration work.

The independent `game/physics` and `game/systems` modules remain prototypes. Once connected, RSDK legacy collision must be the authoritative collision solver; do not run both collision solvers against one player.
