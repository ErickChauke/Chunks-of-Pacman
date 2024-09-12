#pragma once
#include <raylib-cpp.hpp>
#include "Maze.h"

class Pacman {
public:
    Pacman(const std::string& texturePath, int tileSize);
    ~Pacman();

    void update(Maze& maze);
    void draw();
    void setPosition(const raylib::Vector2& newPosition);

private:
    raylib::Texture2D texture_;  // Pacman's texture (spritesheet with three mouth positions)
    raylib::Rectangle sourceRec_; // Source rectangle for sprite animation
    raylib::Rectangle destRec_;   // Destination rectangle on the screen
    raylib::Vector2 position_;    // Pacman's position
    raylib::Vector2 offset_;      // Offset to adjust drawing

    float rotation_;  // Pacman's rotation angle
    float speed_;     // Movement speed
    float scale_;     // Scale of the sprite
    int spriteSize_;  // Size of one Pacman frame
    int tileSize_;    // Size of the maze tile

    // Attributes for handling direction
    enum Direction { UP, DOWN, LEFT, RIGHT, NONE };
    Direction currentDirection_;
    Direction nextDirection_;

    // Attributes for sprite animation
    int currentFrame_;     // Current frame in the spritesheet (0, 1, 2 for open, middle, closed)
    int totalFrames_;      // Total number of frames (3 for the mouth animation)
    float animationTime_;  // Time accumulator for animating the sprite
    float frameDuration_;  // Duration of each frame in seconds

    bool canMove(const Maze& maze, const raylib::Vector2& newPosition) const;
};
