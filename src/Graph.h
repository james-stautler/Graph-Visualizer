
#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"
#include <vector>
#include <set>
#include <map>

class Graph {
private:
     std::vector<Edge> edges;
     std::map<int, Node> nodeMap;
     int currId = 0;

public:
     Graph();

     std::map<int, Node>& getNodeMap();
     std::vector<Edge>& getEdges();

     int checkWithinNodeBoundary(int x, int y) const;
     int assignNodeId();
     bool addNode(const Node& node);
     bool removeNode(int nodeId);
     bool checkIfEdgeExists(int srcId, int dstId);
     bool addEdge(int srcId, int dstId, bool bidirectional);
     bool addEdge(int srcId, int dstId, float weight, bool bidirectional);
     bool removeEdge(int srcId, int dstId);
};

#endif //GRAPH_H
