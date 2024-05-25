#ifndef BOAR_H
#define BOAR_H


#include "include/all_include.h"
class Boar : public Enemy {
  public:
    Boar(int health, int attackPower, int speed)
        : Enemy(health, attackPower, speed) {}
    void move() override;
    void attack(Unit *target) override;
};

#endif // BOAR_H
