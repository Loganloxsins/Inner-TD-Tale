#include "mapchoosewindow.h"
#include "ui_mapchoosewindow.h"
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QMessageBox>

#include "map/map.h"
#include <iostream>

MapChooseWindow::MapChooseWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::MapChooseWindow), _parent(parent) {
    ui->setupUi(this);
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
    connect(ui->pushButton_Shopping, SIGNAL(clicked()), this,
            SLOT(onShoppingClicked()));

    _gameWindow = nullptr;
}

MapChooseWindow::~MapChooseWindow() { delete ui; }

void MapChooseWindow::onShoppingClicked() {
    _shoppingWindow = new shopping(this);
    _shoppingWindow->show();
    this->hide();
}
void MapChooseWindow::onMapChooseClicked() {
    QString dialogTitle = "Select Map File";  // 对话框标题
    QString defaultDir = QDir::currentPath(); // 默认打开的目录
    QString fileFilter =
        "JSON Save Files (*.json);;All Files (*.*)"; // 修改过滤器以查找.json文件

    // 弹出文件选择对话框并获取选中的文件路径
    QString selectedFile =
        QFileDialog::getOpenFileName(this, dialogTitle, defaultDir, fileFilter);

    // 从字符串最后一个斜线后面开始提取文件名
    // 提取文件名 Selected file:
    // "E:/MyProject/s6/cpp_final_proj/Inner-TD-Tale/data/map/map1.json"
    // 提取文件名 Selected file:  "map1.json"
    QString fileName = selectedFile.mid(selectedFile.lastIndexOf("/") + 1);

    // 如果fileName是“map1`.josn” 则创建地图1
    if (fileName == "map1.json") {
        onLevel1Clicked();

    } else if (fileName == "map2.json") {
        onLevel2Clicked();
    } else {
        // 弹出窗口显示 请选择正确的地图
        QMessageBox::information(this, "please choose correct map",
                                 "please choose correct map");
    }
}

void MapChooseWindow::onEnterClicked() {
    if (_gameWindow == nullptr) {
        std::cout << "please a leavel" << std::endl;
    } else {
        _gameWindow->show();
        this->hide();
    }
}

void MapChooseWindow::onBackClicked() {
    _parent->show();
    this->hide();
}

void MapChooseWindow::onLevel1Clicked() {
    // 弹出窗口显示 感谢选择地图1
    QMessageBox::information(this, "thank you", "you choose map 1");
    std::cout << "creating map 1" << std::endl;
    _gameWindow = new GameWindow(this, 1);
}

void MapChooseWindow::onLevel2Clicked() {
    // 弹出窗口显示 感谢选择地图1
    QMessageBox::information(this, "thank you", "you choose map 2");
    std::cout << "creating map 2" << std::endl;
    _gameWindow = new GameWindow(this, 2);
}
