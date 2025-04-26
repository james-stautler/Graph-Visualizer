

#ifndef EDGE_H
#define EDGE_H

#include "Node.h"

class Edge {
private:
    int srcId;
    int dstId;
    float weight;
    bool bidirectional;

public:
    Edge() = default;
    Edge(int srcId, int dstId, bool bidirectional);
    Edge(int srcId, int dstId, float weight, bool bidirectional);
    bool operator==(const Edge &other) const;

    [[nodiscard]] int getSrc() const;
    [[nodiscard]] int getDst() const;
    [[nodiscard]] float getWeight() const;
    [[nodiscard]] bool isBidirectional() const;

    void setSource(int srcId);
    void setDestination(int dstId);
    void setWeight(float weight);
    void setBidirectional(bool bidirectional);
};

#endif //EDGE_H
