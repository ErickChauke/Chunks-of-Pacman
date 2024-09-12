//Text.cpp
#include "Text.h"

Text::Text(const raylib::Font& font) : font_(font) {}

void Text::writeToScreen(const std::string& content, float size, const raylib::Vector2& position, const raylib::Color& color)
{ 
    text_.SetFont(font_);
    text_.SetFontSize(size);
    text_.SetColor(color);
    text_.SetText(content);
    text_.Draw(position);
}