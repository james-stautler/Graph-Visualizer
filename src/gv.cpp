#include "Window.h"
#include "Button.h"
#include <thread>

enum GRAPH_CREATION_STATE {
    CREATE,
    DELETE,
    RANDOM,
    CLEARED,
    SELECT_START,
    SELECT_END,
    NONE
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
    constexpr int SELECT_NODE_BUTTON_BASE_Y = 415;
    constexpr int ALGORITHM_BUTTON_BASE_X = 1650;
    constexpr int ALGORITHM_BUTTON_BASE_Y = 600;
    constexpr int BUTTON_HEIGHT = 50;
    constexpr int BUTTON_WIDTH = 200;

    constexpr int RANDOM_NODES = 25;
    constexpr int RANDOM_EDGES = 35;
    constexpr int ALGORITHM_SPEED = 5;

    const std::string TITLE = "Graph Visualizer";
    const sf::Font font("../assets/swansea.ttf");

    const sf::Color RED = sf::Color::Red;
    const sf::Color WHITE = sf::Color::White;
    const sf::Color BLUE = sf::Color::Blue;
    const sf::Color LIGHT_GRAY = sf::Color {148, 148, 148};
    const sf::Color DARK_GRAY = sf::Color { 84, 84, 84 };
    const sf::Color PINK = sf::Color { 255, 105, 180 };

    auto win = Window(WIDTH, HEIGHT, TITLE, FRAMERATE_LIMIT, font);

    Button nodeCreationButton = Button(CREATION_BUTTON_BASE_X, CREATION_BUTTON_BASE_Y, BUTTON_WIDTH, BUTTON_HEIGHT, true, DARK_GRAY, LIGHT_GRAY, "Create Node");
    Button nodeDeletionButton = Button(CREATION_BUTTON_BASE_X, CREATION_BUTTON_BASE_Y + (65 * 1), BUTTON_WIDTH, BUTTON_HEIGHT, false, DARK_GRAY, LIGHT_GRAY, "Delete Node");
    Button randomGraphButton = Button(CREATION_BUTTON_BASE_X, CREATION_BUTTON_BASE_Y + (65 * 2), BUTTON_WIDTH, BUTTON_HEIGHT, false, DARK_GRAY, LIGHT_GRAY, "Random Graph");
    Button clearGraphButton = Button(CREATION_BUTTON_BASE_X, CREATION_BUTTON_BASE_Y + (65 * 3), BUTTON_WIDTH, BUTTON_HEIGHT, false, DARK_GRAY, LIGHT_GRAY, "Clear Graph");
    Button selectStartNodeButton = Button(SELECT_NODE_BUTTON_BASE_X, SELECT_NODE_BUTTON_BASE_Y, BUTTON_WIDTH, BUTTON_HEIGHT, false, DARK_GRAY, LIGHT_GRAY, "Choose Start Node");
    Button selectEndNodeButton = Button(SELECT_NODE_BUTTON_BASE_X, SELECT_NODE_BUTTON_BASE_Y + (65 * 1), BUTTON_WIDTH, BUTTON_HEIGHT, false, DARK_GRAY, LIGHT_GRAY, "Choose End Node");
    Button bfsButton = Button(ALGORITHM_BUTTON_BASE_X, ALGORITHM_BUTTON_BASE_Y, BUTTON_WIDTH, BUTTON_HEIGHT, false, DARK_GRAY, LIGHT_GRAY, "BFS");
    Button dfsButton = Button(ALGORITHM_BUTTON_BASE_X, ALGORITHM_BUTTON_BASE_Y + (65 * 1), BUTTON_WIDTH, BUTTON_HEIGHT, false, DARK_GRAY, LIGHT_GRAY, "DFS");
    Button kruskalButton = Button(ALGORITHM_BUTTON_BASE_X, ALGORITHM_BUTTON_BASE_Y + (65 * 2), BUTTON_WIDTH, BUTTON_HEIGHT, false, DARK_GRAY, LIGHT_GRAY, "Kruskal's MST");
    Button primsButton = Button(ALGORITHM_BUTTON_BASE_X, ALGORITHM_BUTTON_BASE_Y + (65 * 3), BUTTON_WIDTH, BUTTON_HEIGHT, false, DARK_GRAY, LIGHT_GRAY, "Prim's MST");

    win.addButton(std::reference_wrapper<Button>(nodeCreationButton));
    win.addButton(std::reference_wrapper<Button>(nodeDeletionButton));
    win.addButton(std::reference_wrapper<Button>(randomGraphButton));
    win.addButton(std::reference_wrapper<Button>(clearGraphButton));
    win.addButton(std::reference_wrapper<Button>(selectStartNodeButton));
    win.addButton(std::reference_wrapper<Button>(selectEndNodeButton));
    win.addButton(std::reference_wrapper<Button>(bfsButton));
    win.addButton(std::reference_wrapper<Button>(dfsButton));
    win.addButton(std::reference_wrapper<Button>(kruskalButton));
    win.addButton(std::reference_wrapper<Button>(primsButton));

    int selectedId_1 = -1; // Selected src node
    int selectedId_2 = -1; // Selected dst node

    int startId = -1;
    int endId = -1;

    GRAPH_CREATION_STATE graphCreationState = CREATE;

    while (win.getWindow().isOpen()) {

        bool reset = false;

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
                                if (nodeColor == RED) {
                                    win.setNodeColor(nodeId, BLUE);
                                    if (selectedId_1 == -1) {
                                        selectedId_1 = nodeId;
                                    } else if (selectedId_2 == -1) {
                                        selectedId_2 = nodeId;
                                    }
                                } else if (nodeColor == PINK) {
                                    if (selectedId_1 == -1) {
                                        selectedId_1 = nodeId;
                                    } else if (selectedId_2 == -1) {
                                        selectedId_2 = nodeId;
                                    }
                                } else {
                                    win.setNodeColor(nodeId, RED);
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
                                win.edgeHandler(selectedId_1, selectedId_2, true, WHITE);
                                if (win.getNodeColor(selectedId_1) != PINK) {
                                    win.setNodeColor(selectedId_1, RED);
                                }
                                if (win.getNodeColor(selectedId_2) != PINK) {
                                    win.setNodeColor(selectedId_2, RED);
                                }
                                selectedId_1 = -1;
                                selectedId_2 = -1;
                            }

                        } else {
                            win.addNode(Node(win.getGraph().assignNodeId(), pos.x, pos.y, NODE_RADIUS, NODE_PADDING, 1, RED));
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
                                win.setNodeColor(startId, RED);
                            }
                            startId = nodeId;
                            win.setNodeColor(startId, PINK);
                        }
                    } else if (graphCreationState == SELECT_END) {
                        if (nodeId != -1) {
                            if (endId != -1) {
                                win.setNodeColor(endId, RED);
                            }
                            endId = nodeId;
                            win.setNodeColor(endId, PINK);
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
                        win.generateRandomGraphBidirectional(RANDOM_NODES, RANDOM_EDGES, NODE_RADIUS, NODE_PADDING, RED, false);
                        selectedId_1 = -1;
                        selectedId_2 = -1;
                        startId = -1;
                        endId = -1;
                    } else if (clearGraphButton.isWithinBounds(pos.x, pos.y)) {
                        graphCreationState = CLEARED;
                        win.clearGraph();
                        win.setAllButtonsInactive();
                        clearGraphButton.flipActiveState();
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
                        graphCreationState = NONE;
                        win.setAllButtonsInactive();
                        bfsButton.flipActiveState();
                        if (startId != -1 && endId != -1) {
                            if (win.BFS(startId, endId, ALGORITHM_SPEED, false)) {
                                win.resetGraph(false);
                                win.drawPath(startId, endId);
                                win.update();
                                win.getWindow().display();
                            } else {
                                win.redOutGraph();
                                win.update();
                                win.getWindow().display();
                            };
                            reset = true;
                        }
                        bfsButton.flipActiveState();
                    } else if (dfsButton.isWithinBounds(pos.x, pos.y)) {
                        graphCreationState = NONE;
                        win.setAllButtonsInactive();
                        dfsButton.flipActiveState();
                        if (startId != -1 && endId != -1) {
                            std::set<int> visited;
                            if (win.DFS(startId, startId, endId, ALGORITHM_SPEED, visited, false)) {
                                win.resetGraph(false);
                                win.drawPath(startId, endId);
                                win.update();
                                win.getWindow().display();
                            } else {
                                win.redOutGraph();
                                win.update();
                                win.getWindow().display();
                            }
                            reset = true;
                        }
                    } else if (kruskalButton.isWithinBounds(pos.x, pos.y)) {
                        // TODO: KRUSKAL'S ALGORITHM
                    } else if (primsButton.isWithinBounds(pos.x, pos.y)) {
                        // TODO: PRIM'S ALGORITHM
                    }
                }
            }
        }

        if (reset) {
            std::this_thread::sleep_for(std::chrono::milliseconds(4000));
            win.resetGraph(true);
        }
        win.update();
        win.getWindow().display();
    }
}
