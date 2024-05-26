#ifndef ENEMY_STATE_H
#define ENEMY_STATE_H

enum class EnemyState {
    DEAD,      // 死亡
    MOVING,    // 移动
    ATTACKING, // 攻击
    ARRIVED    // 到达终点
};

#endif // ENEMY_STATE_H