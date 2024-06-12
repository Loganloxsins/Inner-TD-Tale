#ifndef SHOPPING_H
#define SHOPPING_H

#include <QDialog>

namespace Ui {
class shopping;
}

class shopping : public QDialog {
    Q_OBJECT

  public:
    explicit shopping(QWidget *parent = nullptr);
    ~shopping();

    void updateLabels();

  public slots:
    void onHpMedicineClicked();
    void onSkinClicked();
    void onHolyWaterSpeedClicked();
    void onBackClicked();

  private:
    Ui::shopping *ui;
    QWidget *_parent;
};

#endif // SHOPPING_H
