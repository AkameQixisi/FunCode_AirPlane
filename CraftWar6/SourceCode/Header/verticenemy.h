#ifndef VERTICENEMY_H
#define VERTICENEMY_H

#include "basicenemy.h"

class VerticEnemy : public BasicEnemy {
public:
    VerticEnemy(const char* name_);
    virtual ~VerticEnemy();

    static std::shared_ptr<BasicEnemy> creatEnemy(const int id_);

    virtual void onMove(const float deltaTime_);

    virtual bool isOverScreen();
private:

};


#endif // VERTICENEMY_H

