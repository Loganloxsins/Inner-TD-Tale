#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QDialog>
#include "map/map.h"


namespace Ui {
class GameWindow;
}

class GameWindow : public QDialog {
    Q_OBJECT

  public:


    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();



    Map* map; //地图组件
    void paintEvent(QPaintEvent *) override; // 绘图事件

  public slots:
    void onSaveandBackClicked();

  private:
    Ui::GameWindow *ui;
    QWidget *_parent;
};

#endif // GAMEWINDOW_H
