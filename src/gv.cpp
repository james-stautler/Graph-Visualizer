#include "Window.h"
#include <iostream>

enum STATE {
    GRAPH_CREATION,
    NODE_SELECTION,
    ALGORITHM
};

enum GRAPH_CREATION_STATE {
    CREATE,
    DELETE
};

int main()
{
    constexpr int WIDTH = 1920;
    constexpr int HEIGHT = 1080;
    constexpr int FRAMERATE_LIMIT = 60;
    constexpr int NODE_RADIUS = 15;
    constexpr int NODE_PADDING = 30;
    const std::string TITLE = "Graph Visualizer";
    const sf::Font font("../assets/swansea.ttf");

    const sf::Color BLACK = sf::Color::Black;
    const sf::Color GREEN = sf::Color::Green;
    const sf::Color BLUE = sf::Color::Blue;

    auto win = Window(WIDTH, HEIGHT, TITLE, FRAMERATE_LIMIT, font);

    int selectedId_1 = -1; // Selected src node
    int selectedId_2 = -1; // Selected dst node

    STATE state = GRAPH_CREATION;
    GRAPH_CREATION_STATE graphCreationState = CREATE;

    while (win.getWindow().isOpen()) {

        while (const std::optional event = win.getWindow().pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                win.getWindow().close();
            }

            if (event->is<sf::Event::KeyPressed>()) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) {
                    graphCreationState = CREATE;
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) {
                    graphCreationState = DELETE;
                }
            }

            if (state == GRAPH_CREATION) {

                if (event->is<sf::Event::MouseButtonPressed>()) {

                    sf::Vector2i pos = sf::Mouse::getPosition(win.getWindow());
                    // Graph creation block
                    if (pos.x <= WIDTH * 0.8) {
                        int nodeId = win.getGraph().checkWithinNodeBoundary(pos.x, pos.y);
                        if (graphCreationState == CREATE) {
                            if (nodeId != -1) {
                                // Select Nodes
                                if (win.getGraph().getNodeMap().at(nodeId).strictlyWithinBounds(pos.x, pos.y)) {
                                    sf::Color nodeColor = win.getNodeColor(nodeId);
                                    if (nodeColor == GREEN) {
                                        win.setNodeColor(nodeId, BLUE);
                                        if (selectedId_1 == -1) {
                                            selectedId_1 = nodeId;
                                        } else if (selectedId_2 == -1) {
                                            selectedId_2 = nodeId;
                                        }
                                    } else {
                                        win.setNodeColor(nodeId, GREEN);
                                        if (selectedId_1 == nodeId) {
                                            selectedId_1 = -1;
                                        } else if (selectedId_2 == nodeId) {
                                            selectedId_2 = -1;
                                        }
                                    }
                                }
                                // Edge Handler
                                if (selectedId_1 != -1 && selectedId_2 != -1) {
                                    win.edgeHandler(selectedId_1, selectedId_2);
                                    selectedId_1 = -1;
                                    selectedId_2 = -1;
                                }

                            } else {
                                win.addNode(Node(win.getGraph().assignNodeId(), pos.x, pos.y, NODE_RADIUS, NODE_PADDING, 1, GREEN));
                            }
                        } else if (graphCreationState == DELETE) {
                            if (nodeId != -1) {
                                if (win.getGraph().getNodeMap().at(nodeId).strictlyWithinBounds(pos.x, pos.y)) {
                                    win.removeNode(nodeId);
                                }
                            }
                        }
                    } else {
                        // TODO: Handle button functionality here
                    }
                }
            } else if (state == NODE_SELECTION) {
                // TODO: Handle the node selection for the algorithm
            } else if (state == ALGORITHM) {

            }
        }

        win.getWindow().clear();
        win.update();
        win.getWindow().display();
    }
}
