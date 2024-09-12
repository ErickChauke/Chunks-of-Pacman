// Game.cpp
#include "Game.h"

Game::Game(int width, int height, const std::string& title)
    : window_(width, height, title), font_("../resources/sensation.ttf"),
    text_renderer_(font_), showingSplash_(true),
    showGamePlay_(false), startDuration_(2.0f)
{
    loadResources();
}

Game::~Game() = default;

void Game::run() {
    while (!window_.ShouldClose()) {
        update();
        draw();
    }
}

void Game::update() {
    if (showingSplash_) {
        if (IsKeyPressed(KEY_F1)) {
            showingSplash_ = false;
            helpWindow = true;
        } else if (IsKeyPressed(KEY_ENTER)) {
            showingSplash_ = false;
            helpWindow = false;
            gameplayWindow = true;
            startTimer_=0.0f;
        }
    }
    else if (gameplayWindow) 
    {   
        startTimer_ += GetFrameTime();
        if (startTimer_ >= startDuration_) 
        {
            showingSplash_ = false;
            pacman_->update(*maze_);
            showGamePlay_=false;
        }
        else{showGamePlay_=true;}
        if(IsKeyPressed(KEY_F1))
        {gameplayWindow=false; helpWindow=true; showGamePlay_=false;}
    }
    if(helpWindow)
    {if(IsKeyPressed(KEY_ENTER))
    {gameplayWindow=true; helpWindow=false; showGamePlay_=true; startTimer_=0.0f;}}
}

void Game::draw() {
    window_.BeginDrawing();
    
    if (showingSplash_) {drawSplash();}   
    else if(showGamePlay_)
    {drawStart();}
    else if(helpWindow)
    {drawControls();}
    else{
        window_.ClearBackground(raylib::Color::Black());
        maze_->draw();
        pacman_->draw();
        text_renderer_.writeToScreen("Pacman Game", 30, raylib::Vector2(10, 10), raylib::Color::White());
    }

    window_.EndDrawing();
}

void Game::initializeWindow(int width, int height, const std::string& title) {
    // Window initialization logic (if more complex setup is needed)
}

void Game::loadResources() {
    splashTexture_ = raylib::Texture2D("../resources/splash.png");
    helpTexture_ = raylib::Texture2D("../resources/brick.png");
}

void Game::drawSplash() {
    window_.ClearBackground(raylib::Color::White());
    splashTexture_.Draw(
    raylib::Vector2(
        (window_.GetWidth() - splashTexture_.GetWidth()) / 2,
        (window_.GetHeight() - splashTexture_.GetHeight()) / 2
        )
    );
    
    DrawText("PRESS", window_.GetWidth() / 2 - 100, window_.GetHeight() - 200, 20, WHITE);
    DrawText("F1", window_.GetWidth() / 2 - 20, window_.GetHeight() - 200, 20, Color{static_cast<unsigned char>(GetRandomValue(0, 255)), static_cast<unsigned char>(GetRandomValue(0, 255)), static_cast<unsigned char>(GetRandomValue(0, 255)), 255});
    DrawText("FOR HELP", window_.GetWidth() / 2 + 8, window_.GetHeight() - 200, 20, WHITE);
    DrawText("PRESS", window_.GetWidth() / 2 - 100 - 30, window_.GetHeight() - 175, 20, WHITE);
    DrawText("ENTER", window_.GetWidth() / 2 - 20 - 30, window_.GetHeight() - 175, 20, Color{static_cast<unsigned char>(GetRandomValue(0, 255)), static_cast<unsigned char>(GetRandomValue(0, 255)), static_cast<unsigned char>(GetRandomValue(0, 255)), 255});
    DrawText("TO START", window_.GetWidth() / 2 + 58 - 30, window_.GetHeight() - 175, 20, WHITE); 
}

void Game::drawStart() {
    window_.ClearBackground(raylib::Color::Black());
    text_renderer_.writeToScreen("Starting Game ...", 50, raylib::Vector2(window_.GetWidth() / 2,  window_.GetHeight())/2, raylib::Color::White());
}

void Game::drawControls() {
    helpTexture_.Draw(
    raylib::Vector2(
        (window_.GetWidth() - splashTexture_.GetWidth()) / 2,
        (window_.GetHeight() - splashTexture_.GetHeight()) / 2
        )
    );
    window_.ClearBackground(raylib::Color::Black());
    text_renderer_.writeToScreen("Controls ...", 50, raylib::Vector2(window_.GetWidth() / 2 -100,  window_.GetHeight()-100)/2, raylib::Color::White());
}