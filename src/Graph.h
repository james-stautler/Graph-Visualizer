
#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"
#include <vector>
#include <memory>
#include <set>
#include <queue>
#include <map>

class Graph {
private:
     std::vector<std::unique_ptr<Edge>> edges;
     std::map<int, Node> nodeMap;
     std::map<int, std::vector<int>> adjMap;
     int currId = 0;

public:
     Graph();

     std::map<int, Node>& getNodeMap();
     std::vector<std::unique_ptr<Edge>>& getEdges();
     std::map<int, std::vector<int>>& getAdjMap();

     void resetGraph(bool hardReset);

     int checkWithinNodeBoundary(int x, int y) const;
     int assignNodeId();
     bool addNode(const Node& node);
     bool removeNode(int nodeId);
     bool checkIfEdgeExists(int srcId, int dstId);
     bool addEdge(int srcId, int dstId, bool bidirectional, sf::Color color);
     bool addEdge(int srcId, int dstId, float weight, bool bidirectional, sf::Color color);
     bool removeEdge(int srcId, int dstId);

     bool TestBFS(int start, int end);
     bool TestDFS(int curr, int start, int end, std::set<int>& visited);
};

#endif //GRAPH_H
