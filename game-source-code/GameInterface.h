// GameInterface.h
#pragma once
#include <string>

class GameInterface {
public:
    virtual ~GameInterface() = default;
    virtual void run() = 0;
protected:
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void initializeWindow(int width, int height, const std::string& title) = 0;
    virtual void loadResources() = 0;
};
