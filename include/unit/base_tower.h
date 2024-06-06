#ifndef BASE_TOWER_H
#define BASE_TOWER_H

#include "unit/base_unit.h"
#include "utils/enemy_state.h"
#include "utils/tower_state.h"
#include <vector>

class Tower : public Unit {
  public:
    // 绘图
    virtual void draw(QPainter *painter) = 0;

    // 逻辑
    GridType _gridType;
    TowerState _state;

    virtual void attack() = 0;
    virtual void idle() = 0;

    virtual void buffFury() {
        if (_buffSlot[0] == -1) {
            _buffSlot[0] = 0;
        } else if (_buffSlot[1] == -1) {
            _buffSlot[1] = 0;
        }

        _damage *= 10;
        _attackSpeed /= 2;
    }
    virtual void debuffFury() {
        if (_buffSlot[0] == 0) {
            _buffSlot[0] = -1;
        } else if (_buffSlot[1] == 0) {
            _buffSlot[1] = -1;
        }
        _damage /= 10;
        _attackSpeed *= 2;
    }
    virtual void buffIce() {
        if (_buffSlot[0] == -1) {
            _buffSlot[0] = 1;
        } else if (_buffSlot[1] == -1) {
            _buffSlot[1] = 1;
        }
    }
    virtual void debuffIce() {
        if (_buffSlot[0] == 1) {
            _buffSlot[0] = -1;
        } else if (_buffSlot[1] == 1) {
            _buffSlot[1] = -1;
        }
    }
    virtual void buffAoE() {
        if (_buffSlot[0] == -1) {
            _buffSlot[0] = 2;
        } else if (_buffSlot[1] == -1) {
            _buffSlot[1] = 2;
        }
    }
    virtual void debuffAoE() {
        if (_buffSlot[0] == 2) {
            _buffSlot[0] = -1;
        } else if (_buffSlot[1] == 2) {
            _buffSlot[1] = -1;
        }
    }
    virtual void buffBleed() {
        if (_buffSlot[0] == -1) {
            _buffSlot[0] = 3;
        } else if (_buffSlot[1] == -1) {
            _buffSlot[1] = 3;
        }
    }
    virtual void debuffBleed() {
        if (_buffSlot[0] == 3) {
            _buffSlot[0] = -1;
        } else if (_buffSlot[1] == 3) {
            _buffSlot[1] = -1;
        }
    }
};

#endif // BASE_TOWER_H

/*
    void buffFury();
    void buffIce();
    void buffAoE();
    void buffBleed();
    void buffJump();
    void buffSpeed();
*/