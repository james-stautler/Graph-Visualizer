
#include "Node.h"

Node::Node(const int id, const float x, const float y, const float value, const sf::Color color) {
    this->id = id;
    this->x = x;
    this->y = y;
    this->value = value;
    this->color = color;
}

int Node::getId() const {
    return this->id;
}

float Node::getX() const {
    return this->x;
}

float Node::getY() const {
    return this->y;
}

float Node::getValue() const {
    return this->value;
}

sf::Color Node::getColor() const {
    return this->color;
}

void Node::setX(const float x) {
    this->x = x;
}

void Node::setY(const float y) {
    this->y = y;
}

void Node::setValue(const float value) {
    this->value = value;
}

void Node::setColor(const sf::Color color) {
    this->color = color;
}







