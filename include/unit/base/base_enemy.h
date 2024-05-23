#ifndef BASE_ENEMY_H
#define BASE_ENEMY_H


#include "base_unit.h"
#include "grid.h"
#include <vector>

class Enemy : public Unit {
private:
    int speed;
public:
    Enemy(int health, int attackPower, int speed) : Unit(health, attackPower), speed(speed) {}
    void move() override;
    void attack(Unit* target) override;
};

#endif // BASE_ENEMY_H