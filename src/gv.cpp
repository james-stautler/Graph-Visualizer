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

void resetSelectedIds(int& selected_1, int& selected_2) {
    selected_1 = -1;
    selected_2 = -1;
};

void resetStartEndIds(int& start, int& end) {
    start = -1;
    end = -1;
}

int main(int argc, char *argv[])
{
    constexpr int WIDTH = 1920;
    constexpr int HEIGHT = 1080;
    constexpr int GRAPH_AREA_LIMIT_X = WIDTH * 0.8;
    constexpr int GRAPH_AREA_LIMIT_Y = HEIGHT * 0.9;
    constexpr int FRAMERATE_LIMIT = 60;

    constexpr int NODE_RADIUS = 15;
    constexpr int NODE_PADDING = 30;
    constexpr int CREATION_BUTTON_BASE_X = 1600;
    constexpr int CREATION_BUTTON_BASE_Y = 100;
    constexpr int SELECT_NODE_BUTTON_BASE_X = 1600;
    constexpr int SELECT_NODE_BUTTON_BASE_Y = 415;
    constexpr int ALGORITHM_BUTTON_BASE_X = 1600;
    constexpr int ALGORITHM_BUTTON_BASE_Y = 600;
    constexpr int QUIT_BUTTON_BASE_X = 1600;
    constexpr int QUIT_BUTTON_BASE_Y = 800;
    constexpr int BUTTON_HEIGHT = 50;
    constexpr int BUTTON_WIDTH = 250;

    int RANDOM_NODES = 20;
    int RANDOM_EDGES = 30;
    constexpr int ALGORITHM_SPEED = 1;

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
    Button quitButton = Button(QUIT_BUTTON_BASE_X, QUIT_BUTTON_BASE_Y, BUTTON_WIDTH, BUTTON_HEIGHT, false, DARK_GRAY, LIGHT_GRAY, "Quit");

    win.addButton(std::reference_wrapper<Button>(nodeCreationButton));
    win.addButton(std::reference_wrapper<Button>(nodeDeletionButton));
    win.addButton(std::reference_wrapper<Button>(randomGraphButton));
    win.addButton(std::reference_wrapper<Button>(clearGraphButton));
    win.addButton(std::reference_wrapper<Button>(selectStartNodeButton));
    win.addButton(std::reference_wrapper<Button>(selectEndNodeButton));
    win.addButton(std::reference_wrapper<Button>(bfsButton));
    win.addButton(std::reference_wrapper<Button>(dfsButton));
    win.addButton(std::reference_wrapper<Button>(quitButton));

    const std::string EDGE_MODIFICATION_STRING = "* Use the create node function and select two nodes to create or delete the edge between them.";
    sf::Text edgeModificationText = sf::Text(font, EDGE_MODIFICATION_STRING);
    edgeModificationText.setCharacterSize(15);
    edgeModificationText.setFillColor(WHITE);
    sf::Vector2f edgeModificationTextPosition = sf::Vector2f(150, 960);
    edgeModificationText.setPosition(edgeModificationTextPosition);
    win.addText(std::reference_wrapper<sf::Text>(edgeModificationText));

    const std::string NODE_COLOR_STRING = "* During traversal orange nodes indicate frontier nodes (those on queue/stack), green indicates fully explored nodes, pink indicates start/goal nodes, and red indicates unexplored nodes.";
    sf::Text nodeColorText = sf::Text(font, NODE_COLOR_STRING);
    nodeColorText.setCharacterSize(15);
    nodeColorText.setFillColor(WHITE);
    sf::Vector2f nodeColorTextPosition = sf::Vector2f(150, 985);
    nodeColorText.setPosition(nodeColorTextPosition);
    win.addText(std::reference_wrapper<sf::Text>(nodeColorText));

    const std::string RANDOM_GRAPH_TEXT = "* You can modify the number of random nodes and edges by changing RANDOM_NODES and RANDOM_EDGES in the source code. Can also adjust animation speed with ALGORITHM_SPEED variable.";
    sf::Text randomGraphText = sf::Text(font, RANDOM_GRAPH_TEXT);
    randomGraphText.setCharacterSize(15);
    randomGraphText.setFillColor(WHITE);
    sf::Vector2f randomGraphTextPosition = sf::Vector2f(150, 1010);
    randomGraphText.setPosition(randomGraphTextPosition);
    win.addText(std::reference_wrapper<sf::Text>(randomGraphText));

    int selectedId_1 = -1; // Selected src node
    int selectedId_2 = -1; // Selected dst node

    int startId = -1; // Graph algorithm start node
    int endId = -1; // Graph algorithm target node

    GRAPH_CREATION_STATE graphCreationState = CREATE;

    while (win.getWindow().isOpen()) {

        bool reset = false;

        while (const std::optional event = win.getWindow().pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                win.getWindow().close();
            }

            if (event->is<sf::Event::MouseButtonPressed>()) {
                sf::Vector2i pos = sf::Mouse::getPosition(win.getWindow());
                if (pos.x <= GRAPH_AREA_LIMIT_X && pos.y <= GRAPH_AREA_LIMIT_Y) {
                    int nodeId = win.getGraph().checkWithinNodeBoundary(pos.x, pos.y);
                    if (graphCreationState == CREATE) {
                        if (nodeId != -1) {
                            if (win.getGraph().getNodeMap().at(nodeId).strictlyWithinBounds(pos.x, pos.y)) {
                                sf::Color nodeColor = win.getNodeColor(nodeId);
                                if (nodeColor == RED || nodeColor == PINK) {
                                    if (nodeColor == RED) {
                                        win.setNodeColor(nodeId, BLUE);
                                    }
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
                                resetSelectedIds(selectedId_1, selectedId_2);
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
                        win.generateRandomGraph(RANDOM_NODES, RANDOM_EDGES, NODE_RADIUS, NODE_PADDING, RED, false);
                        resetSelectedIds(selectedId_1, selectedId_2);
                        resetStartEndIds(startId, endId);
                    } else if (clearGraphButton.isWithinBounds(pos.x, pos.y)) {
                        graphCreationState = CLEARED;
                        win.clearGraph();
                        win.setAllButtonsInactive();
                        clearGraphButton.flipActiveState();
                        resetSelectedIds(selectedId_1, selectedId_2);
                        resetStartEndIds(startId, endId);
                    } else if (selectStartNodeButton.isWithinBounds(pos.x, pos.y)) {
                        graphCreationState = SELECT_START;
                        win.setAllButtonsInactive();
                        selectStartNodeButton.flipActiveState();
                    } else if (selectEndNodeButton.isWithinBounds(pos.x, pos.y)) {
                        graphCreationState = SELECT_END;
                        win.setAllButtonsInactive();
                        selectEndNodeButton.flipActiveState();
                    } else if (bfsButton.isWithinBounds(pos.x, pos.y)) {
                        if (startId != -1 && endId != -1) {
                            graphCreationState = NONE;
                            win.setAllButtonsInactive();
                            bfsButton.flipActiveState();
                            if (win.BFS(startId, endId, ALGORITHM_SPEED, false)) {
                                win.resetGraph(false);
                                win.drawPath(startId, endId);
                            } else {
                                win.redOutGraph();
                            };
                            win.update();
                            win.getWindow().display();
                            reset = true;
                            bfsButton.flipActiveState();
                        }
                    } else if (dfsButton.isWithinBounds(pos.x, pos.y)) {
                        if (startId != -1 && endId != -1) {
                            graphCreationState = NONE;
                            win.setAllButtonsInactive();
                            dfsButton.flipActiveState();
                            std::set<int> visited;
                            if (win.DFS(startId, startId, endId, ALGORITHM_SPEED, visited, false)) {
                                win.resetGraph(false);
                                win.drawPath(startId, endId);
                            } else {
                                win.redOutGraph();
                            }
                            win.update();
                            win.getWindow().display();
                            reset = true;
                            dfsButton.flipActiveState();
                        }
                    } else if (quitButton.isWithinBounds(pos.x, pos.y)) {
                        win.getWindow().close();
                    }
                }
            }
        }

        if (reset) {
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            win.resetGraph(true);
            resetSelectedIds(selectedId_1, selectedId_2);
            resetStartEndIds(startId, endId);
        }
        win.update();
        win.getWindow().display();
    }
}
