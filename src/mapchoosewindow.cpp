#include "mapchoosewindow.h"
#include "ui_mapchoosewindow.h"
#include <QDebug>
MapChooseWindow::MapChooseWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::MapChooseWindow), _parent(parent) {
    ui->setupUi(this);
    connect(ui->pushButton_MapChoose, SIGNAL(clicked()), this,
            SLOT(onMapChooseClicked()));
    connect(ui->pushButton_Back, SIGNAL(clicked()), this,
            SLOT(onBackClicked()));
    connect(ui->pushButton_Enter, SIGNAL(clicked()), this,
            SLOT(onEnterClicked()));
}

MapChooseWindow::~MapChooseWindow() { delete ui; }

void MapChooseWindow::onMapChooseClicked() {
    // Code to choose map
    qDebug() << "map choose";
}

void MapChooseWindow::onEnterClicked() {
    // Code to enter the game
    qDebug() << "enter";
}

void MapChooseWindow::onBackClicked() {
    // Code to return to the main menu
    qDebug() << "back";
    _parent->show();
    this->hide();
}
