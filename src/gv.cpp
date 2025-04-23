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

    auto win = Window(WIDTH, HEIGHT, TITLE, FRAMERATE_LIMIT, font);

    while (win.getWindow().isOpen()) {

        while (const std::optional event = win.getWindow().pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                win.getWindow().close();
            }

            if (event->is<sf::Event::MouseButtonPressed>()) {

                sf::Vector2i pos = sf::Mouse::getPosition(win.getWindow());
                int nodeId = win.getGraph().checkWithinNodeBoundary(pos.x, pos.y);
                if (nodeId != -1) {
                    // TODO: Change node state
                } else {
                    win.addNode(Node(win.getGraph().assignNodeId(), pos.x, pos.y, NODE_RADIUS, NODE_PADDING, 1, sf::Color::Green));
                }
            }
        }

        win.getWindow().clear();
        win.update();
        win.getWindow().display();
    }
}
