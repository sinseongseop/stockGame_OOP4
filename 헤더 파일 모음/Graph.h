#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>


#include "Print.h"

using namespace std;

class Graph
{
private:
    int initial_x, initial_y, x, y, height;
    vector<int> width; // 한칸마다 너비 설정 벡터
    vector<int> sum;
    vector<sf::RectangleShape> Line_H; // 가로 선 저장 벡터
    vector<sf::RectangleShape> Line_V; // 세로 선 저장 벡터
    vector<Print> prints; // 표 값
    vector<sf::FloatRect> buttons_s;
    vector<sf::FloatRect> buttons_b;

public:
    Graph();
    Graph(int initial_x, int initial_y, int x, int y, vector<int>& vect, int height); // vect : 한칸마다의 너비 저장되어 있는 벡터
    void printText(int x, int y, string message, vector<int>& vect); // 숫자 string으로 바꿔서 넣어주기
    sf::RectangleShape getLine_H(int n);
    sf::RectangleShape getLine_V(int n);
    int getX();
    int getY();
    Print getPrint(int n);
    int getSizeOfPrints();
    void setButton_s(int x, int y);
    void setButton_b(int x, int y);
    bool clickGraph(sf::Vector2f mousePosition, int n, int check);
};

#endif

