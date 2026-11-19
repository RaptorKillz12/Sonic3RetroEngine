#include "RSDKPlayerAdapter.hpp"
#include "RSDK/Scene/Legacy/v3/CollisionLegacyv3.hpp"

namespace sonic3::rsdk {

void applyTuning(RSDK::Legacy::v3::Player& player, const PlayerTuning& tuning)
{
    player.topSpeed = tuning.topSpeed;
    player.acceleration = tuning.acceleration;
    player.deceleration = tuning.deceleration;
    player.airAcceleration = tuning.airAcceleration;
    player.gravityStrength = tuning.gravityStrength;
    player.jumpStrength = tuning.jumpStrength;
    player.tileCollisions = true;
    player.objectInteractions = true;
    player.visible = true;
}

void readNativeInput(RSDK::Legacy::v3::Player& player)
{
    RSDK::Legacy::v3::ProcessPlayerControl(&player);
}

void resolveNativeTileCollision(RSDK::Legacy::v3::Player& player)
{
    RSDK::Legacy::v3::ProcessPlayerTileCollisions(&player);
}

} // namespace sonic3::rsdk
