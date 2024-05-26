#include "gamewindow.h"
#include "map/map.h"
#include "ui_gamewindow.h"
#include <QDebug>
#include <QDir>
#include <QPainter>
#include <QPixmap>

#include "unit/enemy/boar.h"

GameWindow::GameWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::GameWindow), _parent(parent) {
    ui->setupUi(this);
    connect(ui->pushButton_SaveandBack, SIGNAL(clicked()), this,
            SLOT(onSaveandBackClicked()));

    // 初始化地图
    this->map = new Map();
    QString filePath =
        R"(E:\MyProject\s6\cpp_final_proj\Inner-TD-Tale\data\map\map1.json)";
    if (this->map->loadMap(filePath)) {
        qDebug() << "load map success";
    } else {
        qDebug() << "load map failed";
    }

    // 初始化10个敌人
    for (int i = 0; i < 10; i++) {
        std::vector<std::pair<int, int>> path = this->map->_monsterPaths[0];
        Enemy *enemy = new Boar(100, 1, path);
        this->_enemies.push_back(enemy);
    }

    // 初始化塔

    // 初始化定时器
    this->_timerID = startTimer(1000);
}

GameWindow::~GameWindow() {

    delete ui;
    delete map;
    for (auto enemy : _enemies) {
        delete enemy;
    }
    // for (auto tower : _towers) {
    //     delete tower;
    // }
    if (_timerID != 0) {
        killTimer(_timerID);
    }
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
    // QString path =
    //     R"(:\assets\BG-hd.png)";不行
    QPixmap pixmap(path);
    painter.drawPixmap(0, 0, this->width(), this->height(), pixmap);

    map->drawMap(&painter); // 绘制地图
    for (auto enemy : _enemies) {
        if (enemy->_state != EnemyState::ARRIVED) {
            enemy->draw(&painter); // 绘制敌人
        }
    }
}

void GameWindow::timerEvent(QTimerEvent *event) {
    if (event->timerId() == _timerID) {
        for (auto enemy : _enemies) {
            enemy->move();
        }
        update();
    }
}
