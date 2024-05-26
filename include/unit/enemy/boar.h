#ifndef BOAR_H
#define BOAR_H

#include "unit/base/base_enemy.h"
#include <vector>
#include <QPoint>
#include <QVector>
#include <QPainter>
class Boar : public Enemy {
  public:
  
    Boar(int hp, int speed, std::vector<std::pair<int, int>> path);

    void move() override;
    void draw(QPainter *painter) override;

};

#endif // BOAR_H
