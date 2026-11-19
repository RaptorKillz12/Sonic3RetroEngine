#pragma once
#include <cstdint>
namespace sonic3 {
using Fixed = std::int32_t;
constexpr Fixed FIXED_ONE = 1 << 16;
constexpr Fixed fixed(int value) { return static_cast<Fixed>(value) << 16; }
struct PhysicsTuning {
    Fixed groundAcceleration = fixed(1);
    Fixed groundDeceleration = fixed(2);
    Fixed friction = fixed(1);
    Fixed airAcceleration = fixed(0);
    Fixed maxGroundSpeed = fixed(6);
    Fixed gravity = fixed(1);
    Fixed jumpImpulse = fixed(10);
    Fixed jumpReleaseGravity = fixed(2);
    Fixed maxFallSpeed = fixed(16);
};
struct Input {
    std::int8_t horizontal = 0;
    bool jumpPressed = false;
    bool jumpHeld = false;
};
struct PlayerState {
    Fixed x = 0, y = 0;
    Fixed velocityX = 0, velocityY = 0;
    bool grounded = true;
    bool facingRight = true;
};
// One deterministic movement step. RSDK scene collision remains responsible
// for floor/wall contact, slope alignment, and grounded-state correction.
void stepPlayerPhysics(PlayerState& player, const Input& input,
                       const PhysicsTuning& tuning = {});
} // namespace sonic3
