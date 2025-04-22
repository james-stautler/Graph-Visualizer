#include "Window.h"

int main()
{
    constexpr int WIDTH = 1920;
    constexpr int HEIGHT = 1080;
    constexpr int FRAMERATE_LIMIT = 60;
    const std::string TITLE = "Graph Visualizer";

    auto win = Window(WIDTH, HEIGHT, TITLE, FRAMERATE_LIMIT);

    while (win.getWindow().isOpen())
    {
        while (const std::optional event = win.getWindow().pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                win.getWindow().close();
            }
        }

        win.getWindow().clear();
        win.getWindow().display();
    }
}
