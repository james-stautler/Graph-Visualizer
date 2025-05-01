
#include "Graph.h"

#include <algorithm>

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

bool Graph::removeNode(int nodeId) {
    if (this->nodeMap.find(nodeId) == this->nodeMap.end()) {
        return false;
    }
    this->nodeMap.erase(nodeId);

    auto it = std::remove_if(this->edges.begin(), this->edges.end(), [nodeId](const Edge& e) { return e.getSrc() == nodeId || e.getDst() == nodeId; });
    this->edges.erase(it, this->edges.end());
    return true;
}

bool Graph::checkIfEdgeExists(int srcId, int dstId) {

    for (const auto& edge: this->edges) {
        if ((edge.getSrc() == srcId && edge.getDst() == dstId) || (edge.getSrc() == dstId && edge.getDst() == srcId)) {
            return true;
        }
    }
    return false;
}


bool Graph::addEdge(int srcId, int dstId, bool bidirectional) {

    for (const auto& edge: this->edges) {
        if ((edge.getSrc() == srcId && edge.getDst() == dstId) ||
            (edge.getSrc() == dstId && edge.getDst() == srcId)) {
            return false;
        }
    }

    if (bidirectional) {
        Edge edge = Edge(srcId, dstId, true);
        Edge edge_reverse = Edge(dstId, srcId, true);
        this->edges.push_back(edge);
        this->edges.push_back(edge_reverse);
    } else {
        Edge edge = Edge(srcId, dstId, false);
        this->edges.push_back(edge);
    }

    return true;
}

bool Graph::addEdge(int srcId, int dstId, float weight, bool bidirectional) {

    for (const auto& edge: this->edges) {
        if (edge.getSrc() == srcId && edge.getDst() == dstId) {
            return false;
        }
    }

    if (bidirectional) {
        Edge edge = Edge(srcId, dstId, weight, true);
        Edge edge_reverse = Edge(dstId, srcId, weight, true);
        this->edges.push_back(edge);
        this->edges.push_back(edge_reverse);
    } else {
        Edge edge = Edge(srcId, dstId, weight, false);
        this->edges.push_back(edge);
    }

    return true;
}


bool Graph::removeEdge(int srcId, int dstId) {
    bool removed = false;
    for (int i = 0; i < this->edges.size(); i++) {
        if (this->edges[i].getSrc() == srcId && this->edges[i].getDst() == dstId) {
            this->edges.erase(this->edges.begin() + i);
            removed = true;
            break;
        }
    }

    for (int i = 0; i < this->edges.size(); i++) {
        if (this->edges[i].getSrc() == dstId && this->edges[i].getDst() == srcId) {
            this->edges.erase(this->edges.begin() + i);
            removed = true;
            break;
        }
    }
    return removed;
}

