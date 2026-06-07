cmake_minimum_required(VERSION 4.0.1)
project(Barrios_Marchan_Anthony__Proyecto_2_)

set(CMAKE_CXX_STANDARD 20)

add_executable(Barrios_Marchan_Anthony__Proyecto_2_ main.cpp
        Entity.cpp
        Entity.h
        Character.cpp
        Character.h
        Inventory.h
        WorldObject.cpp
        WorldObject.h
        Enemy.cpp
        Enemy.h)
