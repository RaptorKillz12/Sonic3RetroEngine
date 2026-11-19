#include "../PlayerPhysics.hpp"
#include <cassert>
using namespace sonic3;
int main() {
    PlayerState player;
    PhysicsTuning tuning;
    stepPlayerPhysics(player, Input{1, false, false}, tuning);
    assert(player.velocityX == tuning.groundAcceleration);
    assert(player.facingRight);
    const Fixed beforeFriction = player.velocityX;
    stepPlayerPhysics(player, Input{0, false, false}, tuning);
    assert(player.velocityX < beforeFriction);
    player.grounded = true;
    player.velocityY = 0;
    stepPlayerPhysics(player, Input{0, true, true}, tuning);
    assert(!player.grounded);
    assert(player.velocityY < 0);
    assert(player.y < 0);
    const Fixed risingVelocity = player.velocityY;
    stepPlayerPhysics(player, Input{0, false, false}, tuning);
    assert(player.velocityY > risingVelocity);
    return 0;
}
