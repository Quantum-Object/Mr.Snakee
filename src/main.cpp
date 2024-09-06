#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include<cmath>
#include <vector>
#include "grid.h"

using namespace std;
Color color1 = {24, 1, 97};
    Color color2 = {79, 23, 135};
    Color color3 = {235, 54, 120};
    Color color4 = {251, 119, 60};

int cell=10;
int cnt=100;


int main()
{
    
    InitWindow(cell*cnt, cell*cnt, "Game of Life");
    SetTargetFPS(12);


    Grid g=Grid(cnt,cnt,cell);
    bool v=false;
    int pop=0;
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKBLUE);
        g.Draw();
        DrawText(TextFormat("population: %04i", g.getPop()), 4*cell*cnt/6, cell, 20,WHITE);
        if (v){
        g.update();
        }else {
            int x=GetMouseX()/cell;
            int y=GetMouseY()/cell;
            g.a[x][y]=1;
            g.a[(x-1)%cnt][(y-1)%cnt]=1;
            g.a[(x+1)%cnt][(y+1)%cnt]=1;
            g.a[(x-1)%cnt][(y+1)%cnt]=1;
            g.a[(x+1)%cnt][(y-1)%cnt]=1;
            DrawText("Press Enter to Run",cell*cnt/4,cell*cnt/3,50,WHITE);
        }
        if (IsKeyPressed(KEY_ENTER))
            v=true;
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}