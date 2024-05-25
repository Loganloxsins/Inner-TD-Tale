#include "gamewindow.h"
#include "map/map.h"
#include "ui_gamewindow.h"
#include <QDebug>
#include <QDir>
#include <QPainter>
#include <QPixmap>

GameWindow::GameWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::GameWindow), _parent(parent) {
    ui->setupUi(this);
    connect(ui->pushButton_SaveandBack, SIGNAL(clicked()), this,
            SLOT(onSaveandBackClicked()));

    this->map = new Map();
    QString filePath =
        R"(E:\MyProject\s6\cpp_final_proj\Inner-TD-Tale\data\map\map1.json)";

    if (this->map->loadMap(filePath)) {
        qDebug() << "load map success";
    } else {
        qDebug() << "load map failed";
    }
}

GameWindow::~GameWindow() {
    delete map;
    delete ui;
}

void GameWindow::onSaveandBackClicked() {
    // Code to save and back
    qDebug() << "save and back";
    this->hide();
    _parent->show();
}

// 绘图事件 绘制画面上的所有内容
void GameWindow::paintEvent(QPaintEvent *) {

    QPainter painter(this);
    QString path =
        R"(E:\MyProject\s6\cpp_final_proj\Inner-TD-Tale\assets\BG-hd.png)";
    QPixmap pixmap(path);
    painter.drawPixmap(0, 0, this->width(), this->height(), pixmap);


     map->drawMap(&painter); // 绘制地图
     update();
}
