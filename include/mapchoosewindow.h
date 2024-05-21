#ifndef MAPCHOOSEWINDOW_H
#define MAPCHOOSEWINDOW_H

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

  private:
    Ui::MapChooseWindow *ui;
    QWidget *_parent;
};

#endif // MAPCHOOSEWINDOW_H
