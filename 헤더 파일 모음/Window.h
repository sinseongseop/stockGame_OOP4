#ifndef WINDOW_H
#define WINDOW_H
#include <iostream>
#include <string>
#include <vector>
#include "Button.h"
#include "Print.h"
#include "Graph.h"

using namespace std;

class Window
{
private:
    vector<Button> v_Button;
    vector<Print> v_Print;
    Graph graph;
public:
    void makeButton(float x, float y, float width, float height, char color, string name); // (위치x, 위치y, 크기x, 크기y)
    void makePrint(float x, float y, float number, float size, int type, string name);
    void makePrint(float x, float y, string message, float size);
    void makeGraph(int initial_x, int initial_y, int x, int y, vector<int>& vect, int height);
    Button findButton(string name);
    Print& findPrint(string name);
    Button getButton(int n);
    Print getPrint(int n);
    Graph& getGraph();
    int getSizeOfV_Button();
    int getSizeOfV_Print();
    void removeButton(string name);

    void clear_print();

};

#endif
