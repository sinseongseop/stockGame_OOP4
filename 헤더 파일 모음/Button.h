#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

class Button
{
private:
    string text, name;
    float x, y, width, height;
    sf::RectangleShape buttonRect;
    sf::FloatRect newWindowArea;

public:
    Button();
    Button(float x, float y, float width, float height);
    string getName();
    void setColor(char color);
    void setName(string name);
    bool clickButton(sf::Vector2f mousePosition);
    sf::RectangleShape getButton();
};

#endif
