
#include "Edge.h"

Edge::Edge(int srcId, int dstId, const bool bidirectional) {
    this->srcId = srcId;
    this->dstId = dstId;
    this->weight = 1;
    this->bidirectional = bidirectional;
}

Edge::Edge(int srcId, int dstId, const float weight, const bool bidirectional) {
    this->srcId = srcId;
    this->dstId = dstId;
    this->weight = weight;
    this->bidirectional = bidirectional;
}

bool Edge::operator==(const Edge& other) const {
    return this->srcId == other.getSrc() && this->dstId == other.getDst();
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




