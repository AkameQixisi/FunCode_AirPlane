#ifndef BASICENEMY_H
#define BASICENEMY_H

#include "basiccraft.h"

class BasicEnemy : public BasicCraft {
public:
    BasicEnemy(const char* name_);
    virtual ~BasicEnemy();


    virtual void onMove(const float deltaTime_) = 0;

    virtual std::shared_ptr<Bullet> onFire(const float deltaTime_);

    // 判断是否飞出屏幕
    virtual bool isOverScreen() = 0;

    virtual void beenDown();

protected:
    virtual std::shared_ptr<Bullet> fire();

    float deltaMoveTime;

    bool increMove;

    int beenDownId;
};

#endif // BASICENEMY_H
