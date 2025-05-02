
#include "Edge.h"

Edge::Edge(int srcId, int dstId, const bool bidirectional, sf::Color color) {
    this->srcId = srcId;
    this->dstId = dstId;
    this->weight = 1;
    this->bidirectional = bidirectional;
    this->color = color;
}

Edge::Edge(int srcId, int dstId, const float weight, const bool bidirectional, sf::Color color) {
    this->srcId = srcId;
    this->dstId = dstId;
    this->weight = weight;
    this->bidirectional = bidirectional;
    this->color = color;
}

bool Edge::operator==(const Edge& other) const {
    return this->srcId == other.getSrc() &&
            this->dstId == other.getDst() &&
            this->weight == other.getWeight() &&
            this->bidirectional == other.isBidirectional();
}

int Edge::getSrc() const {
    return this->srcId;
}

int Edge::getDst() const {
    return this->dstId;
}

float Edge::getWeight() const {
    return this->weight;
}

bool Edge::isBidirectional() const {
    return this->bidirectional;
}

sf::Color Edge::getColor() const {
    return this->color;
}

void Edge::setSource(int srcId) {
    this->srcId = srcId;
}

void Edge::setDestination(int dstId) {
    this->dstId = dstId;
}

void Edge::setWeight(float weight) {
    this->weight = weight;
}

void Edge::setBidirectional(bool bidirectional) {
    this->bidirectional = bidirectional;
}

void Edge::setColor(sf::Color color) {
    this->color = color;
}




