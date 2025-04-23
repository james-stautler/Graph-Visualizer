
#include "Graph.h"

Graph::Graph() {
    this->nodes = std::vector<Node>();
    this->nodeMap = std::map<int, Node>();
    this->edges = std::vector<Edge>();
    this->nodeIds = std::set<int>();
}

std::vector<Node> Graph::getNodes() {
    return this->nodes;
}

std::map<int, Node> Graph::getNodeMap() {
    return this->nodeMap;
}

std::vector<Edge> Graph::getEdges() {
    return this->edges;
}

int Graph::checkWithinNodeBoundary(int x, int y) const {
    for (int i = 0; i < this->nodes.size(); i++) {
        Node node = this->nodes[i];
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
    if (this->nodeIds.find(node.getId()) != this->nodeIds.end()) {
        return false;
    }
    this->nodes.push_back(node);
    this->nodeMap.insert(std::pair<int, Node>(node.getId(), node));
    this->nodeIds.insert(node.getId());
    return true;
}

bool Graph::removeNode(const Node& node) {
    if (this->nodeIds.find(node.getId()) == this->nodeIds.end()) {
        return false;
    }
    for (int i = 0; i < this->nodes.size(); i++) {
        if (this->nodes.at(i).getId() == node.getId()) {
            this->nodes.erase(this->nodes.begin() + i);
            this->nodeMap.erase(node.getId());
            break;
        }
    }
    return true;
}
