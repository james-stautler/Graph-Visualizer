
#include "Node.h"

Node::Node(int id, int x, int y, int radius, int padding, float value, sf::Color color) {
    this->id = id;
    this->x = x;
    this->y = y;
    this->radius = radius;
    this->padding = padding;
    this->value = value;
    this->color = color;
}

int Node::getId() const {
    return this->id;
}

int Node::getX() const {
    return this->x;
}

int Node::getY() const {
    return this->y;
}

int Node::getRadius() const {
    return this->radius;
}

float Node::getValue() const {
    return this->value;
}

sf::Color Node::getColor() const {
    return this->color;
}

bool Node::withinBounds(int x, int y) const {
    return ((x >= this->x - this->radius - padding) &&
            (y >= this->y - this->radius - padding) &&
            (x <= this->x + this->radius + padding) &&
            (y <= this->y + this->radius + padding));
}


void Node::setX(int x) {
    this->x = x;
}

void Node::setY(int y) {
    this->y = y;
}

void Node::setRadius(int radius) {
    this->radius = radius;
}

void Node::setValue(float value) {
    this->value = value;
}

void Node::setColor(sf::Color color) {
    this->color = color;
}







