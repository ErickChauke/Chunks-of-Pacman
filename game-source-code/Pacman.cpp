#include "Pacman.h"

Pacman::Pacman(const std::string& texturePath, int tileSize)
    : texture_(texturePath),
    position_(0, 0),
      sourceRec_(0, 0, static_cast<float>(texture_.GetWidth() / 3), static_cast<float>(texture_.GetHeight())),  // Adjust sourceRec to account for 3 frames
    rotation_(0.0f),
      speed_(0.05f),  // Adjust the speed to fit your game
    spriteSize_(tileSize - 2),
    tileSize_(tileSize),
    offset_(10.0f, 10.0f),
    currentDirection_(NONE),
    nextDirection_(NONE),
      currentFrame_(0),    // Start from frame 0 (mouth open)
      totalFrames_(3),     // We have 3 frames (open, middle, closed)
    animationTime_(0.0f),
      frameDuration_(0.1f) // Each frame will be shown for 0.1 seconds
    {
    scale_ = static_cast<float>(spriteSize_) / (texture_.GetWidth() / 3);  // Divide by 3 since we have 3 frames in the texture
    destRec_ = raylib::Rectangle(0, 0, static_cast<float>(spriteSize_), static_cast<float>(spriteSize_));
    }

Pacman::~Pacman() = default;

void Pacman::setPosition(const raylib::Vector2& newPosition) {
    position_ = newPosition;
    destRec_.x = position_.x + offset_.x;
    destRec_.y = position_.y + offset_.y;
}

void Pacman::update(Maze& maze) {}

void Pacman::draw() {
    texture_.Draw(sourceRec_, destRec_, raylib::Vector2(spriteSize_ / 2.0f, spriteSize_ / 2.0f), rotation_, raylib::Color::Yellow());
}

bool Pacman::canMove(const Maze& maze, const raylib::Vector2& newPosition) const {}