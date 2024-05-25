#include "mapchoosewindow.h"
#include "ui_mapchoosewindow.h"
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QMessageBox>

#include "map/map.h"

MapChooseWindow::MapChooseWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::MapChooseWindow), _parent(parent) {
    ui->setupUi(this);
    _gameWindow = new GameWindow(this);
    connect(ui->pushButton_MapChoose, SIGNAL(clicked()), this,
            SLOT(onMapChooseClicked()));
    connect(ui->pushButton_Back, SIGNAL(clicked()), this,
            SLOT(onBackClicked()));
    connect(ui->pushButton_Enter, SIGNAL(clicked()), this,
            SLOT(onEnterClicked()));
    connect(ui->pushButton_Level1, SIGNAL(clicked()), this,
            SLOT(onLevel1Clicked()));
    connect(ui->pushButton_Level2, SIGNAL(clicked()), this,
            SLOT(onLevel2Clicked()));
}

MapChooseWindow::~MapChooseWindow() { delete ui; }

void MapChooseWindow::onMapChooseClicked() {
    // Code to choose map
    qDebug() << "map choose";
}

void MapChooseWindow::onEnterClicked() {
    // Code to enter the game
    qDebug() << "enter";
    _gameWindow->show();
    this->hide();
}

void MapChooseWindow::onBackClicked() {
    // Code to return to the main menu
    qDebug() << "back";
    _parent->show();
    this->hide();
}

void MapChooseWindow::onLevel1Clicked() {
    // Code to choose map
    qDebug() << "感谢您选择level1\n";
}

void MapChooseWindow::onLevel2Clicked() {
    // Code to choose map
    qDebug() << "level2";
}
