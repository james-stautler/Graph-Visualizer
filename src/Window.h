
#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Graph.h"
#include <iostream>

class Window {
private:
    int width;
    int height;
    std::string title;
    int framerateLimit;
    sf::RenderWindow window;
    sf::Font font;

    Graph graph;

public:
    Window(int width, int height, const std::string &title, int framerateLimit, sf::Font font);

    sf::RenderWindow& getWindow();
    Graph& getGraph();
    bool addNode(const Node& node);
    void drawGraph();
    void update();
};

#endif //WINDOW_H
