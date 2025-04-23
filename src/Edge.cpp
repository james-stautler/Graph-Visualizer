
#include "Edge.h"

Edge::Edge(const Node& src, const Node& dst, const bool bidirectional) {
    this->src = src;
    this->dst = dst;
    this->weight = 1;
    this->bidirectional = bidirectional;
}

Edge::Edge(const Node &src, const Node &dst, const float weight, const bool bidirectional) {
    this->src = src;
    this->dst = dst;
    this->weight = weight;
    this->bidirectional = bidirectional;
}

Node& Edge::getSrc() {
    return this->src;
}

Node& Edge::getDst() {
    return this->dst;
}

float Edge::getWeight() const {
    return this->weight;
}

bool Edge::isBidirectional() const {
    return this->bidirectional;
}

void Edge::setSource(const Node &src) {
    this->src = src;
}

void Edge::setDestination(const Node &dst) {
    this->dst = dst;
}

void Edge::setWeight(float weight) {
    this->weight = weight;
}

void Edge::setBidirectional(bool bidirectional) {
    this->bidirectional = bidirectional;
}




