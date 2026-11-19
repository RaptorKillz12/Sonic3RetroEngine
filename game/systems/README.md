# Gameplay systems foundation

Engine-independent gameplay logic intended to be connected to RSDKv5 entities and scene callbacks.

Implemented starter systems:
- AABB overlap and axis-separated solid tile collision
- Character capability table for Sonic, Tails, and Knuckles
- Shields and provisional shield ability flags
- Rings, score, extra lives, damage, invulnerability timers
- Spring launch, monitors, checkpoints, enemy stomp/contact
- Camera follow and level bounds
- Emerald progression
- Underwater air countdown and drowning state
- Life loss and game-over state

This is not yet a complete Sonic 3 recreation. Tile collision is a simple rectangular prototype: it does not implement angle masks, one-way platforms, slope-following, loop geometry, moving-platform carry, breakable terrain, water surface transitions, ring scatter entities, boss logic, special-stage gameplay, or exact original frame timing. Those require dedicated RSDK integrations and tuning. Character ability flags are capability metadata, not full flight/glide/shield movement implementations.

The code is deliberately separate from upstream engine files so it can be unit-tested without copying proprietary game code or assets. All gameplay art, level layouts, music, and sound must be original or properly licensed.
