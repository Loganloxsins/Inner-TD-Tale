#ifndef BASE_UNIT_H
#define BASE_UNIT_H

#include "map/map.h"
#include <QPainter>
#include <QString>
#include <vector>

// Interface for all units
class Unit {

  public:
    // 绘制相关
    int _x, _y;
    QString _pic_path;
    bool _isHighlighted = false;
    virtual void draw(QPainter *painter) = 0;
    bool contains(const QPoint &point) {
        QRect enemyRect(_x * GRID_SIZE, _y * GRID_SIZE, 60, 60);
        return enemyRect.contains(point);
    };
    void highlight() { _isHighlighted = !_isHighlighted; };

    // 逻辑相关
    int _hp_full, _hp_cur;
    int _attackRange;
    int _damage;
    Map *_map;

    virtual bool isAlive() const { return _hp_cur > 0; }
    virtual void receiveDamage(int damage) {
        if (_hp_cur > damage)
            _hp_cur -= damage;
        else
            _hp_cur = 0;
    }
    // 判断是否在攻击范围内
    virtual bool isInRange(Unit *target) {
        return (target->_x - _x) * (target->_x - _x) +
                   (target->_y - _y) * (target->_y - _y) <=
               _attackRange * _attackRange;
    }
};

#endif // BASE_UNIT_H
