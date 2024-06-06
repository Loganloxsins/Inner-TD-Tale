#include "mainwindow.h"
#include "mapchoosewindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    _mapChooseWindow = new MapChooseWindow(this);
    connect(ui->pushButton_Start, SIGNAL(clicked()), this,
            SLOT(onStartGameClicked()));
    connect(ui->pushButton_Exit, SIGNAL(clicked()), this,
            SLOT(onExitClicked()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::onStartGameClicked() {
    // 打开地图选择窗口，隐藏主窗口
    qDebug() << "start";
    _mapChooseWindow->show();
    this->hide();
}

void MainWindow::onExitClicked() {
    // Code to exit the game
    qDebug() << "exit";
    QCoreApplication::quit();
}
