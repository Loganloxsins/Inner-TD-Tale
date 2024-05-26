#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "map/map.h"
#include <QDialog>
#include "unit/base/base_enemy.h"
#include "unit/base/base_tower.h"

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

    std::vector<Enemy *> _enemies; // 敌人组件
   // std::vector<Tower *> _towers;  // 塔组件

    int _timerID; // 定时器ID

  public slots:
    void onSaveandBackClicked();

  private:
    Ui::GameWindow *ui;
    QWidget *_parent;
};

#endif // GAMEWINDOW_H
