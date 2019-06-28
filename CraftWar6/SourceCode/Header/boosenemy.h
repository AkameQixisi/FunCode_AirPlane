#ifndef BOOSENEMY_H
#define BOOSENEMY_H

/// boos ´¿ÊôÆ´Ð´´íÎó ÊµÎª boss

#include "basicenemy.h"

class BoosEnemy : public BasicEnemy {
public:
    BoosEnemy(const char* name_);
    virtual ~BoosEnemy();

    static std::shared_ptr<BasicEnemy> creatEnemy(const int id_);

    virtual void onMove(const float deltaTime_);

    virtual bool isOverScreen();
private:

};

#endif // BOOSENEMY_H
