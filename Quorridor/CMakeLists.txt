cmake_minimum_required(VERSION 3.21)
project(Quorridor)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Quorridor
        Model/Board.cpp
        Model/Board.hpp
        Model/MotherCell.cpp
        Model/MotherCell.hpp
        Model/Piece.cpp
        Model/Piece.hpp
        Model/Player.cpp
        Model/Player.hpp
        Model/Position.cpp
        Model/Position.hpp
        View/DisplayBoard.cpp
        View/DisplayBoard.hpp
        main.cpp
        Controller/Game.h
        Controller/Game.cpp)


