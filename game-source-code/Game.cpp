// Game.cpp
#include "Game.h"

Game::Game(int width, int height, const std::string& title)
    : window_(width, height, title), showingSplash_(true),
    showGamePlay_(false), startDuration_(2.0f)
{
    loadResources();
}

Game::~Game() = default;

void Game::run() {}

void Game::update() {}

void Game::draw() {}

void Game::initializeWindow(int width, int height, const std::string& title) {
    // Window initialization logic (if more complex setup is needed)
}

void Game::loadResources() {}
