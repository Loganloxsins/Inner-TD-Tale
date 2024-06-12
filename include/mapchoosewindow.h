#ifndef MAPCHOOSEWINDOW_H
#define MAPCHOOSEWINDOW_H

#include "gamewindow.h"
#include "shopping.h"
#include <QDialog>

namespace Ui {
class MapChooseWindow;
}

class MapChooseWindow : public QDialog {
    Q_OBJECT

  public:
    explicit MapChooseWindow(QWidget *parent = nullptr);
    ~MapChooseWindow();

  public slots:
    void onMapChooseClicked();
    void onEnterClicked();
    void onBackClicked();
    void onLevel1Clicked();
    void onLevel2Clicked();
    void onShoppingClicked();

  private:
    Ui::MapChooseWindow *ui;
    QWidget *_parent;
    GameWindow *_gameWindow;
    shopping *_shoppingWindow;
};

#endif // MAPCHOOSEWINDOW_H
