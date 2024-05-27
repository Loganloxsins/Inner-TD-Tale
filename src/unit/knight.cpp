#include "unit/knight.h"
#include "unit/base_tower.h"

Knight::Knight(int hp, int attackPower, int range) {
    _hp_full = hp;
    _hp_cur = hp;
    _attackRange=range;
    _gridType = GridType::PATH;

    _pic_path =
        R"(E:\MyProject\s6\cpp_final_proj\Inner-TD-Tale\assets\monster1.png)";

    _x = -1;
    _y = -1;
}

void Knight::draw(QPainter *painter) {
    QPixmap pixmap(_pic_path);

    painter->drawPixmap(_x * GRID_SIZE, _y * GRID_SIZE, 60, 60, pixmap);
}
