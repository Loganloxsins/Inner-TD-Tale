#include "unit/knight.h"
#include "unit/base_tower.h"

Knight::Knight(int x, int y, int hp, int attackPower, int range) {
    _hp_full = hp;
    _hp_cur = hp;
    _attackRange = range;
    _gridType = GridType::PATH;
    _x = x;
    _y = y;

    _pic_path =
        R"(E:\MyProject\s6\cpp_final_proj\Inner-TD-Tale\assets\TorchWood.png)";
}

void Knight::draw(QPainter *painter) {
    QPixmap pixmap(_pic_path);

    painter->drawPixmap(_x * GRID_SIZE, _y * GRID_SIZE, 60, 60, pixmap);
}
