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

void Pacman::update(Maze& maze) {
    raylib::Vector2 newPosition = position_;

    // Handle input and set next direction
    if (IsKeyPressed(KEY_RIGHT)) { nextDirection_ = RIGHT; }
    if (IsKeyPressed(KEY_LEFT))  { nextDirection_ = LEFT; }
    if (IsKeyPressed(KEY_DOWN))  { nextDirection_ = DOWN; }
    if (IsKeyPressed(KEY_UP))    { nextDirection_ = UP; }

    // Switch direction if possible
    if (nextDirection_ != NONE) {
        raylib::Vector2 tempPosition = position_;
        switch (nextDirection_) {
            case RIGHT: tempPosition.x += speed_; break;
            case LEFT:  tempPosition.x -= speed_; break;
            case DOWN:  tempPosition.y += speed_; break;
            case UP:    tempPosition.y -= speed_; break;
            default: break;
        }

        if (canMove(maze, tempPosition)) {
            currentDirection_ = nextDirection_;
            nextDirection_ = NONE;
        }
    }

    // Move in the current direction
    switch (currentDirection_) {
        case RIGHT: newPosition.x += speed_; rotation_ = 0.0f; break;
        case LEFT:  newPosition.x -= speed_; rotation_ = 180.0f; break;
        case DOWN:  newPosition.y += speed_; rotation_ = 90.0f; break;
        case UP:    newPosition.y -= speed_; rotation_ = 270.0f; break;
        default: break;
    }

    // Update Pacman's position if the move is valid
    if (canMove(maze, newPosition)) {
        position_ = newPosition;
    }

    // Update sprite animation
    animationTime_ += GetFrameTime();
    if (animationTime_ >= frameDuration_) {
        currentFrame_ = (currentFrame_ + 1) % totalFrames_;  // Cycle between 0, 1, 2
        animationTime_ = 0.0f;
    }

    // Update sourceRec to select the current sprite frame
    sourceRec_.x = static_cast<float>(currentFrame_) * texture_.GetWidth() / totalFrames_;

    // Update Pacman's destination position for drawing
    destRec_.x = position_.x + offset_.x;
    destRec_.y = position_.y + offset_.y;

    // Check for dot or pellet collisions
    int centerX = static_cast<int>((position_.x + spriteSize_ / 2) / tileSize_);
    int centerY = static_cast<int>((position_.y + spriteSize_ / 2) / tileSize_);
    
    if (maze.isDot(centerX, centerY) || maze.isPowerPellet(centerX, centerY)) {
        maze.removeDot(centerX, centerY);
        // Add score or play sound here
    }
}

void Pacman::draw() {
    texture_.Draw(sourceRec_, destRec_, raylib::Vector2(spriteSize_ / 2.0f, spriteSize_ / 2.0f), rotation_, raylib::Color::Yellow());
}

bool Pacman::canMove(const Maze& maze, const raylib::Vector2& newPosition) const {
    int cornerX[4] = {
        static_cast<int>(newPosition.x),
        static_cast<int>(newPosition.x + spriteSize_ - 1),
        static_cast<int>(newPosition.x),
        static_cast<int>(newPosition.x + spriteSize_ - 1)
    };
    int cornerY[4] = {
        static_cast<int>(newPosition.y),
        static_cast<int>(newPosition.y),
        static_cast<int>(newPosition.y + spriteSize_ - 1),
        static_cast<int>(newPosition.y + spriteSize_ - 1)
    };

    for (int i = 0; i < 4; ++i) {
        int checkX = cornerX[i] / tileSize_;
        int checkY = cornerY[i] / tileSize_;
        if (maze.isWall(checkX, checkY)) {
            return false;
        }
    }
    return true;
}