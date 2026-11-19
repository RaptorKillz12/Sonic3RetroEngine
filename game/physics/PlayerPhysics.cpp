#include "PlayerPhysics.hpp"
#include <algorithm>
namespace sonic3 {
namespace {
Fixed approach(Fixed value, Fixed target, Fixed amount) {
    if (value < target) return std::min<Fixed>(value + amount, target);
    if (value > target) return std::max<Fixed>(value - amount, target);
    return value;
}
Fixed clamp(Fixed value, Fixed low, Fixed high) {
    return std::max(low, std::min(value, high));
}
}
void stepPlayerPhysics(PlayerState& player, const Input& input,
                       const PhysicsTuning& tuning) {
    const int direction = input.horizontal < 0 ? -1 : (input.horizontal > 0 ? 1 : 0);
    if (direction != 0) {
        player.facingRight = direction > 0;
        if (player.grounded) {
            const Fixed target = direction * tuning.maxGroundSpeed;
            const bool reversing = (player.velocityX > 0 && direction < 0) ||
                                   (player.velocityX < 0 && direction > 0);
            player.velocityX = approach(player.velocityX, target,
                reversing ? tuning.groundDeceleration : tuning.groundAcceleration);
        } else if (tuning.airAcceleration > 0) {
            player.velocityX = clamp(player.velocityX + direction * tuning.airAcceleration,
                -tuning.maxGroundSpeed, tuning.maxGroundSpeed);
        }
    } else if (player.grounded) {
        player.velocityX = approach(player.velocityX, 0, tuning.friction);
    }
    if (input.jumpPressed && player.grounded) {
        player.grounded = false;
        player.velocityY = -tuning.jumpImpulse;
    }
    if (!player.grounded) {
        Fixed gravity = tuning.gravity;
        if (!input.jumpHeld && player.velocityY < 0)
            gravity = std::max(gravity, tuning.jumpReleaseGravity);
        player.velocityY = std::min(player.velocityY + gravity, tuning.maxFallSpeed);
    }
    player.x += player.velocityX;
    player.y += player.velocityY;
}
} // namespace sonic3
