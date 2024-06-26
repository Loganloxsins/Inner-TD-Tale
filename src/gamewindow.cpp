#include "gamewindow.h"
#include "globals.h"
#include "map/map.h"
#include "ui_gamewindow.h"
#include "unit/boar.h"
#include "unit/knight.h"
#include "unit/shooter.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QRandomGenerator>
GameWindow::GameWindow(QWidget *parent, int levelIndex)
    : QDialog(parent), ui(new Ui::GameWindow), _parent(parent),
      _spawnedEnemies(0), _arrivedEnemies(0), _isPaused(false), _gameTimerID(0),
      _spawnTimerID(0), _canBuffTower(false), _canBuffEnemy(false),
      _selectedGrid(nullptr), _selectedUnit(nullptr), _levelIndex(levelIndex),
      _holyWater(10) {
    ui->setupUi(this);
    connect(ui->pushButton_SaveandBack, SIGNAL(clicked()), this,
            SLOT(onSaveandBackClicked()));
    connect(ui->pushButton_Pause, SIGNAL(clicked()), this,
            SLOT(onPauseClicked()));
    connect(ui->pushButton_PlantMeele, SIGNAL(clicked()), this,
            SLOT(onPlantMeleeTower()));
    connect(ui->pushButton_PlantRemote, SIGNAL(clicked()), this,
            SLOT(onPlantRemoteTower()));

    connect(ui->pushButton_buffFury, SIGNAL(clicked()), this, SLOT(buffFury()));
    connect(ui->pushButton_debuffFury, SIGNAL(clicked()), this,
            SLOT(debuffFury()));
    connect(ui->pushButton_buffIce, SIGNAL(clicked()), this, SLOT(buffIce()));
    connect(ui->pushButton_debuffIce, SIGNAL(clicked()), this,
            SLOT(debuffIce()));
    connect(ui->pushButton_buffAoE, SIGNAL(clicked()), this, SLOT(buffAoE()));
    connect(ui->pushButton_debuffAoE, SIGNAL(clicked()), this,
            SLOT(debuffAoE()));
    connect(ui->pushButton_buffBleed, SIGNAL(clicked()), this,
            SLOT(buffBleed()));
    connect(ui->pushButton_debuffBleed, SIGNAL(clicked()), this,
            SLOT(debuffBleed()));
    connect(ui->pushButton_buffJump, SIGNAL(clicked()), this, SLOT(buffJump()));
    connect(ui->pushButton_debuffJump, SIGNAL(clicked()), this,
            SLOT(debuffJump()));
    connect(ui->pushButton_buffSpeed, SIGNAL(clicked()), this,
            SLOT(buffSpeed()));
    connect(ui->pushButton_debuffSpeed, SIGNAL(clicked()), this,
            SLOT(debuffSpeed()));
    connect(ui->pushButton_LoadSave, SIGNAL(clicked()), this,
            SLOT(onLoadSaveClicked()));
    connect(ui->pushButton_HpMedicine, SIGNAL(clicked()), this,
            SLOT(onHpMedicineClicked()));
    // 初始化地图
    this->_map = new Map();
    QString filePath =
        R"(..\..\.\data\map\map2.json)";
    if (_levelIndex == 1) {
        filePath =
            R"(..\..\.\data\map\map1.json)";
    } else if (_levelIndex == 2) {
        filePath =
            R"(..\..\.\data\map\map2.json)";
    }

    if (this->_map->loadMap(filePath)) {
        qDebug() << "load map success";
    } else {
        qDebug() << "load map failed";
    }
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

// 绘图事件
void GameWindow::updateLabels() {

    this->ui->label_Heart->setText("生命：" +
                                   QString::number(10 - _arrivedEnemies));
    this->ui->label_Hpmedicine->setText("加血道具数量：" +
                                        QString::number(g_hpmedicine_num));
    this->ui->label_Coins->setText("商店金币数量：" + QString::number(g_coins));

    this->ui->label_HolyWater->setText("圣水数量：" +
                                       QString::number(_holyWater));
}

// SLOT函数
void GameWindow::onHpMedicineClicked() {
    if (g_hpmedicine_num > 0) {
        g_hpmedicine_num--;
        // 遍历所有塔，血量加满
        for (auto tower : _towers) {
            tower->_hp_cur = tower->_hp_full;
        }
        updateLabels();
    } else {
        QMessageBox::information(this, "提示", "血瓶数量不足");
    }
}

void GameWindow::onSaveandBackClicked() {
    _isPaused = true;
    this->hide();
    _parent->show();

    // 创建JSON对象并保存当前游戏状态
    QJsonObject gameState;
    gameState["spawnedEnemies"] = _spawnedEnemies;
    gameState["arrivedEnemies"] = _arrivedEnemies;
    gameState["levelIndex"] = _levelIndex;
    gameState["isPaused"] = _isPaused;
    gameState["canBuffTower"] = _canBuffTower;
    gameState["canBuffEnemy"] = _canBuffEnemy;

    // 保存敌人数据
    QJsonArray enemiesArray;
    for (auto enemy : _enemies) {
        QJsonObject enemyObject;
        // 现有的属性
        enemyObject["x"] = enemy->_x;
        enemyObject["y"] = enemy->_y;

        // 添加其他Enemy相关属性
        enemyObject["state"] = static_cast<int>(enemy->_state);
        enemyObject["hp_cur"] = enemy->_hp_cur;

        enemyObject["isArrivedCounted"] = enemy->_isArrivedCounted;
        enemyObject["bleedDamage"] = enemy->_bleedDamage;
        enemyObject["bleedDuration"] = enemy->_bleedDuration;
        enemyObject["jumpCoolDown"] = enemy->_jumpCoolDown;
        enemyObject["buff_num"] = enemy->_buff_num;

        // 处理长度为2的buff种类数组
        QJsonArray buffSlotArray;
        for (int i = 0; i < 2; ++i) {
            buffSlotArray.append(enemy->_buffSlot[i]);
        }
        enemyObject["buffSlot"] = buffSlotArray;

        enemiesArray.append(enemyObject);
    }
    gameState["enemies"] = enemiesArray;

    // 保存塔的数据
    QJsonArray towersArray;
    for (auto tower : _towers) {
        QJsonObject towerObject;
        // 现有的属性
        towerObject["x"] = tower->_x;
        towerObject["y"] = tower->_y;
        towerObject["hp_cur"] = tower->_hp_cur;
        towerObject["buff_num"] = tower->_buff_num;

        // 新增的属性
        towerObject["gridType"] = static_cast<int>(tower->_gridType);
        towerObject["state"] = 0;

        // 处理长度为2的buff种类数组
        QJsonArray buffSlotArray;
        for (int i = 0; i < 2; ++i) {
            buffSlotArray.append(tower->_buffSlot[i]);
        }
        towerObject["buffSlot"] = buffSlotArray;

        towersArray.append(towerObject);
    }
    gameState["towers"] = towersArray;

    // 将JSON对象写入绝对路径文件
    QString filePath =
        R"(E:/MyProject/s6/cpp_final_proj/Inner-TD-Tale/data/saves/save.json)";
    QFile saveFile(filePath);
    if (saveFile.open(QIODevice::WriteOnly)) {
        QJsonDocument saveDoc(gameState);
        saveFile.write(saveDoc.toJson());
        saveFile.close();
    } else {
        qWarning("Couldn't open save file.");
    }
}

void GameWindow::onLoadSaveClicked() {
    _isPaused = true;
    QString dialogTitle = "Select Save File"; // 对话框标题
    QString defaultDir = QDir::currentPath(); // 默认打开的目录
    QString fileFilter =
        "JSON Save Files (*.json);;All Files (*.*)"; // 修改过滤器以查找.json文件

    // 弹出文件选择对话框并获取选中的文件路径
    QString selectedFile =
        QFileDialog::getOpenFileName(this, dialogTitle, defaultDir, fileFilter);

    // 检查是否选择了文件
    if (!selectedFile.isEmpty()) {
        qDebug() << "Selected JSON file:" << selectedFile;

        // 尝试打开并读取JSON文件
        QFile jsonFile(selectedFile);
        if (jsonFile.open(QIODevice::ReadOnly)) {
            // 读取文件内容
            QByteArray jsonData = jsonFile.readAll();

            // 关闭文件
            jsonFile.close();

            // 使用QJsonDocument解析JSON数据
            QJsonParseError parseError;
            QJsonDocument jsonDoc =
                QJsonDocument::fromJson(jsonData, &parseError);

            if (parseError.error == QJsonParseError::NoError) {
                // JSON解析成功
                qDebug() << "JSON data loaded successfully";

                QJsonObject gameState = jsonDoc.object();

                // 恢复游戏状态
                _spawnedEnemies = gameState["spawnedEnemies"].toInt();
                _arrivedEnemies = gameState["arrivedEnemies"].toInt();
                _levelIndex = gameState["levelIndex"].toInt();
                _isPaused = gameState["isPaused"].toBool();
                _canBuffTower = gameState["canBuffTower"].toBool();
                _canBuffEnemy = gameState["canBuffEnemy"].toBool();
                g_coins = gameState["g_coins"].toInt();

                // 恢复敌人数据
                _enemies.clear();
                QJsonArray enemiesArray = gameState["enemies"].toArray();
                for (auto enemyValue : enemiesArray) {
                    QJsonObject enemyObject = enemyValue.toObject();
                    std::vector<std::pair<int, int>> path =
                        this->_map->_monsterPaths[0];
                    Enemy *enemy = new Boar(path, _map);

                    // 根据需要添加其他敌人类型

                    if (enemy) {
                        enemy->_x = enemyObject["x"].toInt();
                        enemy->_y = enemyObject["y"].toInt();
                        enemy->_state = static_cast<EnemyState>(
                            enemyObject["state"].toInt());
                        enemy->_hp_cur = enemyObject["hp_cur"].toInt();
                        enemy->_isArrivedCounted =
                            enemyObject["isArrivedCounted"].toBool();
                        enemy->_bleedDamage =
                            enemyObject["bleedDamage"].toInt();
                        enemy->_bleedDuration =
                            enemyObject["bleedDuration"].toInt();
                        enemy->_jumpCoolDown =
                            enemyObject["jumpCoolDown"].toInt();
                        enemy->_buff_num = enemyObject["buff_num"].toInt();

                        QJsonArray buffSlotArray =
                            enemyObject["buffSlot"].toArray();
                        for (int i = 0; i < 2; ++i) {
                            enemy->_buffSlot[i] = buffSlotArray[i].toInt();
                        }

                        _enemies.push_back(enemy);
                    }
                }

                // 恢复塔的数据
                _towers.clear();
                QJsonArray towersArray = gameState["towers"].toArray();
                for (auto towerValue : towersArray) {
                    QJsonObject towerObject = towerValue.toObject();

                    Tower *tower = nullptr;

                    int gridType = towerObject["gridType"].toInt();

                    if (gridType == 1) {
                        tower = new Knight(towerObject["x"].toInt(),
                                           towerObject["y"].toInt(), _enemies);
                    } else if (gridType == 2) {
                        tower = new Shooter(towerObject["x"].toInt(),
                                            towerObject["y"].toInt(), _enemies);
                    }
                    if (tower) {
                        tower->_hp_cur = towerObject["hp_cur"].toInt();
                        tower->_buff_num = towerObject["buff_num"].toInt();
                        tower->_gridType = static_cast<GridType>(
                            towerObject["gridType"].toInt());
                        tower->_state = static_cast<TowerState>(
                            towerObject["state"].toInt());

                        QJsonArray buffSlotArray =
                            towerObject["buffSlot"].toArray();
                        for (int i = 0; i < 2; ++i) {
                            tower->_buffSlot[i] = buffSlotArray[i].toInt();
                        }

                        _towers.push_back(tower);
                    }
                }

                // 恢复计时器
                qDebug() << "_gameTimerID: " << _gameTimerID;
                qDebug() << "_spawnTimerID: " << _spawnTimerID;
                if (_gameTimerID != 0) {
                    killTimer(_gameTimerID);
                }
                if (_spawnTimerID != 0) {
                    killTimer(_spawnTimerID);
                }
                _spawnTimerID = startTimer(3000);
                _gameTimerID = startTimer(1000);
                qDebug() << "_gameTimerID: " << _gameTimerID;
                qDebug() << "_spawnTimerID: " << _spawnTimerID;

                // 恢复其他游戏状态
                // ...（根据需要添加其他状态的恢复）

                // 更新游戏界面
                update();
            } else {
                // JSON解析错误，给出提示
                QMessageBox::critical(
                    this, "Error",
                    "Failed to parse the selected JSON file: " +
                        parseError.errorString());
            }
        } else {
            // 文件打开失败，给出提示
            QMessageBox::critical(this, "Error",
                                  "Failed to open the selected file.");
        }
    } else {
        qDebug() << "No file selected";
    }
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
                !_selectedGrid->isplanted && _holyWater >= 5) {
                qDebug() << "Plant melee tower here!";
                _holyWater -= 5;
                // 种植近战塔
                Tower *tower =
                    new Knight(_selectedGrid->x, _selectedGrid->y, _enemies);
                // 将该格子的tower指针指向新建的塔
                _selectedGrid->_tower = tower;

                // 检测all_grids是否正确加入该格子的该塔
                // qDebug() << "Tower
                // on:"<<_map->_all_grids[_selectedGrid->y][_selectedGrid->x]->_tower->_x<<"
                // "<<_map->_all_grids[_selectedGrid->y][_selectedGrid->x]->_tower->_y;

                _towers.push_back(tower);
                _selectedGrid->isHighlighted = false;
                _selectedGrid->isplanted = true;
                // 清除selectedGrid
                _selectedGrid = nullptr;
                update();
            } else {
                // 弹出提示框 不能种植
                QMessageBox::information(this, "提示", "不能在此处种植近战塔");
            }
        }
    }
}

void GameWindow::onPlantRemoteTower() {
    if (_isPaused) {
        // 输出选中格子的坐标
        if (_selectedGrid) {
            qDebug() << "selected grid: " << _selectedGrid->x << " "
                     << _selectedGrid->y;
        }
        // 如果被选中的格子高亮，则检查格子类型，种植远程塔
        if (_selectedGrid && _selectedGrid->isHighlighted) {
            if (_selectedGrid->type == GridType::REMOTE &&
                !_selectedGrid->isplanted && _holyWater >= 10) {
                qDebug() << "Plant remote tower here!";
                _holyWater -= 10;
                // 种植远程塔
                Tower *tower =
                    new Shooter(_selectedGrid->x, _selectedGrid->y, _enemies);
                // 将该格子的tower指针指向新建的塔
                _selectedGrid->_tower = tower;

                // 检测all_grids是否正确加入该格子的该塔
                // qDebug() << "Tower
                // on:"<<_map->_all_grids[_selectedGrid->y][_selectedGrid->x]->_tower->_x<<"
                // "<<_map->_all_grids[_selectedGrid->y][_selectedGrid->x]->_tower->_y;

                _towers.push_back(tower);
                _selectedGrid->isHighlighted = false;
                _selectedGrid->isplanted = true;
                // 清除selectedGrid
                _selectedGrid = nullptr;
                update();
            } else {
                // 弹出提示框 不能种植
                QMessageBox::information(this, "提示", "不能在此处种植远程塔");
            }
        }
    }
}

/*

  public slots:
    void onSaveandBackClicked();
    void onPauseClicked();
    void onPlantMeleeTower();  // 种植近战塔按钮点击事件
    void onPlantRemoteTower(); // 种植远程塔按钮点击事件

    void buffFury();
    void buffIce();
    void buffAoE();
    void buffBleed();
    void buffJump();
    void buffSpeed();

  private:
    Ui::GameWindow *ui;
    QWidget *_parent;
};

#endif // GAMEWINDOW_H
       /*
         ·近战塔，三种基本的词缀：
     √狂暴的：附加狂暴属性，装备后伤害和攻击间隔都大幅增加（比如简单设定为都乘以2)
     √冰系的：附加冰冻效果，装备后攻击能使得敌方单位停止攻击、移动一段时间
     √群伤的：附加范围伤害，装备后能同时攻击多个敌人
     ●远程塔，一种基本词缀：
     √放血的：装备后对敌人的攻击附加流血效果，使得敌人在一定时间内持续扣血
     ·基本的敌方词缀：
     √闪现的：该单位能发动闪现，越过我方近战塔的阻挡前进，但需要有冷却时间
     神速的：该单位的移动速度要超过默认单位
         */

void GameWindow::buffFury() {
    if (_isPaused) {
        // 只对选中的塔施加buff
        // 输出选中塔的坐标，不能用格子的坐标替代
        // 将unit转换为tower
        Tower *tower = dynamic_cast<Tower *>(_selectedUnit);
        if (tower) {
            qDebug() << "selected tower: " << tower->_x << " " << tower->_y;
        }

        // 如果被选中的塔高亮，则检查塔类型，施加狂暴buff
        if (tower->_isHighlighted && tower->_buff_num < 2) {
            if (tower->_gridType == GridType::PATH) {
                tower->_buff_num++;
                qDebug() << "Buff melee tower here!";
                // buff近战塔
                tower->buffFury();
                // 清除selectedGrid
                tower->_isHighlighted = false;
                _selectedUnit = nullptr;
                update();
            } else {

                qDebug() << "Can't buff  here!";
            }
        } else {
            qDebug() << "Buff Num: " << tower->_buff_num;
            qDebug() << "Can't buff  here!";
        }
    }
}
void GameWindow::debuffFury() {
    if (_isPaused) {
        // 只对选中的塔施加buff
        // 输出选中塔的坐标，不能用格子的坐标替代
        // 将unit转换为tower
        Tower *tower = dynamic_cast<Tower *>(_selectedUnit);
        if (tower) {
            qDebug() << "selected tower: " << tower->_x << " " << tower->_y;
        }

        // 如果被选中的塔高亮，则检查塔类型，清除狂暴buff
        if (tower->_isHighlighted &&
            (tower->_buffSlot[0] == 0 || tower->_buffSlot[1] == 0)) {
            if (tower->_gridType == GridType::PATH) {
                tower->_buff_num--;
                qDebug() << "Debuff melee tower here!";
                // debuff近战塔
                tower->debuffFury();
                // 清除selectedGrid
                tower->_isHighlighted = false;
                _selectedUnit = nullptr;
                update();
            } else {
                qDebug() << "Can't debuff  here!";
            }
        } else {
            qDebug() << "Buff Num: " << tower->_buff_num;
            qDebug() << "Can't buff  here!";
        }
    }
}

// ice
void GameWindow::buffIce() {
    if (_isPaused) {
        // 只对选中的塔施加buff
        // 输出选中塔的坐标，不能用格子的坐标替代
        // 将unit转换为tower
        Tower *tower = dynamic_cast<Tower *>(_selectedUnit);
        if (tower) {
            qDebug() << "selected tower: " << tower->_x << " " << tower->_y;
        }

        // 如果被选中的塔高亮，则检查塔类型，施加冰冻buff
        if (tower->_isHighlighted && tower->_buff_num < 2) {
            if (tower->_gridType == GridType::PATH) {
                tower->_buff_num++;
                qDebug() << "Buff PATH tower here!";
                // buff远程塔
                tower->buffIce();
                // 清除selectedGrid
                tower->_isHighlighted = false;
                _selectedUnit = nullptr;
                update();
            } else {
                qDebug() << "Can't buff  here!";
            }
        } else {
            qDebug() << "Buff Num: " << tower->_buff_num;
            qDebug() << "Can't buff  here!";
        }
    }
}

void GameWindow::debuffIce() {
    if (_isPaused) {
        // 只对选中的塔施加buff
        // 输出选中塔的坐标，不能用格子的坐标替代
        // 将unit转换为tower
        Tower *tower = dynamic_cast<Tower *>(_selectedUnit);
        if (tower) {
            qDebug() << "selected tower: " << tower->_x << " " << tower->_y;
        }

        // 如果被选中的塔高亮，则检查塔类型，清除冰冻buff
        if (tower->_isHighlighted &&
            (tower->_buffSlot[0] == 1 || tower->_buffSlot[1] == 1)) {
            if (tower->_gridType == GridType::PATH) {
                tower->_buff_num--;
                qDebug() << "Debuff PATH tower here!";
                // debuff远程塔
                tower->debuffIce();
                // 清除selectedGrid
                tower->_isHighlighted = false;
                _selectedUnit = nullptr;
                update();
            } else {
                qDebug() << "Can't debuff  here!";
            }
        } else {
            qDebug() << "Buff Num: " << tower->_buff_num;
            qDebug() << "Can't buff  here!";
        }
    }
}

// AoE
void GameWindow::buffAoE() {
    if (_isPaused) {
        // 只对选中的塔施加buff
        // 输出选中塔的坐标，不能用格子的坐标替代
        // 将unit转换为tower
        Tower *tower = dynamic_cast<Tower *>(_selectedUnit);
        if (tower) {
            qDebug() << "selected tower: " << tower->_x << " " << tower->_y;
        }

        // 如果被选中的塔高亮，则检查塔类型，施加范围伤害buff
        if (tower->_isHighlighted && tower->_buff_num < 2) {
            if (tower->_gridType == GridType::PATH) {
                tower->_buff_num++;
                qDebug() << "Buff PATH tower here!";
                // buff远程塔
                tower->buffAoE();
                // 清除selectedGrid
                tower->_isHighlighted = false;
                _selectedUnit = nullptr;
                update();
            } else {
                qDebug() << "Can't buff  here!";
            }
        } else {
            qDebug() << "Buff Num: " << tower->_buff_num;
            qDebug() << "Can't buff  here!";
        }
    }
}

void GameWindow::debuffAoE() {
    if (_isPaused) {
        // 只对选中的塔施加buff
        // 输出选中塔的坐标，不能用格子的坐标替代
        // 将unit转换为tower
        Tower *tower = dynamic_cast<Tower *>(_selectedUnit);
        if (tower) {
            qDebug() << "selected tower: " << tower->_x << " " << tower->_y;
        }

        // 如果被选中的塔高亮，则检查塔类型，清除范围伤害buff
        if (tower->_isHighlighted &&
            (tower->_buffSlot[0] == 2 || tower->_buffSlot[1] == 2)) {
            if (tower->_gridType == GridType::PATH) {
                tower->_buff_num--;
                qDebug() << "Debuff PATH tower here!";
                // debuff远程塔
                tower->debuffAoE();
                // 清除selectedGrid
                tower->_isHighlighted = false;
                _selectedUnit = nullptr;
                update();
            } else {
                qDebug() << "Can't debuff  here!";
            }
        } else {
            qDebug() << "Buff Num: " << tower->_buff_num;
            qDebug() << "Can't buff  here!";
        }
    }
}

// bleed
void GameWindow::buffBleed() {
    if (_isPaused) {
        // 只对选中的塔施加buff
        // 输出选中塔的坐标，不能用格子的坐标替代
        // 将unit转换为tower
        Tower *tower = dynamic_cast<Tower *>(_selectedUnit);
        if (tower) {
            qDebug() << "selected tower: " << tower->_x << " " << tower->_y;
        }

        // 如果被选中的塔高亮，则检查塔类型，施加流血buff
        if (tower->_isHighlighted && tower->_buff_num < 2) {
            if (tower->_gridType == GridType::REMOTE) {
                tower->_buff_num++;
                qDebug() << "Buff REMOTE tower here!";
                // buff远程塔
                tower->buffBleed();
                // 清除selectedGrid
                tower->_isHighlighted = false;
                _selectedUnit = nullptr;
                update();
            } else {
                qDebug() << "Can't buff  here!";
            }
        } else {
            qDebug() << "Buff Num: " << tower->_buff_num;
            qDebug() << "Can't buff  here!";
        }
    }
}

void GameWindow::debuffBleed() {
    if (_isPaused) {
        // 只对选中的塔施加buff
        // 输出选中塔的坐标，不能用格子的坐标替代
        // 将unit转换为tower
        Tower *tower = dynamic_cast<Tower *>(_selectedUnit);
        if (tower) {
            qDebug() << "selected tower: " << tower->_x << " " << tower->_y;
        }

        // 如果被选中的塔高亮，则检查塔类型，清除流血buff
        if (tower->_isHighlighted &&
            (tower->_buffSlot[0] == 3 || tower->_buffSlot[1] == 3)) {
            if (tower->_gridType == GridType::REMOTE) {
                tower->_buff_num--;
                qDebug() << "Debuff REMOTE tower here!";
                // debuff远程塔
                tower->debuffBleed();
                // 清除selectedGrid
                tower->_isHighlighted = false;
                _selectedUnit = nullptr;
                update();
            } else {
                qDebug() << "Can't debuff  here!";
            }
        } else {
            qDebug() << "Buff Num: " << tower->_buff_num;
            qDebug() << "Can't buff  here!";
        }
    }
}

// jump和speed是针对怪物的buff
void GameWindow::buffJump() {
    if (_isPaused) {
        // 只对选中的怪物施加buff
        // 输出选中怪物的坐标，不能用格子的坐标替代
        // 将unit转换为enemy
        Enemy *enemy = dynamic_cast<Enemy *>(_selectedUnit);
        if (enemy) {
            qDebug() << "selected enemy: " << enemy->_x << " " << enemy->_y;
        }

        // 如果被选中的怪物高亮，则检查怪物类型，施加闪现buff
        if (enemy->_isHighlighted) {

            qDebug() << "Buff jump enemy here!";
            // buff怪物
            enemy->buffJump();
            // 清除selectedGrid
            enemy->_isHighlighted = false;
            _selectedUnit = nullptr;
            update();

        } else {
            qDebug() << "Can't buff  here!";
        }
    }
}

void GameWindow::debuffJump() {
    if (_isPaused) {
        // 只对选中的怪物施加buff
        // 输出选中怪物的坐标，不能用格子的坐标替代
        // 将unit转换为enemy
        Enemy *enemy = dynamic_cast<Enemy *>(_selectedUnit);
        if (enemy) {
            qDebug() << "selected enemy: " << enemy->_x << " " << enemy->_y;
        }

        // 如果被选中的怪物高亮，则检查怪物类型，清除闪现buff
        if (enemy->_isHighlighted) {

            qDebug() << "Debuff jump here!";
            // debuff怪物
            enemy->debuffJump();
            // 清除selectedGrid
            enemy->_isHighlighted = false;
            _selectedUnit = nullptr;
            update();

        } else {
            qDebug() << "Can't debuff jummp here!";
        }
    }
}

void GameWindow::buffSpeed() {
    if (_isPaused) {
        // 只对选中的怪物施加buff
        // 输出选中怪物的坐标，不能用格子的坐标替代
        // 将unit转换为enemy
        Enemy *enemy = dynamic_cast<Enemy *>(_selectedUnit);
        if (enemy) {
            qDebug() << "selected enemy: " << enemy->_x << " " << enemy->_y;
        }

        // 如果被选中的怪物高亮，则检查怪物类型，施加神速buff
        if (enemy->_isHighlighted) {

            qDebug() << "Buff PATH enemy here!";
            // buff怪物
            enemy->buffSpeed();
            // 清除selectedGrid
            enemy->_isHighlighted = false;
            _selectedUnit = nullptr;
            update();

        } else {
            qDebug() << "Can't buff  here!";
        }
    }
}

void GameWindow::debuffSpeed() {
    if (_isPaused) {
        // 只对选中的怪物施加buff
        // 输出选中怪物的坐标，不能用格子的坐标替代
        // 将unit转换为enemy
        Enemy *enemy = dynamic_cast<Enemy *>(_selectedUnit);
        if (enemy) {
            qDebug() << "selected enemy: " << enemy->_x << " " << enemy->_y;
        }

        // 如果被选中的怪物高亮，则检查怪物类型，清除神速buff
        if (enemy->_isHighlighted) {

            qDebug() << "Debuff speed here!";
            // debuff怪物
            enemy->debuffSpeed();
            // 清除selectedGrid
            enemy->_isHighlighted = false;
            _selectedUnit = nullptr;
            update();

        } else {
            qDebug() << "Can't debuff speed here!";
        }
    }
}

// 绘图事件 绘制画面上的所有内容
void GameWindow::showEvent(QShowEvent *event) {
    QDialog::showEvent(event);
    _gameTimerID = startTimer(1000);
    _spawnTimerID = startTimer(3000); // 每隔3秒生成一个新怪物
}
void GameWindow::paintEvent(QPaintEvent *) {

    QPainter painter(this);
    QString path =
        R"(..\..\.\assets\bg_day.png)";
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

    // 绘图事件
    updateLabels();

    _holyWater += g_holywater_speed;
    if (event->timerId() == _gameTimerID) {
        // 使用迭代器遍历所有敌人，以便在遍历过程中安全地删除敌人
        for (auto it = _enemies.begin(); it != _enemies.end();) {
            Enemy *enemy = *it;
            // 检查血量
            if (enemy->_hp_cur <= 0) {
                enemy->_state = EnemyState::DEAD;
                if (_canBuffTower == false) {
                    // std::cout << "你被剥夺了无限tower buff（记得改为获得）"
                    //           << std::endl;
                    std::cout << "You're in luck! Auto pick gets unlimited "
                                 "buff, buff tower"
                              << std::endl;
                    _canBuffTower = true;
                }
            }

            // 根据敌人的状态执行不同的操作
            if (enemy->_state == EnemyState::MOVING) {
                enemy->move(); // 如果敌人正在移动，调用移动函数
                ++it;          // 移动到下一个敌人
            } else if (enemy->_state == EnemyState::ATTACKING) {
                enemy->attack(); // 如果敌人正在攻击，调用攻击函数
                ++it;            // 移动到下一个敌人
            } else if (enemy->_state == EnemyState::ARRIVED &&
                       !enemy->_isArrivedCounted) {
                _arrivedEnemies++;               // 记录到达的敌人数量
                enemy->_isArrivedCounted = true; // 标记敌人已被计数
                if (_arrivedEnemies >= 10) {
                    // 弹出失败窗口
                    QMessageBox::information(this, "Game Over", "You Lose!");
                    this->hide();    // 隐藏当前窗口
                    _parent->show(); // 显示父窗口
                    return;
                }
                // 如果敌人已到达终点且被计数，移除敌人
                it = _enemies.erase(it);
                delete enemy; // 释放敌人对象的内存
            } else if (enemy->_state == EnemyState::DEAD) {
                g_coins += 10;

                // 删除敌人
                it = _enemies.erase(it);
                delete enemy; // 释放敌人对象的内存
            } else {
                ++it; // 移动到下一个敌人
            }
        }

        // 迭代器遍历塔，根据塔的状态执行不同的操作
        for (auto it = _towers.begin(); it != _towers.end();) {
            Tower *tower = *it;
            if (tower->_hp_cur <= 0) {
                tower->_state = TowerState::DEAD;
                // 由坐标找到塔所在的格子，恢复格子的未种植
                _map->_all_grids[tower->_y][tower->_x]->isplanted = false;
                if (_canBuffEnemy == false) {
                    // std::cout << "你被剥夺了无限enemy buff（记得改为获得）"
                    //           << std::endl;
                    std::cout << "You're in unluck! Auto pick gets unlimited "
                                 "buff, buff enemies"
                              << std::endl;

                    _canBuffEnemy = true;
                }
            }

            if (tower->_state == TowerState::IDLE) {
                // 如果塔处于空闲状态，执行相应函数
                tower->idle();
                ++it;
            } else if (tower->_state == TowerState::ATTACKING) {
                // 如果塔正在攻击，执行相应的代码
                tower->attack();
                ++it;
            } else if (tower->_state == TowerState::DEAD) {
                g_coins -= 2;

                // 如果塔已经死亡，删除塔
                it = _towers.erase(it);
                delete tower;
            } else {
                ++it; // 移动到下一个塔
            }
        }

        update(); // 确保在所有敌人都移动后再更新界面
    }
    if (event->timerId() == _spawnTimerID) {
        if (_spawnedEnemies < 10) {
            std::vector<std::pair<int, int>> path =
                this->_map->_monsterPaths[0];
            Enemy *enemy = new Boar(path, this->_map);
            this->_enemies.push_back(enemy);
            _spawnedEnemies++;
            int randomSpawnInterval =
                QRandomGenerator::global()->bounded(4000) + 3000;
            // int randomSpawnInterval = 1000;
            _spawnTimerID = startTimer(randomSpawnInterval);
        } else if (10 < _spawnedEnemies < 20) {
            std::vector<std::pair<int, int>> path =
                this->_map->_monsterPaths[1];
            Enemy *enemy = new Boar(path, this->_map);
            this->_enemies.push_back(enemy);
            _spawnedEnemies++;
            int randomSpawnInterval =
                QRandomGenerator::global()->bounded(4000) + 3000;
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
        bool towerSelected = false; // 标志变量，表示是否选中了塔

        // 检查 _enemies 是否为空
        if (!_enemies.empty()) {
            for (auto enemy : _enemies) {
                // 检查 enemy 是否为 nullptr
                if (enemy && enemy->contains(clickPos)) {
                    enemy->highlight();
                    _selectedUnit = enemy;
                    enemySelected = true; // 设置标志变量
                    update();

                    break;
                }
            }
        }

        // 检查 _towers 是否为空
        if (!_towers.empty()) {
            for (auto tower : _towers) {
                // 检查 tower 是否为 nullptr
                if (tower && tower->contains(clickPos)) {
                    tower->highlight();
                    _selectedUnit = tower;
                    towerSelected = true; // 设置标志变量
                    update();

                    break;
                }
            }
        }

        // 如果没有选中怪物和塔，则选中格子
        if (!enemySelected && !towerSelected && !_map->_all_grids.empty()) {
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
