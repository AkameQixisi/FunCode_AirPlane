#include "bullet.h"
#include <sstream>

Bullet::Bullet(const char* name_)
    : MoveObject(name_) {
    beenDownId = 0;
    setHp(1);
}

Bullet::~Bullet() {}


bool Bullet::isOverScreen() {
    return ((GetSpritePositionX() <= CSystem::GetScreenLeft() - 10) || (GetSpritePositionX() >= CSystem::GetScreenRight() + 10));
}

void Bullet::beenDown() {
    std::stringstream ss;
	ss << "enemyDown_" << beenDownId++;
    std::string str;
    ss >> str;

	std::shared_ptr<CSprite> bd = std::make_shared<CSprite>(str.c_str());
	bd->CloneSprite("bulletDown");
	bd->SetSpriteLifeTime(0.2);
	bd->SetSpritePosition(GetSpritePositionX(), GetSpritePositionY());
}
