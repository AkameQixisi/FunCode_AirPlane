#include "horizenemy.h"
#include <sstream>

HorizEnemy::HorizEnemy(const char* name_)
    : BasicEnemy(name_) {
    deltaMoveTime = 0;
    increMove = true;
    setHp(1);
}

HorizEnemy::~HorizEnemy() {}

// 创建敌机
std::shared_ptr<BasicEnemy> HorizEnemy::creatEnemy(const int id_) {
    std::stringstream ss;
    ss << "horizEnemy_" << id_;
    std::string str;
    ss >> str;
    std::shared_ptr<BasicEnemy> pe = std::make_shared<HorizEnemy>(str.c_str());
    pe->CloneSprite("HorizontalSprite_Template");  //克隆模板
    pe->SetSpritePosition(static_cast<float>(CSystem::GetScreenRight() + 20),
                            CSystem::RandomRange(static_cast<int>(CSystem::GetScreenTop()),
                                                static_cast<int>(CSystem::GetScreenBottom() ) ) );
    pe->SetSpriteLinearVelocityX(-10);
    // 不用设置世界边缘，因为手动判断删除
    return pe;
}

void HorizEnemy::onMove(const float deltaTime_) {
    if (increMove) {
        deltaMoveTime += deltaTime_;
        if (deltaMoveTime >= 2) increMove = false;
    } else {
        deltaMoveTime -= deltaTime_;
        if (deltaMoveTime <= -2) increMove = true;
    }
    SetSpriteLinearVelocityY(deltaMoveTime * 3);
}


bool HorizEnemy::isOverScreen() {
    return GetSpritePositionX() <= CSystem::GetScreenLeft() - 10;
}
