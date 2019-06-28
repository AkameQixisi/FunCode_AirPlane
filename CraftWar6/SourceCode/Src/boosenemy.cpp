#include "boosenemy.h"
#include <sstream>

BoosEnemy::BoosEnemy(const char* name_)
    : BasicEnemy(name_) {
    deltaMoveTime = 0;
    increMove = true;
    setHp(3);
}

BoosEnemy::~BoosEnemy() {}

// �����л�
std::shared_ptr<BasicEnemy> BoosEnemy::creatEnemy(const int id_) {
    std::stringstream ss;
    ss << "boosEnemy_" << id_;
    std::string str;
    ss >> str;
    std::shared_ptr<BasicEnemy> pe = std::make_shared<BoosEnemy>(str.c_str());
    pe->CloneSprite("BigBoss_Template");  //��¡ģ��
    pe->SetSpritePosition(static_cast<float>(CSystem::GetScreenRight() + 20),
                            CSystem::RandomRange(static_cast<int>(CSystem::GetScreenTop()),
                                                static_cast<int>(CSystem::GetScreenBottom() ) ) );
    pe->SetSpriteLinearVelocityX(-10);
    // �������������Ե����Ϊ�ֶ��ж�ɾ��
    return pe;
}

void BoosEnemy::onMove(const float deltaTime_) {
    if (increMove) {
        deltaMoveTime += deltaTime_;
        if (deltaMoveTime >= 2) increMove = false;
    } else {
        deltaMoveTime -= deltaTime_;
        if (deltaMoveTime <= -2) increMove = true;
    }
    SetSpriteLinearVelocityY(deltaMoveTime * 3);
}


bool BoosEnemy::isOverScreen() {
    return GetSpritePositionX() <= CSystem::GetScreenLeft() - 10;
}

