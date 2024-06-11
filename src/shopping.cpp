#include "shopping.h"
#include "ui_shopping.h"

shopping::shopping(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::shopping)
{
    ui->setupUi(this);
}

shopping::~shopping()
{
    delete ui;
}
