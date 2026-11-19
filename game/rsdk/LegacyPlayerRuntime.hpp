#pragma once

#include "RSDK/Scene/Legacy/v3/PlayerLegacyv3.hpp"

namespace sonic3::rsdk {

// RSDKv5 exposes the legacy-v3 player as a data structure, not as a
// standalone C++ Entity subclass. The game/mod script owns the entity and
// invokes these bridge functions from its player update callback.
struct LegacyPlayerTuning {
    int topSpeed          = 0x60000;
    int acceleration      = 0x1000;
    int deceleration      = 0x2000;
    int airAcceleration   = 0x0000;
    int airDeceleration   = 0x0000;
    int gravityStrength   = 0x3800;
    int jumpStrength      = 0x68000;
    int jumpCap           = 0x60000;
    int rollingAcceleration = 0x0800;
    int rollingDeceleration = 0x1000;
};

void configureLegacyPlayer(RSDK::Legacy::v3::Player& player,
                           const LegacyPlayerTuning& tuning = {});

// Call once per game frame before reading the player's directional/jump flags.
void sampleLegacyPlayerInput(RSDK::Legacy::v3::Player& player);

// Call after the game-specific movement/state logic has updated XPos/YPos
// and velocities. RSDK then performs its native path-grip/air tile collision.
void resolveLegacyPlayerCollision(RSDK::Legacy::v3::Player& player);

} // namespace sonic3::rsdk
