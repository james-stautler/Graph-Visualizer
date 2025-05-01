
#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Graph.h"
#include "Button.h"
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
    bool removeNode(int nodeId);

    sf::Color getNodeColor(int nodeId);
    void setNodeColor(int nodeId, sf::Color color);
    void edgeHandler(int srcId, int dstId, bool bidirectional);
    void drawButton(Button button);
    void drawGraph();
    void update();
};

#endif //WINDOW_H
