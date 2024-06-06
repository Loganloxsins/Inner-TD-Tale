#ifndef MAPCHOOSEWINDOW_H
#define MAPCHOOSEWINDOW_H

#include "gamewindow.h"
#include <QDialog>

namespace Ui {
class MapChooseWindow;
}

class MapChooseWindow : public QDialog {
    Q_OBJECT

  public:
    explicit MapChooseWindow(QWidget *parent = nullptr);
    ~MapChooseWindow();
    int _levelIndex;

  public slots:
    void onMapChooseClicked();
    void onEnterClicked();
    void onBackClicked();
    void onLevel1Clicked();
    void onLevel2Clicked();

  private:
    Ui::MapChooseWindow *ui;
    QWidget *_parent;
    GameWindow *_gameWindow;
};

#endif // MAPCHOOSEWINDOW_H
