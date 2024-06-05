#ifndef BOAR_H
#define BOAR_H

#include "unit/base_enemy.h"
#include <QPainter>
#include <QPoint>
#include <QVector>
#include <vector>
class Boar : public Enemy {
  public:
    // vector<Tower *> &_tower_all; // 场景中所有塔
    // Tower *_target_tower; // 要攻击的目标敌人 可以有不同的选择策略

    Boar(int hp, int speed, std::vector<std::pair<int, int>> path, Map *map);

    void move() override;
    void draw(QPainter *painter) override;
    void attack() override;
};

#endif // BOAR_H
