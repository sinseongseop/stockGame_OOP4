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
    vector<int> width; // ��ĭ���� �ʺ� ���� ����
    vector<int> sum;
    vector<sf::RectangleShape> Line_H; // ���� �� ���� ����
    vector<sf::RectangleShape> Line_V; // ���� �� ���� ����
    vector<Print> prints; // ǥ ��
    vector<sf::FloatRect> buttons_s;
    vector<sf::FloatRect> buttons_b;

public:
    Graph();
    Graph(int initial_x, int initial_y, int x, int y, vector<int>& vect, int height); // vect : ��ĭ������ �ʺ� ����Ǿ� �ִ� ����
    void printText(int x, int y, string message, vector<int>& vect); // ���� string���� �ٲ㼭 �־��ֱ�
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

