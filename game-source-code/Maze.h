// Maze.h
#pragma once
#include <raylib-cpp.hpp>
#include <vector>
#include <string>

class Maze {
public:
    Maze(int width, int height);
    void loadMaze(const std::string& filename);
    void draw();
    int getTileSize() const { return tileSize_; }
    raylib::Vector2 getPacmanStartPosition() const { return pacmanStartPos_; }
    
    bool Maze::isWall(int x, int y) const;
private:
    std::vector<std::string> grid_;
    raylib::Texture2D wallTexture_;
    int tileSize_;
    raylib::Vector2 pacmanStartPos_;
    int width_;
    int height_;
};