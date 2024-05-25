#ifndef BASE_UNIT_H
#define BASE_UNIT_H

#include "include/all_include.h"
#include <vector>


class Unit {
protected:
    int health;
    int attackPower;
public:
    Unit(int health, int attackPower) : health(health), attackPower(attackPower) {}
    virtual void move() = 0;
    virtual void attack(Unit* target) = 0;
    virtual bool isAlive() const { return health > 0; }
    void receiveDamage(int damage) { health -= damage; }
};

#endif // BASE_UNIT_H
