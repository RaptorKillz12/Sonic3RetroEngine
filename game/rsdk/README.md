# RSDKv5 player adapter

This is the first explicit connection point to the upstream RSDKv5 legacy-v3 player system.

It uses the engine's existing:
- `Legacy::v3::Player` data structure
- `ProcessPlayerControl` input processing
- `ProcessPlayerTileCollisions` tile collision and path-grip implementation

The adapter configures the native player's speed/acceleration/gravity/jump fields and exposes the native input and collision calls. It deliberately does not call them from an invented update callback: the correct call order depends on the game project's player object and its existing state machine.

## Integration status

This is an adapter source file, not yet compiled into the upstream engine. The upstream decompilation repository is checked out by CI into a temporary Actions workspace; it is not vendored into this repository. To compile this adapter, add `game/rsdk/RSDKPlayerAdapter.cpp` to the actual RSDK game/mod target and add the upstream `RSDKv5` source include directory.

The tuning values are provisional 16.16 fixed-point examples, not measured Sonic 3 constants. Do not treat this as exact original physics.

The independent `game/physics` and `game/systems` modules remain prototypes. Native RSDK collision should be authoritative once this adapter is integrated; do not run both collision solvers on the same player.
