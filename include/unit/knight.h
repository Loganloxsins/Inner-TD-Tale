#include "unit/base_tower.h"
#include "unit/base_unit.h"

class Knight : public Tower {
  public:
    Knight(int hp, int attackPower, int range);
    void draw(QPainter *painter) override;
    
};