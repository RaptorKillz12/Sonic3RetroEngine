#include "GameSystems.hpp"
#include <algorithm>
#include <cmath>

namespace sonic3 {
bool overlaps(const Rect& a,const Rect& b) {
    return a.x < b.x+b.w && a.x+a.w > b.x &&
           a.y < b.y+b.h && a.y+a.h > b.y;
}
CharacterAbilities abilitiesFor(Character c, Shield s) {
    CharacterAbilities a;
    if(c==Character::Tails) { a.canFly=true; a.canSwim=true; }
    if(c==Character::Knuckles) { a.canGlide=true; a.canClimb=true; }
    if(c==Character::Sonic) {
        a.canFireDash=s==Shield::Fire;
        a.canBubbleBounce=s==Shield::Water;
        a.canDoubleJump=s==Shield::Lightning;
    }
    return a;
}
void tickVitals(PlayerVitals& v) {
    if(v.invulnerabilityFrames>0) --v.invulnerabilityFrames;
    if(v.hurtCooldownFrames>0) --v.hurtCooldownFrames;
}
void grantExtraLifeIfEligible(PlayerVitals& v) {
    while(v.score>=50000) { v.score-=50000; ++v.lives; }
}
void collectRing(PlayerVitals& v,int amount) {
    if(amount<=0 || v.dead) return;
    v.rings+=amount;
    if(v.rings>=100) { ++v.lives; v.rings-=100; }
}
void awardScore(PlayerVitals& v,int amount) {
    if(amount<=0) return;
    v.score+=amount;
    grantExtraLifeIfEligible(v);
}
void damagePlayer(PlayerVitals& v,Vec2& velocity) {
    if(v.dead || v.invincible || v.invulnerabilityFrames>0 || v.hurtCooldownFrames>0) return;
    if(v.shield!=Shield::None) { v.shield=Shield::None; v.hasShield=false; }
    else if(v.rings>0) v.rings=0; // Ring scatter is handled by the level object system.
    else { v.dead=true; velocity.y=-6.0f; velocity.x=0.0f; return; }
    v.invulnerabilityFrames=120;
    v.hurtCooldownFrames=30;
    velocity.y=-5.0f;
    if(velocity.x==0.0f) velocity.x=-2.0f;
}
bool TileMap::isSolid(int x,int y) const {
    if(x<0 || y<0 || x>=width || y>=height || tileSize<=0) return false;
    const auto i=static_cast<std::size_t>(y*width+x);
    return i<solid.size() && solid[i]!=0;
}
CollisionResult moveAndCollide(Rect& b,Vec2& v,const TileMap& m) {
    CollisionResult hit;
    if(m.tileSize<=0 || m.width<=0 || m.height<=0) { b.x+=v.x; b.y+=v.y; return hit; }
    b.x+=v.x;
    if(v.x!=0.0f) {
        int left=static_cast<int>(std::floor(b.x/m.tileSize));
        int right=static_cast<int>(std::floor((b.x+b.w-0.001f)/m.tileSize));
        int top=static_cast<int>(std::floor(b.y/m.tileSize));
        int bottom=static_cast<int>(std::floor((b.y+b.h-0.001f)/m.tileSize));
        for(int ty=top;ty<=bottom;++ty) for(int tx=left;tx<=right;++tx) if(m.isSolid(tx,ty)) {
            if(v.x>0) { b.x=tx*m.tileSize-b.w; hit.hitRight=true; }
            else { b.x=(tx+1)*m.tileSize; hit.hitLeft=true; }
            v.x=0.0f;
        }
    }
    b.y+=v.y;
    if(v.y!=0.0f) {
        int left=static_cast<int>(std::floor(b.x/m.tileSize));
        int right=static_cast<int>(std::floor((b.x+b.w-0.001f)/m.tileSize));
        int top=static_cast<int>(std::floor(b.y/m.tileSize));
        int bottom=static_cast<int>(std::floor((b.y+b.h-0.001f)/m.tileSize));
        for(int ty=top;ty<=bottom;++ty) for(int tx=left;tx<=right;++tx) if(m.isSolid(tx,ty)) {
            if(v.y>0) { b.y=ty*m.tileSize-b.h; hit.hitFloor=true; }
            else { b.y=(ty+1)*m.tileSize; hit.hitCeiling=true; }
            v.y=0.0f;
        }
    }
    return hit;
}
bool activateSpring(const Spring& s,const Rect& p,Vec2& v) {
    if(!s.active || !overlaps(s.bounds,p)) return false;
    v=s.launchVelocity; return true;
}
bool breakMonitor(Monitor& m,PlayerVitals& v) {
    if(m.broken) return false;
    m.broken=true;
    switch(m.type) {
        case MonitorType::Rings: collectRing(v,10); break;
        case MonitorType::Shield: v.shield=Shield::Standard; v.hasShield=true; break;
        case MonitorType::ExtraLife: ++v.lives; break;
        case MonitorType::Speed: v.invulnerabilityFrames=std::max(v.invulnerabilityFrames,600); break;
        case MonitorType::Invincibility: v.invincible=true; v.invulnerabilityFrames=std::max(v.invulnerabilityFrames,600); break;
    }
    return true;
}
bool activateCheckpoint(Checkpoint& c,const Rect& p) {
    if(c.activated || !overlaps({c.position.x-8,c.position.y-24,16,48},p)) return false;
    c.activated=true; return true;
}
EnemyContact resolveEnemyContact(Enemy& e,const Rect& p,Vec2& v,PlayerVitals& vitals) {
    if(!e.alive || !overlaps(e.bounds,p)) return EnemyContact::None;
    const float playerBottom=p.y+p.h;
    if(v.y>0.0f && playerBottom-e.bounds.y<12.0f) {
        e.alive=false; v.y=-6.0f; awardScore(vitals,100); return EnemyContact::Stomped;
    }
    damagePlayer(vitals,v); return EnemyContact::HurtPlayer;
}
void followPlayer(CameraState& c,const Vec2& p,float lw,float lh,float smoothing) {
    smoothing=std::clamp(smoothing,0.0f,1.0f);
    float tx=p.x-c.viewportWidth*0.5f, ty=p.y-c.viewportHeight*0.5f;
    tx=std::clamp(tx,0.0f,std::max(0.0f,lw-c.viewportWidth));
    ty=std::clamp(ty,0.0f,std::max(0.0f,lh-c.viewportHeight));
    c.position.x+=(tx-c.position.x)*smoothing;
    c.position.y+=(ty-c.position.y)*smoothing;
}
void collectEmerald(StageProgress& p) {
    if(p.emeralds<7) ++p.emeralds;
    p.specialStageUnlocked=true;
    p.allEmeraldsCollected=p.emeralds>=7;
}
void enterWater(WaterState& w,int duration) {
    w.underwater=true; w.airFramesRemaining=std::max(1,duration);
    w.drowningWarning=false; w.drowned=false;
}
void collectAirBubble(WaterState& w,int refill) {
    if(!w.underwater || w.drowned) return;
    w.airFramesRemaining=std::max(1,refill);
    w.drowningWarning=false; w.hasAirBubble=true;
}
void tickWater(WaterState& w) {
    if(!w.underwater || w.drowned) return;
    if(w.airFramesRemaining>0) --w.airFramesRemaining;
    if(w.airFramesRemaining<=10*60) w.drowningWarning=true;
    if(w.airFramesRemaining<=0) w.drowned=true;
}
void loseLife(GameSession& s) {
    if(s.player.lives>0) --s.player.lives;
    s.player.rings=0; s.player.dead=false;
    s.player.invulnerabilityFrames=0; s.player.hurtCooldownFrames=0;
    if(s.player.lives<=0) s.gameOver=true;
}
} // namespace sonic3
