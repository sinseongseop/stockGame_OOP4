#include <iostream>
#include <string>
#include "Print.h"
#include <SFML/Graphics.hpp>

// int, float enum
enum numberType
{
    INT,
    FLOAT,
};

Print::Print() {}

Print::Print(float x, float y, float number, float size, int type, string name)
{
    int intNumber = 0;

    this->x = x;
    this->y = y;
    if (type == INT) {
        intNumber = (int)number; // number가 int인 경우
        this->message = to_string(intNumber);
    }
    else {
        this->message = to_string(number);
    }
    this->size = size;
    this->name = name;
}

Print::Print(float x, float y, string message, float size)
{
    this->x = x;
    this->y = y;
    this->message = message;
    this->size = size;
}

void Print::changeNum(int number)
{
    int intNumber = 0;
    intNumber = (int)number; // number가 int인 경우
    this->message = to_string(intNumber);
}

float Print::getX()
{
    return this->x = x;
}
float Print::getY()
{
    return this->y = y;
}
string Print::getMessage()
{
    return this->message;
}
float Print::getSize()
{
    return this->size = size;
}
string Print::getName() {
    return this->name = name;
}
void Print::setNumber(int number)
{
    this->number = number;
}
