#ifndef MELEE_TOWER_H
#define MELEE_TOWER_H


#include "include/all_include.h"


class MeleeTower : public Tower {
public:
    MeleeTower(int health, int attackPower, int range) : Tower(health, attackPower, range) {}
    void move() override {}
    void place(int x, int y) override;
};

#endif // MELEE_TOWER_H
