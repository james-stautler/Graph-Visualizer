
#include "Window.h"

Window::Window(const int width, const int height, const std::string &title, const int framerateLimit) {
    this->width = width;
    this->height = height;
    this->title = title;
    this->framerateLimit = framerateLimit;

    const auto windowSize = sf::Vector2u(this->width, this->height);
    this->window = sf::RenderWindow(sf::VideoMode(windowSize), this->title);
    this->window.setFramerateLimit(this->framerateLimit);
}

sf::RenderWindow& Window::getWindow() {
    return this->window;
};


