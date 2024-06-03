#include "unit/base_tower.h"
#include "unit/base_unit.h"

class Knight : public Tower {
  public:
    Knight(int x,int y,int hp, int attackPower, int range);
    void draw(QPainter *painter) override;
    
};
