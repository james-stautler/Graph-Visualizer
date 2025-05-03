
#include "Graph.h"


Graph::Graph() {
    this->nodeMap = std::map<int, Node>();
    this->edges = std::vector<std::unique_ptr<Edge>>();
    this->adjMap = std::map<int, std::vector<int>>();
}

void Graph::resetGraph(bool hardReset) {
    for (auto &pair: this->nodeMap) {
        pair.second.setColor(sf::Color::Red);
        if (hardReset) {
            pair.second.setPrev(-1);
        }
    }
    for (auto &edge: this->edges) {
        edge->setColor(sf::Color::White);
    }
}


std::map<int, Node>& Graph::getNodeMap() {
    return this->nodeMap;
}

std::vector<std::unique_ptr<Edge>>& Graph::getEdges() {
    return this->edges;
}

std::map<int, std::vector<int>>& Graph::getAdjMap() {
    return this->adjMap;
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
    this->adjMap.insert(std::pair<int, std::vector<int>>(node.getId(), std::vector<int>()));
    return true;
}

bool Graph::removeNode(int nodeId) {
    if (this->nodeMap.find(nodeId) == this->nodeMap.end()) {
        return false;
    }
    this->nodeMap.erase(nodeId);

    auto it = std::remove_if(this->edges.begin(), this->edges.end(), [nodeId](std::unique_ptr<Edge>& e) { return e->getSrc() == nodeId || e->getDst() == nodeId; });
    this->edges.erase(it, this->edges.end());

    for (auto &pair: this->adjMap) {
        for (int i = 0; i < pair.second.size(); i++) {
            if (pair.second[i] == nodeId) {
                pair.second.erase(pair.second.begin() + i);
            }
        }

    }
    this->adjMap.erase(nodeId);
    return true;
}

bool Graph::checkIfEdgeExists(int srcId, int dstId) {

    for (const auto& edge: this->edges) {
        if ((edge->getSrc() == srcId && edge->getDst() == dstId) ||
            (edge->getSrc() == dstId && edge->getDst() == srcId)) {
            return true;
        }
    }
    return false;
}


bool Graph::addEdge(int srcId, int dstId, bool bidirectional, sf::Color color) {

    for (const auto& edge: this->edges) {
        if ((edge->getSrc() == srcId && edge->getDst() == dstId) ||
            (edge->getSrc() == dstId && edge->getDst() == srcId)) {
            return false;
        }
    }

    if (bidirectional) {
        Edge edge = Edge(srcId, dstId, true, color);
        Edge edge_reverse = Edge(dstId, srcId, true, color);
        this->edges.push_back(std::make_unique<Edge>(edge));
        this->edges.push_back(std::make_unique<Edge>(edge_reverse));
        this->adjMap.at(srcId).push_back(dstId);
        this->adjMap.at(dstId).push_back(srcId);
    } else {
        Edge edge = Edge(srcId, dstId, false, color);
        this->edges.push_back(std::make_unique<Edge>(edge));
        this->adjMap.at(srcId).push_back(dstId);
    }

    return true;
}

bool Graph::addEdge(int srcId, int dstId, float weight, bool bidirectional, sf::Color color) {

    for (const auto& edge: this->edges) {
        if (edge->getSrc() == srcId && edge->getDst() == dstId) {
            return false;
        }
    }

    if (bidirectional) {
        Edge edge = Edge(srcId, dstId, weight, true, color);
        Edge edge_reverse = Edge(dstId, srcId, weight, true, color);
        this->edges.push_back(std::make_unique<Edge>(edge));
        this->edges.push_back(std::make_unique<Edge>(edge_reverse));
        this->adjMap.at(srcId).push_back(dstId);
        this->adjMap.at(dstId).push_back(srcId);
    } else {
        Edge edge = Edge(srcId, dstId, weight, false, color);
        this->edges.push_back(std::make_unique<Edge>(edge));
        this->adjMap.at(srcId).push_back(dstId);
    }

    return true;
}


bool Graph::removeEdge(int srcId, int dstId) {
    bool edgeRemoved = false;
    bool mapEntryRemoved = false;

    for (int i = 0; i < this->edges.size(); i++) {
        if (this->edges[i]->getSrc() == srcId && this->edges[i]->getDst() == dstId) {
            this->edges.erase(this->edges.begin() + i);
            edgeRemoved = true;
            break;
        }
    }

    for (int i = 0; i < this->edges.size(); i++) {
        if (this->edges[i]->getSrc() == dstId && this->edges[i]->getDst() == srcId) {
            this->edges.erase(this->edges.begin() + i);
            edgeRemoved = true;
            break;
        }
    }

    for (int i = 0; i < this->adjMap.at(srcId).size(); i++) {
        if (this->adjMap.at(srcId)[i] == dstId) {
            this->adjMap.at(srcId).erase(this->adjMap.at(srcId).begin() + i);
            mapEntryRemoved = true;
            break;
        }
    }

    for (int i = 0; i < this->adjMap.at(dstId).size(); i++) {
        if (this->adjMap.at(dstId)[i] == srcId) {
            this->adjMap.at(dstId).erase(this->adjMap.at(dstId).begin() + i);
            mapEntryRemoved = true;
            break;
        }
    }

    return edgeRemoved && mapEntryRemoved;
}

bool Graph::TestBFS(int start, int end) {
    std::queue<int> nodeQueue;
    std::set<int> visited;

    nodeQueue.push(start);
    while (!nodeQueue.empty()) {
        auto node = nodeQueue.front();
        nodeQueue.pop();
        if (visited.find(node) != visited.end()) {
            continue;
        }
        if (node == end) {
            return true;
        }
        visited.insert(node);
        if (node != start && node != end) {
            this->nodeMap.at(node).setColor(sf::Color::Green);
        }
        std::vector<int> neighbors = this->adjMap.at(node);
        for (int i = 0; i < neighbors.size(); i++) {
            for (auto &edge: this->edges) {
                if ((edge->getSrc() == node && edge->getDst() == neighbors[i]) ||
                    (edge->getSrc() == neighbors[i] && edge->getDst() == node)) {
                    edge->setColor(sf::Color::Red);
                    }
            }
            if (this->nodeMap.at(neighbors[i]).getPrev() == -1 && neighbors[i] != start) {
                this->nodeMap.at(neighbors[i]).setPrev(node);
            }
            nodeQueue.push(neighbors[i]);
            if (neighbors[i] != start && neighbors[i] != end) {
                this->nodeMap.at(neighbors[i]).setColor(sf::Color { 199, 119, 0 });
            }
        }
    }

    return false;
}

bool Graph::TestDFS(int curr, int start, int end, std::set<int>& visited) {

    bool res = false;
    if (curr == end) {
        return true;
    }

    if (visited.find(curr) != visited.end()) {
        return false;
    }
    visited.insert(curr);

    std::vector<int> neighbors = this->adjMap.at(curr);
    for (int i = 0; i < neighbors.size(); i++) {
        for (auto &edge: this->edges) {
            if ((edge->getSrc() == curr && edge->getDst() == neighbors[i]) ||
                (edge->getSrc() == neighbors[i] && edge->getDst() == curr)) {
                edge->setColor(sf::Color::Red);
                }
        }
        if (this->nodeMap.at(neighbors[i]).getPrev() == -1 && neighbors[i] != start) {
            this->nodeMap.at(neighbors[i]).setPrev(curr);
        }
        res |= this->TestDFS(neighbors[i], start, end, visited);
        if (res) {
            break;
        }
        if (neighbors[i] != start && neighbors[i] != end) {
            this->nodeMap.at(neighbors[i]).setColor(sf::Color { 199, 119, 0 });
        }
    }
    this->nodeMap.at(curr).setColor(sf::Color::Green);
    return res;
}

