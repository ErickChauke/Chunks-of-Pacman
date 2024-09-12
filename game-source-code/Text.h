//Text.h
#pragma once
#include <raylib-cpp.hpp>
#include <string>

class Text {
public:
    Text(const raylib::Font& font);

    void writeToScreen(const std::string& content, float size, const raylib::Vector2& position, const raylib::Color& color);

private:
    raylib::Text text_;
    const raylib::Font& font_;
};