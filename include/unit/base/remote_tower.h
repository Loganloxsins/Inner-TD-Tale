#ifndef REMOTE_TOWER_H
#define REMOTE_TOWER_H


#include "include/all_include.h"

class RangedTower : public Tower {
  public:
    RangedTower(int health, int attackPower, int range)
        : Tower(health, attackPower, range) {}
    void move() override {}
    void place(int x, int y) override;
};

#endif // REMOTE_TOWER_H
