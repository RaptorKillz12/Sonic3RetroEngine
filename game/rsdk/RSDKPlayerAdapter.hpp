#pragma once

// Adapter boundary between our gameplay tuning and RSDKv5's existing
// Legacy v3 player/collision implementation.
// Compile this file as part of a compatible RSDKv5 game/mod project.
#include "RSDK/Scene/Legacy/v3/PlayerLegacyv3.hpp"

namespace sonic3::rsdk {

struct PlayerTuning {
    int topSpeed = 0x60000;       // 6.0 in 16.16 fixed point
    int acceleration = 0x1000;    // provisional; tune in-game
    int deceleration = 0x2000;    // provisional; tune in-game
    int airAcceleration = 0x0000;
    int gravityStrength = 0x3800; // provisional; tune in-game
    int jumpStrength = 0x68000;   // provisional; tune in-game
};

// Copy our tuning into the actual RSDK legacy player structure.
// This does not replace RSDK's movement code; it configures the native player.
void applyTuning(RSDK::Legacy::v3::Player& player,
                 const PlayerTuning& tuning = {});

// Uses RSDK's own input and tile collision routines. Call from the matching
// legacy-player update sequence, not from an unrelated entity update.
void readNativeInput(RSDK::Legacy::v3::Player& player);
void resolveNativeTileCollision(RSDK::Legacy::v3::Player& player);

} // namespace sonic3::rsdk
