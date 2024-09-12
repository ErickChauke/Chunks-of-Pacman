#pragma once
#include "GameInterface.h"
#include <raylib-cpp.hpp>

class Game : public GameInterface {
public:
    Game(int width, int height, const std::string& title);
    ~Game() override;

    void run() override;
    void update() override;
    void draw() override;

protected:
    void initializeWindow(int width, int height, const std::string& title) override;
    void loadResources() override;

private:
    raylib::Window window_;
    bool showingSplash_;
    bool showGamePlay_;
    float startDuration_;
    float startTimer_; 
    bool helpWindow = false;
    bool gameplayWindow = false;
};
