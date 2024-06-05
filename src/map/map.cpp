
#include "include/map/map.h"
#include "map/grid.h"
#include "utils/grid_type.h"

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

    // // 将——gridMatrix中的数字按照矩阵的形式输出
    // for (const auto &row : _gridMatrix) {
    //     for (const auto &elem : row) {
    //         std::cout << elem << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // 将grid存入 std::vector<std::vector<Grid *>> _all_grids;
    for (int row_index = 0; row_index < _gridMatrix.size(); ++row_index) {
        std::vector<Grid *> row;
        for (int col_index = 0; col_index < _gridMatrix[row_index].size(); ++col_index) {
            GridType type = static_cast<GridType>(_gridMatrix[row_index][col_index]);
            Grid *grid = new Grid(col_index, row_index, type, false);
            row.push_back(grid);
        }
        _all_grids.push_back(row);
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
    // 绘制地图 i行j列 iy jx
    for (int row_index = 0; row_index < _all_grids.size(); ++row_index) {
        for (int col_index = 0; col_index < _all_grids[row_index].size(); ++col_index) {
            Grid *grid = _all_grids[row_index][col_index];
            if (grid) {
                grid->paint(painter, nullptr, nullptr);
            }
        }
    }
}
