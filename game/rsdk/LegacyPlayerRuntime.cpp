#include "LegacyPlayerRuntime.hpp"
#include "RSDK/Scene/Legacy/v3/CollisionLegacyv3.hpp"

namespace sonic3::rsdk {

void configureLegacyPlayer(RSDK::Legacy::v3::Player& p,
                           const LegacyPlayerTuning& t)
{
    p.topSpeed = t.topSpeed;
    p.acceleration = t.acceleration;
    p.deceleration = t.deceleration;
    p.airAcceleration = t.airAcceleration;
    p.airDeceleration = t.airDeceleration;
    p.gravityStrength = t.gravityStrength;
    p.jumpStrength = t.jumpStrength;
    p.jumpCap = t.jumpCap;
    p.rollingAcceleration = t.rollingAcceleration;
    p.rollingDeceleration = t.rollingDeceleration;
    p.visible = true;
    p.tileCollisions = true;
    p.objectInteractions = true;
    p.gravity = true;
}

// RSDK's implementation reads the active controller and fills left/right,
// up/down, jumpPress and jumpHold on the legacy player data.
void sampleLegacyPlayerInput(RSDK::Legacy::v3::Player& p)
{
    RSDK::Legacy::v3::ProcessPlayerControl(&p);
}

// Uses the engine's real stage collision map, sensors, path grip and air
// collision. Do not also run the independent prototype TileMap solver.
void resolveLegacyPlayerCollision(RSDK::Legacy::v3::Player& p)
{
    RSDK::Legacy::v3::ProcessPlayerTileCollisions(&p);
}

} // namespace sonic3::rsdk
