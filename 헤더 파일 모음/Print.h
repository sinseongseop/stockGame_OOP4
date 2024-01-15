#ifndef PRINT_H
#define PRINT_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

class Print
{
private:
    float x, y, number, size;
    string message, name;
    sf::Font font;
    sf::Text text;
public:
    Print();
    Print(float x, float y, float number, float size, int type, string name);
    Print(float x, float y, string message, float size);
    void changeNum(int number);
    float getX();
    float getY();
    string getMessage();
    float getSize();
    string getName();
    void setNumber(int number);
};

#endif