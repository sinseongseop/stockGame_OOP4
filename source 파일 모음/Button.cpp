#include <iostream>
#include <string>
#include "Button.h"
#include <SFML/Graphics.hpp>

Button::Button() {}
Button::Button(float x, float y, float width, float height) {
    // ���ο� â�� ���� ���� ���� ����
    newWindowArea.left = x;
    newWindowArea.top = y;
    newWindowArea.width = width;
    newWindowArea.height = height;

    // ��ư ����
    buttonRect.setSize(sf::Vector2f(width, height));

    // ��ư ��ġ ����
    buttonRect.setPosition(x, y);
}
string Button::getName()
{
    return this->name;
}
void Button::setColor(char color) {
    if (color == 'p') {
        buttonRect.setFillColor(sf::Color::Magenta);
    }
    else if (color == 'g') {
        buttonRect.setFillColor(sf::Color::Green);
    }
    else if (color == 'y') {
        buttonRect.setFillColor(sf::Color::Yellow);
    }
    else if (color == 'r') {
        buttonRect.setFillColor(sf::Color::Red);
    }
    else if (color == 'w') {
        buttonRect.setFillColor(sf::Color::White);
    }
    else if (color == 'b') {
        buttonRect.setFillColor(sf::Color::Black);
    }
    else if (color == 'B') {
        buttonRect.setFillColor(sf::Color::Blue);
    }
    else if (color == 'c') {
        buttonRect.setFillColor(sf::Color::Cyan);
    }
}
void Button::setName(string name)
{
    this->name = name;
}
bool Button::clickButton(sf::Vector2f mousePosition) {
    if (newWindowArea.contains(mousePosition)) return true;
    else return false;
}
sf::RectangleShape Button::getButton() {
    return this->buttonRect;
}

