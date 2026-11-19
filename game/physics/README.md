# Player physics prototype

This is the first isolated gameplay module for Sonic3RetroEngine. It uses deterministic 16.16 fixed-point values and a one-frame update.

## Included
- Ground acceleration and speed cap
- Stronger deceleration when reversing direction
- Ground friction when no direction is held
- Optional air steering
- Jump impulse and variable-height jump release
- Gravity and terminal fall speed
- Facing direction

## Integration boundary

This is a tunable starting implementation, not a claim of exact Sonic 3 physics. Values are provisional and must be tuned against authorized reference gameplay. It does not yet implement tile collision, slopes, rolling, spindash, springs, water, or character abilities.

RSDKv5 already contains scene, entity, fixed-point, and collision infrastructure. The next integration step is to connect this module to an RSDK game object and use collision results to determine grounded state, floor snapping, wall response, and slope behavior.

All speeds and tuning values are 16.16 fixed-point units. The prototype currently treats one call as one game frame. The final tick rate and frame-rate handling must be established during integration.
