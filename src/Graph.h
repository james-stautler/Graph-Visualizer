
#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"
#include <vector>
#include <set>
#include <map>

class Graph {
private:
     std::vector<Edge> edges;
     std::vector<Node> nodes;
     std::map<int, Node> nodeMap;
     std::set<int> nodeIds;
     int currId = 0;

public:
     Graph();

     std::vector<Node> getNodes();
     std::map<int, Node> getNodeMap();
     std::vector<Edge> getEdges();

     int checkWithinNodeBoundary(int x, int y) const;

     int assignNodeId();
     bool addNode(const Node& node);
     bool removeNode(const Node& node);
     bool removeEdge(const Node& src, const Node& dst);
     bool addEdge(const Node& src, const Node& dst);
     bool addEdge(const Node& src, const Node& dst, float weight);
};

#endif //GRAPH_H
