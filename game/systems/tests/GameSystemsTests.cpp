#include "../GameSystems.hpp"
#include <cassert>
using namespace sonic3;
int main() {
    PlayerVitals v;
    collectRing(v,100); assert(v.lives==4 && v.rings==0);
    awardScore(v,50000); assert(v.lives==5 && v.score==0);
    Vec2 knockback{};
    damagePlayer(v,knockback); assert(v.rings==0 && !v.dead);
    assert(abilitiesFor(Character::Tails,Shield::None).canFly);
    assert(abilitiesFor(Character::Knuckles,Shield::None).canGlide);
    assert(abilitiesFor(Character::Sonic,Shield::Fire).canFireDash);
    TileMap map; map.width=8; map.height=8; map.tileSize=16; map.solid.resize(64);
    for(int x=0;x<8;++x) map.solid[6*8+x]=1;
    Rect body{20,70,12,12}; Vec2 vel{0,10};
    auto collision=moveAndCollide(body,vel,map);
    assert(collision.hitFloor && vel.y==0);
    Spring spring{{20,50,20,10},{0,-12},true};
    assert(activateSpring(spring,{22,52,8,8},vel) && vel.y==-12);
    Monitor monitor{{0,0,16,16},MonitorType::Rings,false};
    assert(breakMonitor(monitor,v) && v.rings==10);
    Checkpoint cp{{10,10},false};
    assert(activateCheckpoint(cp,{5,0,10,20}));
    Enemy enemy{{0,0,20,20},true}; Vec2 jump{0,4};
    assert(resolveEnemyContact(enemy,{2,-10,10,10},jump,v)==EnemyContact::Stomped);
    StageProgress progress; for(int i=0;i<7;++i) collectEmerald(progress);
    assert(progress.allEmeraldsCollected);
    WaterState water; enterWater(water,2); tickWater(water); assert(!water.drowned);
    tickWater(water); assert(water.drowned);
    CameraState camera; followPlayer(camera,{200,100},1000,500,1.0f);
    assert(camera.position.x>=0 && camera.position.y>=0);
    GameSession session; session.player.lives=1; loseLife(session); assert(session.gameOver);
    return 0;
}
