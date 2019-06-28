#include "enemystool.h"
#include "horizenemy.h"
#include "rotateenemy.h"
#include "verticenemy.h"
#include "boosenemy.h"

EnemysTool::EnemysTool() : enemyId(0), deltaCreatTime(0){}
EnemysTool::~EnemysTool() {}

// 创建敌机
void EnemysTool::creatEnemy(const float deltaTime_) {
    deltaCreatTime -= deltaTime_;
    if (deltaCreatTime < 0) {
        if (enemyId % 1 == 0) {
            std::shared_ptr<BasicEnemy> phe(HorizEnemy::creatEnemy(enemyId++));
            enemys.push_back(phe);
        }
        if (enemyId % 5 == 0) {
            std::shared_ptr<BasicEnemy> pre(RotateEnemy::creatEnemy(enemyId++));
            enemys.push_back(pre);
        }
        if (enemyId % 3 == 0) {
            std::shared_ptr<BasicEnemy> pve(VerticEnemy::creatEnemy(enemyId++));
            enemys.push_back(pve);
        }
        if (enemyId % 10 == 0) {
            std::shared_ptr<BasicEnemy> pbe(BoosEnemy::creatEnemy(enemyId++));
            enemys.push_back(pbe);
        }
        deltaCreatTime = 2;
    }
}

void EnemysTool::onLooop(const float deltaTime_) {
    // 遍历敌机
    for (auto iter = std::begin(enemys); iter != std::end(enemys); ++iter) {
        if ((*iter)->isOverScreen()) {
            (*iter)->DeleteSprite();
            enemys.erase(iter);
            break;
        }
        if ((*iter) != nullptr) {
            (*iter)->onMove(deltaTime_);
        }
    }
}
