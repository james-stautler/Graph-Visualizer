
#include "Node.h"

Node::Node(int id, int x, int y, int radius, int padding, float value, sf::Color color) {
    this->id = id;
    this->x = x;
    this->y = y;
    this->radius = radius;
    this->padding = padding;
    this->value = value;
    this->color = color;
    this->prev = -1;
}

bool Node::operator==(const Node &other) const {
    return this->id == other.id &&
            this->x == other.x &&
            this->y == other.y &&
            this->radius == other.radius &&
            this->padding == other.padding &&
            this->value == other.value &&
            this->color == other.color;
}

bool Node::operator!=(const Node &other) const {
    return this->id != other.id ||
            this->x != other.x ||
            this->y != other.y ||
            this->radius != other.radius ||
            this->padding != other.padding ||
            this->value != other.value ||
            this->color != other.color;
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

int Node::getPrev() const {
    return this->prev;
}

bool Node::withinBounds(int x, int y) const {
    return ((x >= this->x - this->radius - padding) &&
            (y >= this->y - this->radius - padding) &&
            (x <= this->x + this->radius + padding) &&
            (y <= this->y + this->radius + padding));
}

bool Node::strictlyWithinBounds(int x, int y) const {
    return ((x >= this->x - this->radius) &&
            (y >= this->y - this->radius) &&
            (x <= this->x + this->radius) &&
            (y <= this->y + this->radius));
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

void Node::setPrev(int prev) {
    this->prev = prev;
}







