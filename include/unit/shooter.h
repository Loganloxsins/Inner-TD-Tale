#include "unit/base_enemy.h"
#include "unit/base_tower.h"
#include "unit/base_unit.h"

class Shooter : public Tower {
  public:
    vector<Enemy *> &_enemies; // 场景中所有敌人
    Enemy *_target_enemy; // 要攻击的目标敌人 可以有不同的选择策略
    Shooter(int x, int y, vector<Enemy *> &enemies);
    void draw(QPainter *painter) override;
    void idle() override;
    void attack() override;
};