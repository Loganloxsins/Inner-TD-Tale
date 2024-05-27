#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "map/grid.h"
#include "map/map.h"
#include "unit/base_enemy.h"
#include "unit/base_tower.h"
#include <QDialog>
#include <QMouseEvent>

namespace Ui {
class GameWindow;
}

class GameWindow : public QDialog {
    Q_OBJECT

  public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

    Map *map;                                // 地图组件
    void paintEvent(QPaintEvent *) override; // 绘图事件
    void timerEvent(QTimerEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

    std::vector<Enemy *> _enemies; // 敌人组件
    // std::vector<Tower *> _towers;  // 塔组件
    int _spawnedEnemies; // 已经生成的敌人数量
    int _arrivedEnemies; // 已经到达终点的敌人数量

    int _gameTimerID; // 定时器ID
    int _spawnTimerID;
    bool _isPaused; // 游戏是否暂停

    Grid *_selectedGrid; // 当前选中的格子

  public slots:
    void onSaveandBackClicked();
    void onPauseClicked();
    // void onPlantMeleeTower();  // 种植近战塔按钮点击事件
    // void onPlantRemoteTower(); // 种植远程塔按钮点击事件

  private:
    Ui::GameWindow *ui;
    QWidget *_parent;
};

#endif // GAMEWINDOW_H
