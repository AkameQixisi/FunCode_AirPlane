#include "basicenemy.h"
#include "bullet.h"
#include <sstream>

BasicEnemy::BasicEnemy(const char* name_)
    : BasicCraft(name_), increMove(true) {
    isFire = true;
    deltaMoveTime = 0;
    increMove = true;
    beenDownId = 0;
}

BasicEnemy::~BasicEnemy() {}

std::shared_ptr<Bullet> BasicEnemy::fire() {
    std::stringstream ss;
	ss << "enemyBullet_" << bulletId++;
    std::string str;
    ss >> str;
	std::shared_ptr<Bullet> pb = std::make_shared<Bullet>(str.c_str());
	pb->CloneSprite("Bullet1_Template");
	pb->SetSpritePosition(GetSpritePositionX(), GetSpritePositionY());
    pb->SetSpriteFlipX(false);
    pb->SetSpriteLinearVelocityX(-30);
    pb->SetSpriteWorldLimit(WORLD_LIMIT_NULL, CSystem::GetScreenLeft()-10, CSystem::GetScreenTop(), CSystem::GetScreenRight() + 200, CSystem::GetScreenBottom());
    return pb;

}

std::shared_ptr<Bullet> BasicEnemy::onFire(const float deltaTime_) {
    deltaFireTime -= deltaTime_;
    if (deltaFireTime <= 0 && isFire) {
        // 固定发射时间
        deltaFireTime	=	2;
        return fire();
    }
    return nullptr;
}

void BasicEnemy::beenDown() {
    std::stringstream ss;
	ss << "enemyDown_" << beenDownId++;
    std::string str;
    ss >> str;

	std::shared_ptr<CSprite> bd = std::make_shared<CSprite>(str.c_str());
	bd->CloneSprite("enemyExplode");
	bd->SetSpriteLifeTime(1);
	bd->SetSpritePosition(GetSpritePositionX(), GetSpritePositionY());

	std::shared_ptr<CSprite> bd2 = std::make_shared<CSprite>((str + "_").c_str());
	bd2->CloneSprite("bulletDown");
	bd2->SetSpriteLifeTime(0.3);
	bd2->SetSpritePosition(GetSpritePositionX(), GetSpritePositionY());
}
