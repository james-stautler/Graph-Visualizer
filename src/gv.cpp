#include "Window.h"
#include "Button.h"
#include <iostream>

enum STATE {
    GRAPH_CREATION,
    NODE_SELECTION,
    ALGORITHM
};

enum GRAPH_CREATION_STATE {
    CREATE,
    DELETE,
    RANDOM
};

int main()
{
    constexpr int WIDTH = 1920;
    constexpr int HEIGHT = 1080;
    constexpr int FRAMERATE_LIMIT = 60;
    constexpr int NODE_RADIUS = 15;
    constexpr int NODE_PADDING = 30;
    constexpr int BUTTON_HEIGHT = 50;
    constexpr int BUTTON_WIDTH = 175;
    const std::string TITLE = "Graph Visualizer";
    const sf::Font font("../assets/swansea.ttf");

    const sf::Color BLACK = sf::Color::Black;
    const sf::Color RED = sf::Color::Red;
    const sf::Color GREEN = sf::Color::Green;
    const sf::Color BLUE = sf::Color::Blue;
    const sf::Color LIGHT_GRAY = sf::Color {148, 148, 148};
    const sf::Color DARK_GRAY = sf::Color { 84, 84, 84 };

    auto win = Window(WIDTH, HEIGHT, TITLE, FRAMERATE_LIMIT, font);

    std::vector<Button> buttons;
    Button nodeCreationButton = Button(1650, 100, BUTTON_WIDTH, BUTTON_HEIGHT, true, DARK_GRAY, LIGHT_GRAY, "Create Node");
    Button nodeDeletionButton = Button(1650, 165, BUTTON_WIDTH, BUTTON_HEIGHT, false, DARK_GRAY, LIGHT_GRAY, "Delete Node");
    Button randomGraphButton = Button(1650, 230, BUTTON_WIDTH, BUTTON_HEIGHT, false, DARK_GRAY, LIGHT_GRAY, "Random Graph");

    int selectedId_1 = -1; // Selected src node
    int selectedId_2 = -1; // Selected dst node

    STATE state = GRAPH_CREATION;
    GRAPH_CREATION_STATE graphCreationState = CREATE;

    while (win.getWindow().isOpen()) {

        while (const std::optional event = win.getWindow().pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                win.getWindow().close();
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
                                    // All edges are bidirectional as of now
                                    win.edgeHandler(selectedId_1, selectedId_2, true);
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
                        // Handle button functionality
                        if (nodeCreationButton.isWithinBounds(pos.x, pos.y)) {
                            graphCreationState = CREATE;
                            nodeCreationButton.flipActiveState();
                            if (nodeDeletionButton.isActive()) {
                                nodeDeletionButton.flipActiveState();
                            }
                            if (randomGraphButton.isActive()) {
                                randomGraphButton.flipActiveState();
                            }
                        } else if (nodeDeletionButton.isWithinBounds(pos.x, pos.y)) {
                            graphCreationState = DELETE;
                            nodeDeletionButton.flipActiveState();
                            if (nodeCreationButton.isActive()) {
                                nodeCreationButton.flipActiveState();
                            }
                            if (randomGraphButton.isActive()) {
                                randomGraphButton.flipActiveState();
                            }
                        } else if (randomGraphButton.isWithinBounds(pos.x, pos.y)) {
                            graphCreationState = RANDOM;
                            randomGraphButton.flipActiveState();
                            if (nodeCreationButton.isActive()) {
                                nodeCreationButton.flipActiveState();
                            }
                            if (nodeDeletionButton.isActive()) {
                                nodeDeletionButton.flipActiveState();
                            }
                            // TODO: Random Graph Generation
                        }
                    }
                }
            } else if (state == NODE_SELECTION) {
                // TODO: Handle the node selection for the algorithm
            } else if (state == ALGORITHM) {

            }
        }

        win.getWindow().clear();
        win.update();
        win.drawButton(nodeCreationButton);
        win.drawButton(nodeDeletionButton);
        win.drawButton(randomGraphButton);
        win.getWindow().display();
    }
}
