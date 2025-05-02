
#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Graph.h"
#include "Button.h"
#include <queue>
#include <set>

class Window {
private:
    int width;
    int height;
    std::string title;
    int framerateLimit;
    sf::RenderWindow window;
    sf::Font font;
    std::vector<std::reference_wrapper<Button>> buttons;
    Graph graph;

public:
    Window(); // Essentially a mock for testing purposes
    Window(int width, int height, const std::string &title, int framerateLimit, sf::Font font);
    sf::RenderWindow& getWindow();
    Graph& getGraph();
    std::vector<std::reference_wrapper<Button>> getButtons();
    sf::Color getNodeColor(int nodeId);

    bool addNode(const Node& node);
    bool removeNode(int nodeId);
    void addButton(std::reference_wrapper<Button> button);
    void setAllButtonsInactive();
    void setNodeColor(int nodeId, sf::Color color);
    void edgeHandler(int srcId, int dstId, bool bidirectional, sf::Color color);
    void generateRandomGraph(int nodes, int edges, int nodeRadius, int padding, sf::Color nodeColor, bool weighted);
    void drawButton(Button& button);
    void drawGraph();
    void update();

    void clearGraph();
    void resetGraph(bool hardReset);
    void redOutGraph();
    void drawPath(int startId, int endId);
    bool BFS(int start, int end, int speed, bool testing);
    bool DFS(int curr, int start, int end, int speed, std::set<int>& visited, bool testing);

};

#endif //WINDOW_H
