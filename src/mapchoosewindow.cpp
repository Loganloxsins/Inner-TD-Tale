#include "mapchoosewindow.h"
#include "ui_mapchoosewindow.h"
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QMessageBox>
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
}

MapChooseWindow::~MapChooseWindow() { delete ui; }

void MapChooseWindow::onMapChooseClicked() {
    // Code to choose map
    qDebug() << "map choose";

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
                // JSON解析成功，这里可以根据需要处理解析后的数据
                // 例如，将jsonDoc.toVariant().toMap()转换为QVariantMap进行进一步处理
                qDebug() << "JSON data loaded successfully";

                // 打印JSON文件内容
                qDebug() << "JSON content:"
                         << jsonDoc.toJson(QJsonDocument::Indented);
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
