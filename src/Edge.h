

#ifndef EDGE_H
#define EDGE_H

#include "Node.h"

class Edge {
private:
    int srcId;
    int dstId;
    float weight;
    bool bidirectional;
    sf::Color color;

public:
    Edge() = default;
    Edge(int srcId, int dstId, bool bidirectional, sf::Color color);
    Edge(int srcId, int dstId, float weight, bool bidirectional, sf::Color color);
    bool operator==(const Edge &other) const;

    [[nodiscard]] int getSrc() const;
    [[nodiscard]] int getDst() const;
    [[nodiscard]] float getWeight() const;
    [[nodiscard]] bool isBidirectional() const;
    [[nodiscard]] sf::Color getColor() const;

    void setSource(int srcId);
    void setDestination(int dstId);
    void setWeight(float weight);
    void setBidirectional(bool bidirectional);
    void setColor(sf::Color color);
};

#endif //EDGE_H
