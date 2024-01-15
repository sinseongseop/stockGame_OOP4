#include <iostream>
#include <string>
#include "Print.h"
#include "Graph.h"
#include <SFML/Graphics.hpp>


Graph::Graph() {}

Graph::Graph(int initial_x, int initial_y, int x, int y, vector<int>& vect, int height) // vect : 한칸마다의 너비 저장되어 있는 벡터
{
    this->initial_x = initial_x;
    this->initial_y = initial_y;
    this->x = x;
    this->y = y;
    this->height = height;

    // 셀 너비 설정(sum)   cf) 가로선 길이 - sum[5]
    sum.push_back(vect[0]);
    for (int i = 1; i < x; i++) {
        sum.push_back(sum[i - 1] + vect[i]);
    }

    // 셀 너비 저장(width)
    for (int i = 0; i < x; i++) {
        width.push_back(vect[i]);
    }

    // 가로 선 생성 및 벡터에 저장
    for (int i = 0; i <= y; ++i) {
        sf::RectangleShape horizontalLine;
        horizontalLine.setSize(sf::Vector2f(sum[x - 1], 1.0f));
        horizontalLine.setFillColor(sf::Color::Black);
        horizontalLine.setPosition(initial_x, i * height + initial_y);
        Line_H.push_back(horizontalLine);
    }

    // 세로 선 생성 및 벡터에 저장
    for (int i = 0; i <= x; ++i) {
        sf::RectangleShape verticalLine;
        verticalLine.setSize(sf::Vector2f(1.0f, y * height));
        verticalLine.setFillColor(sf::Color::Black);
        if (i == 0) {
            verticalLine.setPosition(initial_x, initial_y);
            Line_V.push_back(verticalLine);
            continue;
        }
        verticalLine.setPosition(sum[i - 1] + initial_x, initial_y);
        Line_V.push_back(verticalLine);
    }
}
void Graph::printText(int x, int y, string message, vector<int>& vect) // 숫자 string으로 바꿔서 넣어주기
{
    if (x == 0) {
        Print print(initial_x + vect[x], initial_y + y * height + height * 0.25, message, height * 0.4);
        prints.push_back(print);
    }
    else {
        Print print(initial_x + sum[x - 1] + vect[x], initial_y + y * height + height * 0.25, message, height * 0.4);
        prints.push_back(print);
    }

}
sf::RectangleShape Graph::getLine_H(int n)
{
    return this->Line_H[n];
}
sf::RectangleShape Graph::getLine_V(int n)
{
    return this->Line_V[n];
}
int Graph::getX()
{
    return this->x;
}
int Graph::getY()
{
    return this->y;
}
Print Graph::getPrint(int n)
{
    return prints[n];
}
int Graph::getSizeOfPrints()
{
    return prints.size();
}
void Graph::setButton_s(int x, int y)
{
    sf::FloatRect Area;
    Area.left = initial_x + sum[x - 1];
    Area.top = initial_y + height * y;
    Area.width = width[x - 1];
    Area.height = height;
    buttons_s.push_back(Area);
}
void Graph::setButton_b(int x, int y)
{
    sf::FloatRect Area;
    Area.left = initial_x + sum[x - 1];
    Area.top = initial_y + height * y;
    Area.width = width[x - 1];
    Area.height = height;
    buttons_b.push_back(Area);
}
bool Graph::clickGraph(sf::Vector2f mousePosition, int n, int check) {
    if (check == 0)
    {
        if (buttons_s[n].contains(mousePosition)) return true;
        else return false;
    }
    else
    {
        if (buttons_b[n].contains(mousePosition)) return true;
        else return false;
    }
}