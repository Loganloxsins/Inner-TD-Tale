cmake_minimum_required(VERSION 3.23)
project(Inner_TD_Tale)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(include/map)
include_directories(include/unit)
include_directories(include/unit/base)
include_directories(include/unit/enemy)
include_directories(include/unit/tower)

add_executable(Inner_TD_Tale
        include/map/grid.h
        include/map/map.h
        include/map/path.h
        include/unit/base/base_enemy.h
        include/unit/base/base_tower.h
        include/unit/base/base_unit.h
        include/unit/base/melee_tower.h
        include/unit/base/remote_tower.h
        include/unit/enemy/boar.h
        include/unit/tower/knight.h
        include/unit/tower/shooter.h
        include/gamewindow.h
        include/mainwindow.h
        include/mapchoosewindow.h
        src/map/grid.cpp
        src/map/map.cpp
        src/map/path.cpp
        src/gamewindow.cpp
        src/main.cpp
        src/mainwindow.cpp
        src/mapchoosewindow.cpp include/all_include.h)
