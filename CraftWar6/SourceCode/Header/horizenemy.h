#ifndef HORIZENEMY
#define HORIZENEMY

#include "basicenemy.h"

class HorizEnemy : public BasicEnemy {
public:
    HorizEnemy(const char* name_);
    virtual ~HorizEnemy();

    // 创建敌机
    static std::shared_ptr<BasicEnemy> creatEnemy(const int id_);

    virtual void onMove(const float deltaTime_);

    virtual bool isOverScreen();
private:

};

#endif // HORIZENEMY
