#pragma once
#include <array>
#include <cstdint>
#include <vector>

namespace sonic3 {

struct Vec2 { float x=0.0f, y=0.0f; };
struct Rect { float x=0.0f, y=0.0f, w=0.0f, h=0.0f; };
bool overlaps(const Rect& a, const Rect& b);

enum class Character : std::uint8_t { Sonic, Tails, Knuckles };
enum class Shield : std::uint8_t { None, Standard, Fire, Water, Lightning };
enum class Ability : std::uint8_t { None, FireDash, BubbleBounce, DoubleJump, Fly, Swim, Glide, Climb };

struct CharacterAbilities {
    bool canFly=false, canSwim=false, canGlide=false, canClimb=false;
    bool canFireDash=false, canBubbleBounce=false, canDoubleJump=false;
};
CharacterAbilities abilitiesFor(Character character, Shield shield);

struct PlayerVitals {
    int rings=0, score=0, lives=3;
    int invulnerabilityFrames=0, hurtCooldownFrames=0;
    bool dead=false, hasShield=false, invincible=false;
    Shield shield=Shield::None;
};
void tickVitals(PlayerVitals& vitals);
void collectRing(PlayerVitals& vitals, int amount=1);
void awardScore(PlayerVitals& vitals, int amount);
void damagePlayer(PlayerVitals& vitals, Vec2& velocity);
void grantExtraLifeIfEligible(PlayerVitals& vitals);

struct TileMap {
    int width=0, height=0, tileSize=16;
    std::vector<std::uint8_t> solid;
    bool isSolid(int tileX, int tileY) const;
};
struct CollisionResult {
    bool hitLeft=false, hitRight=false, hitCeiling=false, hitFloor=false;
};
CollisionResult moveAndCollide(Rect& body, Vec2& velocity, const TileMap& map);

struct Spring {
    Rect bounds;
    Vec2 launchVelocity{0.0f,-12.0f};
    bool active=true;
};
bool activateSpring(const Spring& spring, const Rect& player, Vec2& velocity);

enum class MonitorType : std::uint8_t { Rings, Shield, ExtraLife, Speed, Invincibility };
struct Monitor {
    Rect bounds;
    MonitorType type=MonitorType::Rings;
    bool broken=false;
};
bool breakMonitor(Monitor& monitor, PlayerVitals& vitals);

struct Checkpoint {
    Vec2 position;
    bool activated=false;
};
bool activateCheckpoint(Checkpoint& checkpoint, const Rect& player);

struct Enemy {
    Rect bounds;
    bool alive=true;
};
enum class EnemyContact : std::uint8_t { None, Stomped, HurtPlayer };
EnemyContact resolveEnemyContact(Enemy& enemy, const Rect& player,
                                 Vec2& playerVelocity, PlayerVitals& vitals);

struct CameraState {
    Vec2 position;
    float viewportWidth=424.0f, viewportHeight=240.0f;
};
void followPlayer(CameraState& camera, const Vec2& playerCenter,
                  float levelWidth, float levelHeight, float smoothing=1.0f);

struct StageProgress {
    int emeralds=0;
    bool specialStageUnlocked=false;
    bool allEmeraldsCollected=false;
};
void collectEmerald(StageProgress& progress);

struct WaterState {
    bool underwater=false, hasAirBubble=false;
    int airFramesRemaining=0;
    bool drowningWarning=false, drowned=false;
};
void enterWater(WaterState& water, int airDurationFrames=30*60);
void collectAirBubble(WaterState& water, int refillFrames=30*60);
void tickWater(WaterState& water);

struct GameSession {
    int zone=0, act=1;
    bool paused=false, finished=false, gameOver=false;
    PlayerVitals player;
    Checkpoint checkpoint;
    StageProgress progress;
};
void loseLife(GameSession& session);

} // namespace sonic3
