
#include "Window.h"

Window::Window(const int width, const int height, const std::string &title, const int framerateLimit, sf::Font font) {
    this->width = width;
    this->height = height;
    this->title = title;
    this->framerateLimit = framerateLimit;
    this->font = font;

    const auto windowSize = sf::Vector2u(this->width, this->height);
    this->window = sf::RenderWindow(sf::VideoMode(windowSize), this->title);
    this->window.setFramerateLimit(this->framerateLimit);
}

sf::RenderWindow& Window::getWindow() {
    return this->window;
};

Graph& Window::getGraph() {
    return this->graph;
}

bool Window::addNode(const Node& node) {
    return this->graph.addNode(node);
}

void Window::drawGraph() {
    for (int i = 0; i < this->graph.getNodes().size(); i++) {
        Node node = this->graph.getNodes().at(i);
        sf::CircleShape circle(static_cast<float>(node.getRadius()));
        const auto pos = static_cast<sf::Vector2f>(sf::Vector2i(node.getX() - node.getRadius(), node.getY() - node.getRadius()));
        circle.setPosition(pos);
        circle.setFillColor(node.getColor());
        this->window.draw(circle);
    }
}


void Window::update() {
    this->drawGraph();
}


