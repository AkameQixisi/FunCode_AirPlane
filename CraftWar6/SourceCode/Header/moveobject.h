#ifndef MOVEOBJECT_H
#define MOVEOBJECT_H

#include "CommonClass.h"
#include <memory>


class MoveObject : public CSprite {
public:
    MoveObject(const char* name_);
    virtual ~MoveObject();

    virtual void onMove(const float deltaTime_) = 0;

    virtual void beenDown() = 0;

    virtual void setHp(const int val) { hp = val; }
    virtual int getHp() { return hp; }

private:
    int hp;

};


#endif // MOVEOBJECT_H
