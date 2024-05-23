#ifndef BASE_TOWER_H
#define BASE_TOWER_H

#include "base_unit.h"
#include "grid.h"
#include <vector>

class Tower : public Unit {
  protected:
    int range;

  public:
    Tower(int health, int attackPower, int range)
        : Unit(health, attackPower), range(range) {}
    virtual void place(int x, int y) = 0;
    virtual void attack(Unit *target) override;
};

#endif // BASE_TOWER_H