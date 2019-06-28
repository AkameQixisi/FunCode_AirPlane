#ifndef MYCRAFT_H
#define MYCRAFT_H

#include "basiccraft.h"

class MyCraft : public BasicCraft {
public:
    MyCraft(const char* name_);
    virtual ~MyCraft();

    virtual void onMove(const float deltaTime_) {}
    virtual void onMove(const bool isKeyDown_, const int key_);

    virtual std::shared_ptr<Bullet> onFire(const float deltaTime_);

    virtual void beenDown();

    virtual void setScore(const int val) { score = val; }
    virtual int getScore() {return score; }

private:
    virtual std::shared_ptr<Bullet> fire();

    float left;
    float right;
    float up;
    float down;

    int score;
};

#endif // MYCRAFT_H
