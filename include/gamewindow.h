#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "globals.h"
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
    explicit GameWindow(QWidget *parent = nullptr, int levelIndex = 1);
    ~GameWindow();

    Map *_map;                               // 地图组件
    void paintEvent(QPaintEvent *) override; // 绘图事件
    void timerEvent(QTimerEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

    std::vector<Enemy *> _enemies; // 敌人组件
    std::vector<Tower *> _towers;  // 塔组件
    int _spawnedEnemies;           // 已经生成的敌人数量
    int _arrivedEnemies;           // 已经到达终点的敌人数量

    int _gameTimerID; // 定时器ID
    int _spawnTimerID;
    bool _isPaused; // 游戏是否暂停

    bool _canBuffTower;
    bool _canBuffEnemy;

    Grid *_selectedGrid; // 当前选中的格子
    Unit *_selectedUnit; // 当前选中的单位

    int _levelIndex;
    int _holyWater; // 圣水数量，初始为10，近战塔消耗5，远程塔消耗10，每次timeevent增加1

    // lable绘图
    void updateLabels();

  public slots:
    void onSaveandBackClicked();
    void onLoadSaveClicked();
    void onPauseClicked();
    void onPlantMeleeTower();   // 种植近战塔按钮点击事件
    void onPlantRemoteTower();  // 种植远程塔按钮点击事件
    void onHpMedicineClicked(); // 药水按钮点击事件

    void buffFury();
    void buffIce();
    void buffAoE();
    void buffBleed();
    void buffJump();
    void buffSpeed();

    void debuffFury();
    void debuffIce();
    void debuffAoE();
    void debuffBleed();
    void debuffJump();
    void debuffSpeed();

  private:
    Ui::GameWindow *ui;
    QWidget *_parent;
};

#endif // GAMEWINDOW_H
       /*
         ·近战塔，三种基本的词缀：
     √狂暴的：附加狂暴属性，装备后伤害和攻击间隔都大幅增加（比如简单设定为都乘以2)
     √冰系的：附加冰冻效果，装备后攻击能使得敌方单位停止攻击、移动一段时间
     √群伤的：附加范围伤害，装备后能同时攻击多个敌人
     ●远程塔，一种基本词缀：
     √放血的：装备后对敌人的攻击附加流血效果，使得敌人在一定时间内持续扣血
     ·基本的敌方词缀：
     √闪现的：该单位能发动闪现，越过我方近战塔的阻挡前进，但需要有冷却时间
     神速的：该单位的移动速度要超过默认单位
         */
