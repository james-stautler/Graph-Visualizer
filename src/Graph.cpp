
#include "Graph.h"

Graph::Graph() {
    this->nodeMap = std::map<int, Node>();
    this->edges = std::vector<Edge>();
}

std::map<int, Node>& Graph::getNodeMap() {
    return this->nodeMap;
}

std::vector<Edge>& Graph::getEdges() {
    return this->edges;
}

int Graph::checkWithinNodeBoundary(int x, int y) const {
    for (const auto& pair: this->nodeMap) {
        Node node = pair.second;
        if (node.withinBounds(x, y)) {
            return node.getId();
        }
    }
    return -1;
}


int Graph::assignNodeId() {
    const int id = this->currId;
    this->currId++;
    return id;
}


bool Graph::addNode(const Node& node) {
    if (this->nodeMap.find(node.getId()) != this->nodeMap.end()) {
        return false;
    }
    this->nodeMap.insert(std::pair<int, Node>(node.getId(), node));
    return true;
}

bool Graph::removeNode(const Node& node) {
    if (this->nodeMap.find(node.getId()) == this->nodeMap.end()) {
        return false;
    }
    for (const auto& pair: this->nodeMap) {
        if (pair.second.getId() == node.getId()) {
            this->nodeMap.erase(node.getId());
            break;
        }
    }
    return true;
}
