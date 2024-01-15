#include <iostream>
#include <string>
#include "Window.h"
#include <SFML/Graphics.hpp>

using namespace std;

void Window:: makeButton(float x, float y, float width, float height, char color, string name) // (위치x, 위치y, 크기x, 크기y)
{
    Button button(x, y, width, height);
    button.setName(name);
    button.setColor(color);
    v_Button.push_back(button);
}

void Window::makePrint(float x, float y, float number, float size, int type, string name)
{
    Print print(x, y, number, size, type, name);
    v_Print.push_back(print);
}

void Window::makePrint(float x, float y, string message, float size)
{
    Print print(x, y, message, size);
    v_Print.push_back(print);
}

void Window::makeGraph(int initial_x, int initial_y, int x, int y, vector<int>& vect, int height) {
    Graph graph(initial_x, initial_y, x, y, vect, height);
    this->graph = graph;
}

Button Window::findButton(string name)
{
    for (int i = 0; i < v_Button.size(); i++) {
        if (v_Button[i].getName() == name) return v_Button[i];
    }
}

Print& Window::findPrint(string name)
{
    for (int i = 0; i < v_Print.size(); i++) {
        if (v_Print[i].getName() == name) return v_Print[i];
    }
}

Button Window::getButton(int n)
{
    return v_Button[n];
}

Print Window::getPrint(int n)
{
    return v_Print[n];
}

Graph& Window::getGraph()
{
    return this->graph;
}

int Window::getSizeOfV_Button()
{
    return v_Button.size();
}

int Window::getSizeOfV_Print()
{
    return v_Print.size();
}

void Window::removeButton(string name)
{
    for (int i = 0; i < v_Button.size(); i++) {
        if (v_Button[i].getName() == name) v_Button.erase(v_Button.begin() + i);
    }
}


void Window::clear_print() {
    this->v_Print.clear();
}