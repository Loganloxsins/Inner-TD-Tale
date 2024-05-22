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
    connect(ui->pushButton_LoadSave, SIGNAL(clicked()), this,
            SLOT(onLoadSaveClicked()));
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
void MainWindow::onLoadSaveClicked() {
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

void MainWindow::onExitClicked() {
    // Code to exit the game
    qDebug() << "exit";
    QCoreApplication::quit();
}
