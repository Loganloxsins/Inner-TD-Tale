#include "shopping.h"
#include "globals.h"
#include "ui_shopping.h"
#include <QMessageBox>

shopping::shopping(QWidget *parent)
    : QDialog(parent), ui(new Ui::shopping), _parent(parent) {
    ui->setupUi(this);
    connect(ui->pushButton_HpMedicine, SIGNAL(clicked()), this,
            SLOT(onHpMedicineClicked()));
    connect(ui->pushButton_Skin, SIGNAL(clicked()), this,
            SLOT(onSkinClicked()));
    connect(ui->pushButton_HolyWaterSpeed, SIGNAL(clicked()), this,
            SLOT(onHolyWaterSpeedClicked()));
    connect(ui->pushButton_Back, SIGNAL(clicked()), this,
            SLOT(onBackClicked()));
    updateLabels();
}

shopping::~shopping() { delete ui; }

void shopping::onHpMedicineClicked() {
    if (g_coins >= 5) {
        QMessageBox::information(this, "Shopping", "You bought HpMedicine!");
        g_coins -= 1;
        g_hpmedicine_num += 1;
        updateLabels();
    } else {
        QMessageBox::information(this, "Shopping",
                                 "You don't have enough coins!");
    }
}

void shopping::onSkinClicked() {
    if (g_coins >= 8) {
        QMessageBox::information(this, "Shopping", "You bought Skin!");
        g_coins -= 8;
        g_melee_skin =
            R"(E:\MyProject\s6\cpp_final_proj\Inner-TD-Tale\assets\player0.png)";
        updateLabels();
    } else {
        QMessageBox::information(this, "Shopping",
                                 "You don't have enough coins!");
    }
}

void shopping::onHolyWaterSpeedClicked() {
    if (g_coins >= 10) {
        QMessageBox::information(this, "Shopping",
                                 "You bought HolyWaterSpeed!");
        g_coins -= 1;
        g_holywater_speed += 1;
        updateLabels();
    } else {
        QMessageBox::information(this, "Shopping",
                                 "You don't have enough coins!");
    }
}

void shopping::onBackClicked() {
    this->close();
    this->_parent->show();
}

void shopping::updateLabels() {
    ui->label_Coins->setText("当前金币: " + QString::number(g_coins));
}