#pragma once
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include<cmath>
#include <vector>
#include "grid.h"
using namespace std;
class Grid{
    public:
        int rows,cols,cs;
        vector<vector<int> > a;
    Grid(int r,int c,int cell);

    void Draw();

    void update();

    void randomFill(int n);

    int getPop();

};