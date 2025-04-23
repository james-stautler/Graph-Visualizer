
#ifndef NODE_H
#define NODE_H

#include <SFML/Graphics/Color.hpp>

class Node {
private:
    int id;
    float x;
    float y;
    float radius;
    float value;
    sf::Color color;

public:
    Node() = default;
    Node(int id, float x, float y, float radius, float value, sf::Color color);

    [[nodiscard]] int getId() const;
    [[nodiscard]] float getX() const;
    [[nodiscard]] float getY() const;
    [[nodiscard]] float getRadius() const;
    [[nodiscard]] float getValue() const;
    [[nodiscard]] sf::Color getColor() const;

    void setX(float x);
    void setY(float y);
    void setRadius(float radius);
    void setValue(float value);
    void setColor(sf::Color color);

};

#endif //NODE_H
