#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->pushButton_Start, SIGNAL(clicked()), this,
            SLOT(onStartGameClicked()));
    connect(ui->pushButton_LoadSave, SIGNAL(clicked()), this,
            SLOT(onLoadSaveClicked()));
    connect(ui->pushButton_Exit, SIGNAL(clicked()), this,
            SLOT(onExitClicked()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::onStartGameClicked() {
    // Code to transition to Interface 2
    qDebug() << "start";
}

void MainWindow::onLoadSaveClicked() {
    // Code to load save and transition to Interface 2
    qDebug() << "load";
}

void MainWindow::onExitClicked() {
    // Code to exit the game
    qDebug() << "exit";
    QCoreApplication::quit();
}