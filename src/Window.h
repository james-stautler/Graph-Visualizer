//
// Created by James on 4/22/2025.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include <string>

class Window {
private:
    int width;
    int height;
    std::string title;
    int framerateLimit;
    sf::RenderWindow window;

public:
    Window(int width, int height, const std::string &title, int framerateLimit);

    sf::RenderWindow& getWindow();
};

#endif //WINDOW_H
