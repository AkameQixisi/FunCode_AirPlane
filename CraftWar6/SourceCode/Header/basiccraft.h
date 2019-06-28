#ifndef BASICCRAFT_H
#define BASICCRAFT_H

#include "moveobject.h"
#include "bullet.h"
#include <list>

class BasicCraft : public MoveObject {
public:
    BasicCraft(const char* name_);
    virtual ~BasicCraft();

    virtual void onMove(const float deltaTime_) = 0;

    virtual std::shared_ptr<Bullet> onFire(const float deltaTime_) = 0;

    virtual void setFire(const bool fire_) { isFire = fire_; }
    virtual bool getFire() const { return isFire; }

    virtual void beenDown() = 0;


protected:
    virtual std::shared_ptr<Bullet> fire() = 0;

    float deltaFireTime;

    int bulletId;

    bool isFire;
};

#endif // BASICCRAFT_H
