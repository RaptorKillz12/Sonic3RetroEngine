#pragma once
#include <cstdint>
namespace sonic3 {
enum class PlayerMode : std::uint8_t { Ground, Air, Roll, Spindash, Hurt, Dead, Glide, Climb, Fly, Swim };
enum class PlayerAction : std::uint8_t { None, Jump, ReleaseJump, Down, ReleaseDown, Left, Right, Hurt, Die, Land, Ability };
struct PlayerCommand {
    bool left=false,right=false,down=false,jumpPressed=false,jumpHeld=false,jumpReleased=false;
    bool hurt=false,die=false,abilityPressed=false;
};
struct PlayerMotion {
    float x=0,y=0,vx=0,vy=0,groundSpeed=0;
    float groundAcceleration=0.046875f, groundDeceleration=0.5f, friction=0.046875f;
    float topSpeed=6.0f, airAcceleration=0.09375f, gravity=0.21875f;
    float jumpSpeed=6.5f, rollFriction=0.0234375f, rollDeceleration=0.125f;
    bool grounded=true,facingRight=true,jumpLocked=false;
    PlayerMode mode=PlayerMode::Ground;
    int spindashCharge=0, hurtFrames=0;
};
void updatePlayerState(PlayerMotion& p,const PlayerCommand& command);
}
