#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QDialog>

namespace Ui {
class GameWindow;
}

class GameWindow : public QDialog {
    Q_OBJECT

  public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

  public slots:
    void onSaveandBackClicked();

  private:
    Ui::GameWindow *ui;
    QWidget *_parent;
};

#endif // GAMEWINDOW_H
