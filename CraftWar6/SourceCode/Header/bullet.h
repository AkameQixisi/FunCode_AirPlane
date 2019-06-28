#ifndef BULLET_H
#define BULLET_H

#include "moveobject.h"

class Bullet : public MoveObject {
public:
    Bullet(const char* name_);
    virtual ~Bullet();

    virtual void onMove(const float deltaTime_) {}

    virtual bool isOverScreen();

    virtual void beenDown();

private:
    int beenDownId;
};

#endif // BULLET_H
