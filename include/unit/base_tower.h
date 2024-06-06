#ifndef BASE_TOWER_H
#define BASE_TOWER_H

#include "unit/base_unit.h"
#include "utils/enemy_state.h"
#include "utils/tower_state.h"
#include <vector>

class Tower : public Unit {
  public:
    GridType _gridType;
    TowerState _state;

    virtual void attack() = 0;
    virtual void idle() = 0;

    // 绘图
    virtual void draw(QPainter *painter) = 0;
    virtual void buffFury() { _damage *= 10; }
};

#endif // BASE_TOWER_H
