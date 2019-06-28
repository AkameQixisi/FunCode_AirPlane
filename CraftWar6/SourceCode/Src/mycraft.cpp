#include "mycraft.h"
#include "bullet.h"
#include <sstream>

MyCraft::MyCraft(const char* name_)
    : BasicCraft(name_) {
    left = 0;
    right = 0;
    up = 0;
    down = 0;
    setHp(5); /// OK
    setScore(0);
}

MyCraft::~MyCraft() {}

void MyCraft::onMove(const bool isKeyDown_, const int key_)  {
    if (isKeyDown_) {
        switch(key_) {
        case KEY_A:
            left = 30;
            break;
        case KEY_D:
            right =	30;
            break;
        case KEY_W:
            up = 15;
            break;
        case KEY_S:
            down = 15;
            break;
        }
    } else {
        switch(key_) {
        case KEY_A:
            left = 0;
            break;
        case KEY_D:
            right =	0;
            break;
        case KEY_W:
            up = 0;
            break;
        case KEY_S:
            down = 0;
            break;
        }
    }
    float x	= right - left;
    float y = down - up;
    SetSpriteLinearVelocity(x, y);
}

std::shared_ptr<Bullet> MyCraft::fire() {
    std::stringstream ss;
	ss << "myBullet_" << bulletId++;
    std::string str;
    ss >> str;
	std::shared_ptr<Bullet> pb = std::make_shared<Bullet>(str.c_str());
	pb->CloneSprite("Bullet1_Template");
	pb->SetSpritePosition(GetSpritePositionX(), GetSpritePositionY());
    pb->SetSpriteFlipX(true);
    pb->SetSpriteLinearVelocityX(60);
    return pb;
}

std::shared_ptr<Bullet> MyCraft::onFire(const float deltaTime_) {
    deltaFireTime -= deltaTime_;
    if (deltaFireTime <= 0 && isFire) {
        // 固定发射时间
        deltaFireTime	=	0.3;
        return fire();
    }
    return nullptr;
}


void MyCraft::beenDown() {
    std::string str = "playerIsDead";
	std::shared_ptr<CSprite> bd = std::make_shared<CSprite>(str.c_str());
	bd->CloneSprite("playerExplode");
	bd->SetSpriteLifeTime(1);
	bd->SetSpritePosition(GetSpritePositionX(), GetSpritePositionY());

	std::shared_ptr<CSprite> bd2 = std::make_shared<CSprite>((str + "_").c_str());
	bd2->CloneSprite("bulletDown");
	bd2->SetSpriteLifeTime(1);
	bd2->SetSpritePosition(GetSpritePositionX(), GetSpritePositionY());
}
