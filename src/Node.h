
#ifndef NODE_H
#define NODE_H

#include <SFML/Graphics/Color.hpp>

class Node {
private:
    int id;
    float x;
    float y;
    float value;
    sf::Color color;

public:
    Node(const int id, const float x, const float y, const float value, const sf::Color color);

    [[nodiscard]] int getId() const;
    [[nodiscard]] float getX() const;
    [[nodiscard]] float getY() const;
    [[nodiscard]] float getValue() const;
    [[nodiscard]] sf::Color getColor() const;

    void setX(const float x);
    void setY(const float y);
    void setValue(const float value);
    void setColor(const sf::Color color);

};

#endif //NODE_H
