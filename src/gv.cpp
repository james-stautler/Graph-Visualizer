#include "Window.h"
#include "Button.h"
#include <iostream>

enum STATE {
    GRAPH_CREATION,
    ALGORITHM
};

enum GRAPH_CREATION_STATE {
    CREATE,
    DELETE,
    RANDOM,
    SELECT_START,
    SELECT_END
};

int main()
{
    constexpr int WIDTH = 1920;
    constexpr int HEIGHT = 1080;
    constexpr int FRAMERATE_LIMIT = 60;

    constexpr int NODE_RADIUS = 15;
    constexpr int NODE_PADDING = 30;
    constexpr int CREATION_BUTTON_BASE_X = 1650;
    constexpr int CREATION_BUTTON_BASE_Y = 100;
    constexpr int SELECT_NODE_BUTTON_BASE_X = 1650;
    constexpr int SELECT_NODE_BUTTON_BASE_Y = 350;
    constexpr int ALGORITHM_BUTTON_BASE_X = 1650;
    constexpr int ALGORITHM_BUTTON_BASE_Y = 535;
    constexpr int START_BUTTON_BASE_X = 1650;
    constexpr int START_BUTTON_BASE_Y = 720;
    constexpr int BUTTON_HEIGHT = 50;
    constexpr int BUTTON_WIDTH = 200;

    constexpr int RANDOM_NODES = 75;
    constexpr int RANDOM_EDGES = 100;

    const std::string TITLE = "Graph Visualizer";
    const sf::Font font("../assets/swansea.ttf");

    const sf::Color BLACK = sf::Color::Black;
    const sf::Color RED = sf::Color::Red;
    const sf::Color GREEN = sf::Color::Green;
    const sf::Color BLUE = sf::Color::Blue;
    const sf::Color LIGHT_GRAY = sf::Color {148, 148, 148};
    const sf::Color DARK_GRAY = sf::Color { 84, 84, 84 };
    const sf::Color ORANGE = sf::Color { 255, 165, 0 };

    auto win = Window(WIDTH, HEIGHT, TITLE, FRAMERATE_LIMIT, font);

    Button nodeCreationButton = Button(CREATION_BUTTON_BASE_X, CREATION_BUTTON_BASE_Y, BUTTON_WIDTH, BUTTON_HEIGHT, true, DARK_GRAY, LIGHT_GRAY, "Create Node");
    Button nodeDeletionButton = Button(CREATION_BUTTON_BASE_X, CREATION_BUTTON_BASE_Y + (65 * 1), BUTTON_WIDTH, BUTTON_HEIGHT, false, DARK_GRAY, LIGHT_GRAY, "Delete Node");
    Button randomGraphButton = Button(CREATION_BUTTON_BASE_X, CREATION_BUTTON_BASE_Y + (65 * 2), BUTTON_WIDTH, BUTTON_HEIGHT, false, DARK_GRAY, LIGHT_GRAY, "Random Graph");
    Button selectStartNodeButton = Button(SELECT_NODE_BUTTON_BASE_X, SELECT_NODE_BUTTON_BASE_Y, BUTTON_WIDTH, BUTTON_HEIGHT, false, DARK_GRAY, LIGHT_GRAY, "Choose Start Node");
    Button selectEndNodeButton = Button(SELECT_NODE_BUTTON_BASE_X, SELECT_NODE_BUTTON_BASE_Y + (65 * 1), BUTTON_WIDTH, BUTTON_HEIGHT, false, DARK_GRAY, LIGHT_GRAY, "Choose End Node");
    Button bfsButton = Button(ALGORITHM_BUTTON_BASE_X, ALGORITHM_BUTTON_BASE_Y, BUTTON_WIDTH, BUTTON_HEIGHT, false, DARK_GRAY, LIGHT_GRAY, "BFS");
    Button dfsButton = Button(ALGORITHM_BUTTON_BASE_X, ALGORITHM_BUTTON_BASE_Y + (65 * 1), BUTTON_WIDTH, BUTTON_HEIGHT, false, DARK_GRAY, LIGHT_GRAY, "DFS");
    Button startButton = Button(SELECT_NODE_BUTTON_BASE_X, START_BUTTON_BASE_Y, BUTTON_WIDTH, BUTTON_HEIGHT, false, DARK_GRAY, LIGHT_GRAY, "Start");

    win.addButton(std::reference_wrapper<Button>(nodeCreationButton));
    win.addButton(std::reference_wrapper<Button>(nodeDeletionButton));
    win.addButton(std::reference_wrapper<Button>(randomGraphButton));
    win.addButton(std::reference_wrapper<Button>(selectStartNodeButton));
    win.addButton(std::reference_wrapper<Button>(selectEndNodeButton));
    win.addButton(std::reference_wrapper<Button>(bfsButton));
    win.addButton(std::reference_wrapper<Button>(dfsButton));
    win.addButton(std::reference_wrapper<Button>(startButton));

    int selectedId_1 = -1; // Selected src node
    int selectedId_2 = -1; // Selected dst node

    int startId = -1;
    int endId = -1;

    GRAPH_CREATION_STATE graphCreationState = CREATE;

    while (win.getWindow().isOpen()) {

        while (const std::optional event = win.getWindow().pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                win.getWindow().close();
            }

            if (event->is<sf::Event::MouseButtonPressed>()) {
                sf::Vector2i pos = sf::Mouse::getPosition(win.getWindow());
                // Graph creation/select block
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
                                } else if (nodeColor == ORANGE) {
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
                                if (win.getNodeColor(selectedId_1) != ORANGE) {
                                    win.setNodeColor(selectedId_1, GREEN);
                                }
                                if (win.getNodeColor(selectedId_2) != ORANGE) {
                                    win.setNodeColor(selectedId_2, GREEN);
                                }
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
                    } else if (graphCreationState == SELECT_START) {
                        if (nodeId != -1) {
                            if (startId != -1) {
                                win.setNodeColor(startId, GREEN);
                            }
                            startId = nodeId;
                            win.setNodeColor(startId, ORANGE);
                        }
                    } else if (graphCreationState == SELECT_END) {
                        if (nodeId != -1) {
                            if (endId != -1) {
                                win.setNodeColor(endId, GREEN);
                            }
                            endId = nodeId;
                            win.setNodeColor(endId, ORANGE);
                        }
                    }
                } else {
                    // Handle button functionality
                    if (nodeCreationButton.isWithinBounds(pos.x, pos.y)) {
                        graphCreationState = CREATE;
                        win.setAllButtonsInactive();
                        nodeCreationButton.flipActiveState();
                    } else if (nodeDeletionButton.isWithinBounds(pos.x, pos.y)) {
                        graphCreationState = DELETE;
                        win.setAllButtonsInactive();
                        nodeDeletionButton.flipActiveState();
                    } else if (randomGraphButton.isWithinBounds(pos.x, pos.y)) {
                        graphCreationState = RANDOM;
                        win.setAllButtonsInactive();
                        randomGraphButton.flipActiveState();
                        win.generateRandomGraphBidirectional(RANDOM_NODES, RANDOM_EDGES, NODE_RADIUS, NODE_PADDING, GREEN, false);
                        selectedId_1 = -1;
                        selectedId_2 = -1;
                        startId = -1;
                        endId = -1;
                    } else if (selectStartNodeButton.isWithinBounds(pos.x, pos.y)) {
                        graphCreationState = SELECT_START;
                        win.setAllButtonsInactive();
                        selectStartNodeButton.flipActiveState();
                    } else if (selectEndNodeButton.isWithinBounds(pos.x, pos.y)) {
                        graphCreationState = SELECT_END;
                        win.setAllButtonsInactive();
                        selectEndNodeButton.flipActiveState();
                    } else if (bfsButton.isWithinBounds(pos.x, pos.y)) {
                        // TODO: ALGORITHM
                    } else if (dfsButton.isWithinBounds(pos.x, pos.y)) {
                        // TODO: ALGORITHM
                    }
                }
            }
        }

        win.getWindow().clear();
        win.update();
        for (auto& button: win.getButtons()) {
            win.drawButton(button);
        }
        win.getWindow().display();
    }
}
