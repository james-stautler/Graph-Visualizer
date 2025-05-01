
#ifndef BUTTON_H
#define BUTTON_H
#include <string>

#include "SFML/Graphics/Image.hpp"
#include "SFML/System/Vector2.hpp"

class Button {
private:
    int x;
    int y;
    int width;
    int height;
    bool active;
    sf::Color activeColor;
    sf::Color inactiveColor;
    std::string text;

public:
    Button(int x, int y, int width, int height, bool active, sf::Color activeColor, sf::Color inactiveColor, const std::string& text);

    void flipActiveState();

    int getX();
    int getY();
    int getWidth();
    int getHeight();
    std::string getText();
    sf::Color getCurrentColor();
    bool isActive();
    bool isWithinBounds(int x, int y);


};
#endif //BUTTON_H
