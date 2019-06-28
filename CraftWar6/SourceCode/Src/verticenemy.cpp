#include "verticenemy.h"
#include <sstream>

VerticEnemy::VerticEnemy(const char* name_)
    : BasicEnemy(name_) {
    deltaMoveTime = 0;
    increMove = true;
    setHp(1);
}

VerticEnemy::~VerticEnemy() {}

// 创建敌机
std::shared_ptr<BasicEnemy> VerticEnemy::creatEnemy(const int id_) {
    std::stringstream ss;
    ss << "verticEnemy_" << id_;
    std::string str;
    ss >> str;
    std::shared_ptr<BasicEnemy> pe = std::make_shared<VerticEnemy>(str.c_str());
    pe->CloneSprite("VerticalSprite_Template");  //克隆模板
    pe->SetSpritePosition(CSystem::RandomRange(static_cast<int>(CSystem::GetScreenLeft() + 50),
                                                static_cast<int>(CSystem::GetScreenRight()) ),
                            static_cast<float>(CSystem::GetScreenBottom() + 10) );
    pe->SetSpriteLinearVelocityY(-10);
    // 不用设置世界边缘，因为手动判断删除
    return pe;
}

void VerticEnemy::onMove(const float deltaTime_) {
   if (increMove) {
        deltaMoveTime += deltaTime_;
        if (deltaMoveTime >= 1) increMove = false;
    } else {
        deltaMoveTime -= deltaTime_;
        if (deltaMoveTime <= -1) increMove = true;
    }
    SetSpriteLinearVelocityX(deltaMoveTime * 4);
}


bool VerticEnemy::isOverScreen() {
    return GetSpritePositionY() <= CSystem::GetScreenTop() - 10;
}


