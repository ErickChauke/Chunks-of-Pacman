// Maze.cpp
#include "Maze.h"
#include <fstream>

Maze::Maze(int width, int height) : tileSize_(20), pacmanStartPos_(0, 0), width_(width), height_(height) {
    wallTexture_ = raylib::Texture2D("../resources/brick.png");
}

void Maze::loadMaze(const std::string& filename) { }

void Maze::draw() {}