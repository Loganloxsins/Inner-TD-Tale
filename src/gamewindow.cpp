#include "gamewindow.h"
#include "map/map.h"
#include "ui_gamewindow.h"
#include "unit/boar.h"
#include "unit/knight.h"
#include <QDebug>
#include <QDir>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QRandomGenerator> // 添加头文件以使用随机数生成

GameWindow::GameWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::GameWindow), _parent(parent),
      _spawnedEnemies(0), _arrivedEnemies(0), _isPaused(false), _gameTimerID(0),
      _spawnTimerID(0) {
    ui->setupUi(this);
    connect(ui->pushButton_SaveandBack, SIGNAL(clicked()), this,
            SLOT(onSaveandBackClicked()));
    connect(ui->pushButton_Pause, SIGNAL(clicked()), this,
            SLOT(onPauseClicked()));
    connect(ui->pushButton_PlantMeele, SIGNAL(clicked()), this,
            SLOT(onPlantMeleeTower()));
    connect(ui->pushButton_PlantRemote, SIGNAL(clicked()), this,
            SLOT(onPlantRemoteTower()));

    // 初始化地图
    this->_map = new Map();
    QString filePath =
        R"(E:\MyProject\s6\cpp_final_proj\Inner-TD-Tale\data\map\map1.json)";
    if (this->_map->loadMap(filePath)) {
        qDebug() << "load map success";
    } else {
        qDebug() << "load map failed";
    }

    _gameTimerID = new QTimer(this);
    _spawnTimerID =new QTimer(this);
    _gameTimerID->start(1000);
    _spawnTimerID->start(2000);


    
}

GameWindow::~GameWindow() {

    delete ui;
    delete _map;
    for (auto enemy : _enemies) {
        delete enemy;
    }
    for (auto tower : _towers) {
        delete tower;
    }
    if (_gameTimerID != 0) {
        killTimer(_gameTimerID);
    }
}

// SLOT函数

void GameWindow::onSaveandBackClicked() {
    // Code to save and back
    qDebug() << "save and back";
    this->hide();
    _parent->show();
}
void GameWindow::onPauseClicked() {
    _isPaused = !_isPaused;
    if (_isPaused) {
        if (_gameTimerID != 0) {
            killTimer(_gameTimerID);
            _gameTimerID = 0;
        }
        if (_spawnTimerID != 0) {
            killTimer(_spawnTimerID);
            _spawnTimerID = 0;
        }
    } else {
        _gameTimerID = startTimer(1000);
        // 随机生成1到5秒（1000到5000毫秒）的间隔
        int randomSpawnInterval =
            QRandomGenerator::global()->bounded(4000) + 1000;
        _spawnTimerID = startTimer(randomSpawnInterval);
    }
}
void GameWindow::onPlantMeleeTower() {
    if (_isPaused) {
        // 输出选中格子的坐标
        if (_selectedGrid) {
            qDebug() << "selected grid: " << _selectedGrid->x << " "
                     << _selectedGrid->y;
        }
        // 如果被选中的格子高亮，则检查格子类型，种植近战塔
        if (_selectedGrid && _selectedGrid->isHighlighted) {
            if (_selectedGrid->type == GridType::PATH &&
                !_selectedGrid->isplanted) {
                qDebug() << "Plant melee tower here!";
                // 种植近战塔
                Tower *tower =
                    new Knight(_selectedGrid->x, _selectedGrid->y, 100, 10, 1);
                _towers.push_back(tower);
                _selectedGrid->isHighlighted = false;
                _selectedGrid->isplanted = true;
                // 清除selectedGrid
                _selectedGrid = nullptr;
                update();
            } else {
                qDebug() << "Can't plant melee tower here!";
            }
        }
    }
}

void GameWindow::onPlantRemoteTower() {}



// 绘图事件 绘制画面上的所有内容
void GameWindow::paintEvent(QPaintEvent *) {

    QPainter painter(this);
    QString path =
        R"(E:\MyProject\s6\cpp_final_proj\Inner-TD-Tale\assets\BG-hd.png)";
    // QString path =
    //     R"(:\assets\BG-hd.png)";不行
    QPixmap pixmap(path);
    painter.drawPixmap(0, 0, this->width(), this->height(), pixmap);

    _map->drawMap(&painter); // 绘制地图

    for (auto enemy : _enemies) {
        if (enemy->_state != EnemyState::ARRIVED) {
            enemy->draw(&painter); // 绘制敌人
        }
    }
    for (auto tower : _towers) {
        tower->draw(&painter);
    }
}

void GameWindow::timerEvent(QTimerEvent *event) {
    if (_isPaused)
        return;

    // 打印敌人编号和位置信息
    for (int i = 0; i < _enemies.size(); i++) {
        qDebug() << "enemy" << i << " position: " << _enemies[i]->_x << " " << _enemies[i]->_y;
    }

    if (event->timerId() == _gameTimerID) {
        for (auto enemy : _enemies) {
            enemy->move();
            if (enemy->_state == EnemyState::ARRIVED && !enemy->_isArrivedCounted) {
                _arrivedEnemies++;
                enemy->_isArrivedCounted = true;
                if (_arrivedEnemies >= 10) {
                    qDebug() << "Game Over: You have lost!";
                    this->hide();
                    _parent->show();
                    return;
                }
            }
        }
        update(); // 确保在所有敌人都移动后再更新界面
    }
    if (event->timerId() == _spawnTimerID) {
        if (_spawnedEnemies < 10) {
            std::vector<std::pair<int, int>> path = this->_map->_monsterPaths[0];
            Enemy *enemy = new Boar(100, 1, path, this->_map);
            this->_enemies.push_back(enemy);
            _spawnedEnemies++;
            int randomSpawnInterval = QRandomGenerator::global()->bounded(4000) + 1000;
            _spawnTimerID = startTimer(randomSpawnInterval);
        } else {
            killTimer(_spawnTimerID);
        }
    }
}

void GameWindow::mousePressEvent(QMouseEvent *event) {
    if (_isPaused) {
        QPoint clickPos = event->pos();
        bool enemySelected = false; // 标志变量，表示是否选中了怪物

        // 检查 _enemies 是否为空
        if (!_enemies.empty()) {
            for (auto enemy : _enemies) {
                // 检查 enemy 是否为 nullptr
                if (enemy && enemy->contains(clickPos)) {
                    enemy->highlight();
                    update();
                    enemySelected = true; // 设置标志变量
                    break;
                }
            }
        }

        // 如果没有选中怪物，则检查格子
        if (!enemySelected && _map != nullptr && !_map->_all_grids.empty()) {
            for (auto row : _map->_all_grids) {
                for (auto grid : row) {
                    // 检查 grid 是否为 nullptr
                    if (grid && grid->contains(clickPos)) {
                        // qDebug() << "click grid: " << grid->x << " " <<
                        // grid->y;
                        grid->highlight();
                        _selectedGrid = grid;
                        update();
                        break;
                    }
                }
            }
        }
    }
}
