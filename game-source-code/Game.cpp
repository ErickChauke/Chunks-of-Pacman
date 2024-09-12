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
        {}
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
    else{}

    window_.EndDrawing();
}

void Game::initializeWindow(int width, int height, const std::string& title) {
    // Window initialization logic (if more complex setup is needed)
}

void Game::loadResources() {
    splashTexture_ = raylib::Texture2D("../resources/splash.png");
    helpTexture_ = raylib::Texture2D("../resources/brick.png");
}

void Game::drawSplash() {}
void Game::drawStart() {}
void Game::drawControls() {}