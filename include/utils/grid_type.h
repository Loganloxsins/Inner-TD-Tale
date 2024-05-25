#ifndef GRIDTYPE_H
#define GRIDTYPE_H

enum GridType {
    WALL,
    PATH,   // 路径,或者近战单位 1
    REMOTE, // 非路径，或者远程单位 2
    SPAWN,  // 怪物出生点 3
    DEST,   // 怪物终点 4
};

#endif // GRIDTYPE_H