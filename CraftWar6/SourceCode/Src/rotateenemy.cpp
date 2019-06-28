#include "rotateenemy.h"
#include <sstream>

RotateEnemy::RotateEnemy(const char* name_)
    : BasicEnemy(name_) {
    deltaMoveTime = 0;
    increMove = true;
    setHp(1);
}

RotateEnemy::~RotateEnemy() {}

// �����л�
std::shared_ptr<BasicEnemy> RotateEnemy::creatEnemy(const int id_) {
    std::stringstream ss;
    ss << "rotateEnemy_" << id_;
    std::string str;
    ss >> str;
    std::shared_ptr<BasicEnemy> pe = std::make_shared<RotateEnemy>(str.c_str());
    pe->CloneSprite("RotateSprite_Template");  //��¡ģ��
    pe->SetSpritePosition(static_cast<float>(CSystem::GetScreenLeft() - 20),
                            CSystem::RandomRange(static_cast<int>(CSystem::GetScreenTop()),
                                                static_cast<int>(CSystem::GetScreenBottom() ) ) );
    pe->SetSpriteLinearVelocityX(10);
    // �������������Ե����Ϊ�ֶ��ж�ɾ��
    return pe;
}

void RotateEnemy::onMove(const float deltaTime_) {
   if (increMove) {
        deltaMoveTime += deltaTime_;
        if (deltaMoveTime >= 2) increMove = false;
    } else {
        deltaMoveTime -= deltaTime_;
        if (deltaMoveTime <= -2) increMove = true;
    }
    SetSpriteLinearVelocityY(deltaMoveTime * 2);
}


bool RotateEnemy::isOverScreen() {
    return GetSpritePositionX() >= CSystem::GetScreenRight() + 10;
}


