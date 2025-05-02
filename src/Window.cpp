
#include "Window.h"

#include <iostream>
#include <stack>
#include <thread>

Window::Window() {
    this->graph = Graph();
}

Window::Window(const int width, const int height, const std::string &title, const int framerateLimit, sf::Font font) {
    this->width = width;
    this->height = height;
    this->title = title;
    this->framerateLimit = framerateLimit;
    this->font = font;
    this->graph = Graph();
    this->buttons = std::vector<std::reference_wrapper<Button>>();

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

std::vector<std::reference_wrapper<Button>> Window::getButtons() {
    return this->buttons;
}

void Window::addButton(std::reference_wrapper<Button> button) {
    this->buttons.push_back(button);
}

void Window::setAllButtonsInactive() {
    for (auto& button : this->buttons) {
        if (button.get().isActive()) {
            button.get().flipActiveState();
        }
    }
}

sf::Color Window::getNodeColor(int nodeId) {
    return this->graph.getNodeMap().at(nodeId).getColor();
}

void Window::setNodeColor(int nodeId, sf::Color color) {
    this->graph.getNodeMap().at(nodeId).setColor(color);
}


void Window::edgeHandler(int srcId, int dstId, bool bidirectional, sf::Color color) {
    if (this->graph.checkIfEdgeExists(srcId, dstId) || this->graph.checkIfEdgeExists(dstId, srcId)) {
        this->graph.removeEdge(srcId, dstId);
    } else {
        this->graph.addEdge(srcId, dstId, bidirectional, color);
    }
}

void Window::generateRandomGraph(int nodes, int edges, int nodeRadius, int padding, sf::Color nodeColor, bool weighted) {
    srand(time(nullptr));
    this->graph = Graph();
    for (int i = 0; i < nodes; i++) {
        int randX = rand() % (int(this->width * 0.8 - 2 * padding)) + padding;
        int randY = rand() % (int(this->height * 0.9 - 2 * padding)) + padding;
        while (this->graph.checkWithinNodeBoundary(randX, randY) != -1) {
            randX = rand() % (int(this->width * 0.8));
            randY = rand() % (int(this->height * 0.9));
        }
        float weight = 1;
        if (weighted) {
            // Random weight here
        }
        Node node = Node(this->graph.assignNodeId(), randX, randY, nodeRadius, padding, weight, nodeColor);
        this->graph.addNode(node);
    }

    for (int i = 0; i < edges; i++) {
        int randSrc = rand() % nodes;
        int randDst = rand() % nodes;
        while (this->graph.checkIfEdgeExists(randSrc, randDst)) {
            randSrc = rand() % nodes;
            randDst = rand() % nodes;
        }
        this->graph.addEdge(randSrc, randDst, true, sf::Color::White);
    }
}


void Window::drawButton(Button& button) {
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

void Window::addText(std::reference_wrapper<sf::Text> text) {
    this->texts.push_back(text);
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
        sf::Text text = sf::Text(this->font);
        text.setCharacterSize(10);
        text.setString(std::to_string(edge->getWeight()).substr(0, std::to_string(edge->getWeight()).find(".") + 2 + 1));
        text.setFillColor(sf::Color::Blue);

        sf::VertexArray line(sf::PrimitiveType::Lines, 2);
        Node src = this->graph.getNodeMap().at(edge->getSrc());
        Node dst = this->graph.getNodeMap().at(edge->getDst());

        line[0].position = sf::Vector2f(src.getX(), src.getY());
        line[1].position = sf::Vector2f(dst.getX(), dst.getY());

        line[0].color = edge->getColor();
        line[1].color = edge->getColor();

        sf::Vector2f textPosition = sf::Vector2f((src.getX() + dst.getX()) / 2, (src.getY() + dst.getY()) / 2);
        text.setPosition(textPosition);

        this->window.draw(line);

        if (edge->getWeight() != 1) {
            this->window.draw(text);
        }

    }
}


void Window::update() {
    this->window.clear();
    for (auto &button: this->buttons) {
        this->drawButton(button);
    }
    for (auto &text: this->texts) {
        this->window.draw(text);
    }
    this->drawGraph();
}

void Window::resetGraph(bool hardReset) {
    for (auto &pair: this->graph.getNodeMap()) {
        pair.second.setColor(sf::Color::Red);
        if (hardReset) {
            pair.second.setPrev(-1);
        }
    }
    for (auto &edge: this->graph.getEdges()) {
        edge->setColor(sf::Color::White);
    }
}

void Window::clearGraph() {
    this->graph = Graph();
}

void Window::redOutGraph() {
    for (auto &pair: this->graph.getNodeMap()) {
        pair.second.setColor(sf::Color::Red);
    }
    for (auto &edge: this->graph.getEdges()) {
        edge->setColor(sf::Color::Red);
    }
}

void Window::drawPath(int startId, int endId) {
    int nodeId = endId;
    while (this->graph.getNodeMap().at(nodeId).getPrev() != -1) {
        this->graph.getNodeMap().at(nodeId).setColor(sf::Color::Green);
        for (auto &edge: this->graph.getEdges()) {
            if ((edge->getSrc() == nodeId && edge->getDst() == this->graph.getNodeMap().at(nodeId).getPrev()) ||
                (edge->getSrc() == this->graph.getNodeMap().at(nodeId).getPrev() && edge->getDst() == nodeId)) {
                edge->setColor(sf::Color::Green);
            }
        }
        nodeId = this->graph.getNodeMap().at(nodeId).getPrev();
    }
    this->graph.getNodeMap().at(startId).setColor(sf::Color { 255, 105, 180 });
    this->graph.getNodeMap().at(endId).setColor(sf::Color { 255, 105, 180 });
}

// ALGORITHMS

bool Window::BFS(int start, int end, int speed, bool testing) {
    std::queue<int> nodeQueue;
    std::set<int> visited;

    nodeQueue.push(start);
    while (!nodeQueue.empty()) {
        auto node = nodeQueue.front();
        nodeQueue.pop();
        if (visited.find(node) != visited.end()) {
            continue;
        }
        if (node == end) {
            return true;
        }
        visited.insert(node);
        if (node != start && node != end) {
            this->setNodeColor(node, sf::Color::Green);
        }
        std::vector<int> neighbors = this->graph.getAdjMap().at(node);
        for (int i = 0; i < neighbors.size(); i++) {
            for (auto &edge: this->graph.getEdges()) {
                if ((edge->getSrc() == node && edge->getDst() == neighbors[i]) ||
                    (edge->getSrc() == neighbors[i] && edge->getDst() == node)) {
                    edge->setColor(sf::Color::Red);
                    }
            }
            if (this->graph.getNodeMap().at(neighbors[i]).getPrev() == -1 && neighbors[i] != start) {
                this->graph.getNodeMap().at(neighbors[i]).setPrev(node);
            }
            nodeQueue.push(neighbors[i]);
            if (neighbors[i] != start && neighbors[i] != end) {
                this->setNodeColor(neighbors[i], sf::Color { 199, 119, 0 });
            }
        }
        if (testing) {
            continue;
        }
        this->window.clear();
        this->update();
        this->getWindow().display();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / speed));
    }

    return false;
}

bool Window::DFS(int curr, int start, int end, int speed, std::set<int>& visited, bool testing) {

    if (!testing) {
        if (curr != start && curr != end) {
            this->setNodeColor(curr, sf::Color { 199, 119, 0 });
        }
        this->window.clear();
        this->update();
        this->getWindow().display();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / speed));
    }

    bool res = false;
    if (curr == end) {
        return true;
    }

    if (visited.find(curr) != visited.end()) {
        return false;
    }
    visited.insert(curr);

    std::vector<int> neighbors = this->graph.getAdjMap().at(curr);
    for (int i = 0; i < neighbors.size(); i++) {
        for (auto &edge: this->graph.getEdges()) {
            if ((edge->getSrc() == curr && edge->getDst() == neighbors[i]) ||
                (edge->getSrc() == neighbors[i] && edge->getDst() == curr)) {
                edge->setColor(sf::Color::Red);
                }
        }
        if (this->graph.getNodeMap().at(neighbors[i]).getPrev() == -1 && neighbors[i] != start) {
            this->graph.getNodeMap().at(neighbors[i]).setPrev(curr);
        }
        res |= this->DFS(neighbors[i], start, end, speed, visited, testing);
        if (res) {
            break;
        }
        if (neighbors[i] != start && neighbors[i] != end) {
            this->setNodeColor(neighbors[i], sf::Color { 199, 119, 0 });
        }
    }
    this->setNodeColor(curr, sf::Color::Green);
    return res;
}



