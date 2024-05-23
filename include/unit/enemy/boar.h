#ifndef BOAR_H
#define BOAR_H

#include "base_enemy.h"
class Boar : public Enemy {
  public:
    Boar(int health, int attackPower, int speed)
        : Enemy(health, attackPower, speed) {}
    void move() override;
    void attack(Unit *target) override;
};

#endif // BOAR_H