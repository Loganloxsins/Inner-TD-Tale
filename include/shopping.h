#ifndef SHOPPING_H
#define SHOPPING_H

#include <QDialog>

namespace Ui {
class shopping;
}

class shopping : public QDialog
{
    Q_OBJECT

public:
    explicit shopping(QWidget *parent = nullptr);
    ~shopping();

private:
    Ui::shopping *ui;
};

#endif // SHOPPING_H
