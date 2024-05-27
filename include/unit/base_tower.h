#ifndef BASE_TOWER_H
#define BASE_TOWER_H


#include "utils/enemy_state.h"
#include "utils/grid_type.h"
#include "unit/base_unit.h"
#include <vector>

class Tower : public Unit {
  public:
    GridType _gridType;
};

#endif // BASE_TOWER_H
