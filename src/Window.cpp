
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

bool Window::removeNode(int nodeId) {
    return this->graph.removeNode(nodeId);
}


sf::Color Window::getNodeColor(int nodeId) {
    return this->graph.getNodeMap().at(nodeId).getColor();
}

void Window::setNodeColor(int nodeId, sf::Color color) {
    this->graph.getNodeMap().at(nodeId).setColor(color);
}


void Window::edgeHandler(int srcId, int dstId, bool bidirectional) {
    if (this->graph.checkIfEdgeExists(srcId, dstId) || this->graph.checkIfEdgeExists(dstId, srcId)) {
        this->graph.removeEdge(srcId, dstId);
    } else {
        this->graph.addEdge(srcId, dstId, bidirectional);
    }
    this->setNodeColor(srcId, sf::Color::Green);
    this->setNodeColor(dstId, sf::Color::Green);
}

void Window::drawButton(Button button) {
    sf::RectangleShape buttonShape(sf::Vector2f(static_cast<float>(button.getWidth()), static_cast<float>(button.getHeight())));
    const auto pos = static_cast<sf::Vector2f>(sf::Vector2i(button.getX(), button.getY()));
    buttonShape.setPosition(pos);
    buttonShape.setFillColor(button.getCurrentColor());

    auto text = sf::Text(this->font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    text.setString(button.getText());

    sf::FloatRect textBounds = text.getLocalBounds();
    float textOriginX = textBounds.position.x + textBounds.size.x / 2.0f;
    float textOriginY = textBounds.position.y + textBounds.size.y / 2.0f;
    text.setOrigin(sf::Vector2f(textOriginX, textOriginY));

    float buttonCenterX = button.getX() + button.getWidth() / 2.0f;
    float buttonCenterY = button.getY() + button.getHeight() / 2.0f;
    text.setPosition(sf::Vector2f(buttonCenterX, buttonCenterY));

    this->window.draw(buttonShape);
    this->window.draw(text);
}


void Window::drawGraph() {
    for (const auto& pair: this->graph.getNodeMap()) {
        Node node = pair.second;
        sf::CircleShape circle(static_cast<float>(node.getRadius()));
        const auto pos = static_cast<sf::Vector2f>(sf::Vector2i(node.getX() - node.getRadius(), node.getY() - node.getRadius()));
        circle.setPosition(pos);
        circle.setFillColor(node.getColor());
        this->window.draw(circle);
    }

    for (const auto& edge: this->graph.getEdges()) {
        sf::VertexArray line(sf::PrimitiveType::Lines, 2);
        Node src = this->graph.getNodeMap().at(edge.getSrc());
        Node dst = this->graph.getNodeMap().at(edge.getDst());

        line[0].position = sf::Vector2f(src.getX(), src.getY());
        line[1].position = sf::Vector2f(dst.getX(), dst.getY());

        line[0].color = sf::Color::White;
        line[1].color = sf::Color::White;

        this->window.draw(line);
    }
}


void Window::update() {
    this->drawGraph();
}


