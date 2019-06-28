#ifndef ENEMYSTOOL_H
#define ENEMYSTOOL_H

#include "basicenemy.h"
#include <list>

class EnemysTool {
public:
    EnemysTool();
    virtual ~EnemysTool();

    // 创建敌机
    virtual void creatEnemy(const float deltaTime_);

    virtual void onLooop(const float deltaTime_);

    // 敌机列表，基类指针
    std::list<std::shared_ptr<BasicEnemy>> enemys;

private:
    int enemyId;

    float deltaCreatTime;
};


#endif // ENEMYSTOOL_H
