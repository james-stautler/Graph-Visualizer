

#ifndef EDGE_H
#define EDGE_H

#include "Node.h"

class Edge {
private:
    Node src;
    Node dst;
    float weight;
    bool bidirectional;

public:
    Edge() = default;
    Edge(const Node& src, const Node& dst, bool bidirectional);
    Edge(const Node& src, const Node& dst, float weight, bool bidirectional);

    [[nodiscard]] Node& getSrc();
    [[nodiscard]] Node& getDst();
    [[nodiscard]] float getWeight() const;
    [[nodiscard]] bool isBidirectional() const;

    void setSource(const Node& src);
    void setDestination(const Node& dst);
    void setWeight(float weight);
    void setBidirectional(bool bidirectional);
};

#endif //EDGE_H
