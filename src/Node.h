
#ifndef NODE_H
#define NODE_H

#include <SFML/Graphics/Color.hpp>

class Node {
private:
    int id;
    int x;
    int y;
    int radius;
    int padding;
    float value;
    sf::Color color;

public:
    Node() = default;
    Node(int id, int x, int y, int radius, int padding, float value, sf::Color color);

    [[nodiscard]] int getId() const;
    [[nodiscard]] int getX() const;
    [[nodiscard]] int getY() const;
    [[nodiscard]] int getRadius() const;
    [[nodiscard]] float getValue() const;
    [[nodiscard]] sf::Color getColor() const;

    bool withinBounds(int x, int y) const;
    bool strictlyWithinBounds(int x, int y) const;

    void setX(int x);
    void setY(int y);
    void setRadius(int radius);
    void setValue(float value);
    void setColor(sf::Color color);

};

#endif //NODE_H
