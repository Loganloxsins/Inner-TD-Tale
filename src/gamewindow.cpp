#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QDebug>
GameWindow::GameWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::GameWindow), _parent(parent) {
    ui->setupUi(this);
    connect(ui->pushButton_SaveandBack, SIGNAL(clicked()), this,
            SLOT(onSaveandBackClicked()));
}

GameWindow::~GameWindow() { delete ui; }

void GameWindow::onSaveandBackClicked() {
    // Code to save and back
    qDebug() << "save and back";
    this->hide();
    _parent->show();
}
