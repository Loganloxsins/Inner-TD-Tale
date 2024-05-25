
#include "include/map/map.h"
#include "utils/grid_type.h"
#include "map/grid.h"

#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>


Map::Map() {
    _all_grids.clear();
    _gridMatrix.clear();
    _monsterPaths.clear();
}

bool Map::loadMap(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file:" << filePath;
        return false;
    }

    QByteArray jsonData = file.readAll();
    // 打印整个JSON字符串到控制台
    // qDebug() << "Raw JSON content:\n" << jsonData;

    QJsonParseError error;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &error);
    if (jsonDoc.isNull() || error.error != QJsonParseError::NoError) {
        qWarning() << "Failed to parse JSON:" << error.errorString();
        return false;
    }

    QJsonObject jsonObj = jsonDoc.object();

    // 解析地图数据
    if (jsonObj.contains("mapData") && jsonObj["mapData"].isArray()) {
        QJsonArray mapDataArray = jsonObj["mapData"].toArray();
        for (const auto &rowVal : mapDataArray) {
            if (rowVal.isArray()) {
                std::vector<int> row;
                QJsonArray rowArray = rowVal.toArray();
                for (const auto &cellVal : rowArray) {
                    row.push_back(cellVal.toInt());
                }
                _gridMatrix.push_back(row);
            }
        }
    }

    // 解析怪物路径
    if (jsonObj.contains("monsterPaths") && jsonObj["monsterPaths"].isArray()) {
        QJsonArray pathsArray = jsonObj["monsterPaths"].toArray();
        for (const auto &pathVal : pathsArray) {
            if (pathVal.isArray()) {
                std::vector<std::pair<int, int>> path;
                QJsonArray pathArray = pathVal.toArray();
                for (const auto &coordVal : pathArray) {
                    QJsonArray coordArray = coordVal.toArray();
                    if (coordArray.size() == 2) {
                        int x = coordArray[0].toInt();
                        int y = coordArray[1].toInt();
                        path.emplace_back(x, y);
                    }
                }
                _monsterPaths.push_back(path);
            }
        }
    }

    return true;
}

void Map::drawMap(QPainter *painter) {
    // 绘制地图
    for (int i = 0; i < _gridMatrix.size(); ++i) {
        for (int j = 0; j < _gridMatrix[i].size(); ++j) {
            int gridType = _gridMatrix[i][j];
            GridType type = static_cast<GridType>(gridType);
            Grid* grid = new Grid(i, j, type, false);
            grid->paint(painter,nullptr,nullptr);
        }
    }
}
