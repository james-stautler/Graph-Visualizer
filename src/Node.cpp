
#include "Node.h"

Node::Node(const int id, const float x, const float y, const float radius, const float value, const sf::Color color) {
    this->id = id;
    this->x = x;
    this->y = y;
    this->radius = radius;
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

float Node::getRadius() const {
    return this->radius;
}

float Node::getValue() const {
    return this->value;
}

sf::Color Node::getColor() const {
    return this->color;
}

void Node::setX(float x) {
    this->x = x;
}

void Node::setY(float y) {
    this->y = y;
}

void Node::setRadius(float radius) {
    this->radius = radius;
}

void Node::setValue(float value) {
    this->value = value;
}

void Node::setColor(sf::Color color) {
    this->color = color;
}







