
#include "Button.h"

Button::Button(int x, int y, int width, int height, bool active, sf::Color activeColor, sf::Color inactiveColor, const std::string& text) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->active = active;
    this->activeColor = activeColor;
    this->inactiveColor = inactiveColor;
    this->text = text;
}

void Button::flipActiveState() {
    if (this->active) {
        this->active = false;
    } else {
        this->active = true;
    }
}

int Button::getX() {
    return this->x;
}

int Button::getY() {
    return this->y;
}

int Button::getWidth() {
    return this->width;
}

int Button::getHeight() {
    return this->height;
}

std::string Button::getText() {
    return this->text;
}

sf::Color Button::getCurrentColor() {
    if (this->active) {
        return this->activeColor;
    } else {
        return this->inactiveColor;
    }
}

bool Button::isActive() {
    return this->active;
}

bool Button::isWithinBounds(int x, int y) {
    return (x >= this->x) && (x <= this->x + this->width) && (y >= this->y) && (y <= this->y + this->height);
}






