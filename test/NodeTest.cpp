
#include <gtest/gtest.h>
#include "../src/Node.cpp"
#include "SFML/System/Vector2.hpp"

TEST(Node_Tests, Node_Creation_Tests) {
    Node node = Node(0, 0, 0, 10, 5, 1, sf::Color::White);

    ASSERT_EQ(node.getId(), 0);
    ASSERT_EQ(node.getX(), 0);
    ASSERT_EQ(node.getY(), 0);
    ASSERT_EQ(node.getRadius(), 10);
    ASSERT_EQ(node.getValue(), 1);
    ASSERT_EQ(node.getColor(), sf::Color::White);

    node.setX(10);
    node.setY(10);
    node.setRadius(50);
    node.setValue(100);
    node.setColor(sf::Color::Red);

    ASSERT_EQ(node.getX(), 10);
    ASSERT_EQ(node.getY(), 10);
    ASSERT_EQ(node.getRadius(), 50);
    ASSERT_EQ(node.getValue(), 100);
    ASSERT_EQ(node.getColor(), sf::Color::Red);

}

TEST(Node_Tests, Node_Bounds_Tests) {
    Node node = Node(0, 20, 20, 10, 10, 1, sf::Color::White);

    int outsideX = 100;
    int outsideY = 100;

    ASSERT_EQ(node.withinBounds(outsideX,outsideY), false);

    int withinX = 27;
    int withinY = 27;

    ASSERT_EQ(node.withinBounds(withinX,withinY), true);
    ASSERT_EQ(node.strictlyWithinBounds(outsideX,outsideY), false);

    int strictlyWithinX = 20;
    int strictlyWithinY = 20;

    ASSERT_EQ(node.withinBounds(strictlyWithinX, strictlyWithinY), true);
    ASSERT_EQ(node.strictlyWithinBounds(strictlyWithinX,strictlyWithinY), true);

}
