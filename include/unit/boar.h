#ifndef BOAR_H
#define BOAR_H

#include "unit/base_enemy.h"
#include <QPainter>
#include <QPoint>
#include <QVector>
#include <vector>
class Boar : public Enemy {
  public:
    Boar(int hp, int speed, std::vector<std::pair<int, int>> path);

    void move() override;
    void draw(QPainter *painter) override;
};

#endif // BOAR_H
