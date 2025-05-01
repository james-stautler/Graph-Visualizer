
#include <gtest/gtest.h>
#include "../src/Button.cpp"

TEST(Button_Tests, Button_Creation_Tests) {

    Button button = Button(10, 10, 200, 100, false, sf::Color::Red, sf::Color::Blue, "test button");

    ASSERT_EQ(button.getX(), 10);
    ASSERT_EQ(button.getY(), 10);
    ASSERT_EQ(button.getWidth(), 200);
    ASSERT_EQ(button.getHeight(), 100);
    ASSERT_FALSE(button.isActive());
    ASSERT_EQ(button.getCurrentColor(), sf::Color::Blue);

    button.flipActiveState();
    ASSERT_TRUE(button.isActive());
    ASSERT_EQ(button.getCurrentColor(), sf::Color::Red);

    int x = 50;
    int y = 50;
    ASSERT_TRUE(button.isWithinBounds(x, y));

    x = 201;
    y = 111;
    ASSERT_FALSE(button.isWithinBounds(x, y));

}