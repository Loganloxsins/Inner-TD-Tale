#ifndef BASE_UNIT_H
#define BASE_UNIT_H

#include "map/map.h"
#include <QPainter>
#include <QString>
#include <vector>

// Interface for all units
class Unit {

  public:
    int _x, _y;
    int _hp_full, _hp_cur;
    QString _pic_path;
    Map *_map;

    // 绘制函数接口
    virtual void draw(QPainter *painter) = 0;
    // virtual void move() = 0;
    // virtual void attack(Unit *target) = 0;
    // virtual bool isAlive() const { return health > 0; }
    // void receiveDamage(int damage) { health -= damage; }
};

#endif // BASE_UNIT_H
