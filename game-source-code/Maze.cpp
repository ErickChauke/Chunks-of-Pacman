// Maze.cpp
#include "Maze.h"
#include <fstream>

Maze::Maze(int width, int height) : tileSize_(20), pacmanStartPos_(0, 0), width_(width), height_(height) {
    wallTexture_ = raylib::Texture2D("../resources/brick.png");
}

void Maze::loadMaze(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        grid_.push_back(line);
    }

    for (int y = 0; y < grid_.size(); ++y) {
        for (int x = 0; x < grid_[y].size(); ++x) {
            if (grid_[y][x] == 'P') {
                pacmanStartPos_ = raylib::Vector2(x * tileSize_, y * tileSize_);
                grid_[y][x] = '.'; // Replace 'P' with a dot
            }
        }
    }
}

void Maze::draw() {
    for (int y = 0; y < grid_.size(); ++y) {
        for (int x = 0; x < grid_[y].size(); ++x) {
            raylib::Rectangle destRec{static_cast<float>(x * tileSize_), static_cast<float>(y * tileSize_), static_cast<float>(tileSize_), static_cast<float>(tileSize_)};
            switch (grid_[y][x]) {
                case '#':
                    // Draw wall (blue)
                    DrawRectangleRec(destRec, BLUE);
                    break;
                case '.':
                    // We will draw
                    break;
                case 'o':
                    //we will Draw power pellet   
                    break;
            }
        }
    }
}

bool Maze::isWall(int x, int y) const {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) 
    {return true;  } // Treat out of bounds as walls
    return grid_[y][x] == '#';
}