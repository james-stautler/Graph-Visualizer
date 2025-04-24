#include "Window.h"

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

    int nodeId_1 = -1;
    int nodeId_2 = -1;

    while (win.getWindow().isOpen()) {

        while (const std::optional event = win.getWindow().pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                win.getWindow().close();
            }

            if (event->is<sf::Event::MouseButtonPressed>()) {

                sf::Vector2i pos = sf::Mouse::getPosition(win.getWindow());

                // Graph creation block
                if (pos.x <= WIDTH * 0.8) {
                    // Check if the clicked position is within node boundary including padding
                    int nodeId = win.getGraph().checkWithinNodeBoundary(pos.x, pos.y);
                    if (nodeId != -1) {
                        // If node directly clicked
                        if (win.getGraph().getNodeMap().at(nodeId).strictlyWithinBounds(pos.x, pos.y)) {
                            sf::Color nodeColor = win.getGraph().getNodeMap().at(nodeId).getColor();
                            if (nodeColor == GREEN) {
                                win.getGraph().getNodeMap().at(nodeId).setColor(BLUE);
                                if (nodeId_1 == -1) {
                                    nodeId_1 = nodeId;
                                } else if (nodeId_2 == -1) {
                                    nodeId_2 = nodeId;
                                }
                            } else {
                                win.getGraph().getNodeMap().at(nodeId).setColor(GREEN);
                            }
                        }

                        if (nodeId_1 != -1 && nodeId_2 != -1) {
                            if (win.getGraph().checkIfEdgeExists(nodeId_1, nodeId_2) || win.getGraph().checkIfEdgeExists(nodeId_2, nodeId_1)) {
                                win.getGraph().removeEdge(nodeId_1, nodeId_2);
                            } else {
                                win.getGraph().addEdge(nodeId_1, nodeId_2);
                            }
                            win.getGraph().getNodeMap().at(nodeId_1).setColor(GREEN);
                            win.getGraph().getNodeMap().at(nodeId_2).setColor(GREEN);
                            nodeId_1 = -1;
                            nodeId_2 = -1;
                        }

                    } else {
                        win.addNode(Node(win.getGraph().assignNodeId(), pos.x, pos.y, NODE_RADIUS, NODE_PADDING, 1, GREEN));
                    }
                } else {
                    // TODO: Handle button functionality here
                }
            }
        }

        win.getWindow().clear();
        win.update();
        win.getWindow().display();
    }
}
