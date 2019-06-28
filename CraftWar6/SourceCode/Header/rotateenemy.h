#ifndef ROTATEENEMY_H
#define ROTATEENEMY_H

#include "basicenemy.h"

class RotateEnemy : public BasicEnemy {
public:
    RotateEnemy(const char* name_);
    virtual ~RotateEnemy();

    static std::shared_ptr<BasicEnemy> creatEnemy(const int id_);

    virtual void onMove(const float deltaTime_);

    virtual bool isOverScreen();
private:

};


#endif // ROTATEENEMY_H
