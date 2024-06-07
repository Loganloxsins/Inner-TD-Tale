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
    void drawBloodBar(QPainter *painter) {
        // 保存当前的 painter 状态
        painter->save();

        if (_hp_cur > 0) {
            double hp_ratio = (double)_hp_cur / _hp_full;
            QColor hp_color;
            if (hp_ratio > 0.6) {
                hp_color = Qt::green;
            } else if (hp_ratio > 0.3) {
                hp_color = Qt::yellow;
            } else {
                hp_color = Qt::red;
            }
            painter->setBrush(hp_color);
            painter->drawRect(_x * GRID_SIZE, _y * GRID_SIZE - 10,
                              60 * hp_ratio, 5);
            painter->setBrush(Qt::gray);
            painter->drawRect(_x * GRID_SIZE + 60 * hp_ratio,
                              _y * GRID_SIZE - 10, 60 * (1 - hp_ratio), 5);
        }

        // 恢复到之前保存的状态
        painter->restore();
    }

    void drawSelectionBox(QPainter *painter) {
        // 保存当前的 painter 状态
        painter->save();

        if (_isHighlighted) {
            QPen pen(Qt::yellow);
            pen.setWidth(3);
            painter->setPen(pen);
            painter->drawRect(_x * GRID_SIZE, _y * GRID_SIZE, 60, 60);
        }

        // 恢复到之前保存的状态
        painter->restore();
    }

    // 逻辑相关
    int _hp_full, _hp_cur;
    int _attackRange;
    int _damage;
    Map *_map;
    int _attackSpeed;
    int _attackCoolDown;
    int _buff_num = 0;
    // int长度为2的数组，存储已经加的buff的种类
    int _buffSlot[2];

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
