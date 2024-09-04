#include <raylib.h>
#include <raymath.h>
#include "view.h"
#include <iostream>
#include<cmath>
#include <deque>

using namespace std;
Color green={174,190,70,70};
Color darkgreen={20,60,20,200};
Color color1 = {29, 90, 114, 255};
Color color2 = {3, 36, 32, 255}; 
Color color3 = {109, 128, 199, 255};
Color color4 = {221, 215, 246, 255};

int cell=30;
int cnt=25;


class Food{
    public:
    Vector2 pos;
    Texture2D tx;
    Food(){
        pos=randompos();
        Image img=LoadImage("/Users/quantumobject/Desktop/food.png");
        tx=LoadTextureFromImage(img);
    }

    void draw(){
        DrawTexture(tx,cell*pos.x,cell*pos.y,WHITE);
    }

    Vector2 randompos(){
        float x=GetRandomValue(0,cnt-1);
        float y=GetRandomValue(0,cnt-1);
        Vector2 v;
        v.x=x;
        v.y=y;
        return v;
    }

    
};




class Snake{
    public:
    Vector2 dir={0,1};
    deque< Vector2> snake={{5,5},{5,6}};
    
    void draw(){
        for (int i=0;i<snake.size();i++){
            Vector2 pos=snake[i];
            Rectangle rec=Rectangle{cell*pos.x,cell*pos.y,(float) cell,(float) cell};
            DrawRectangleRounded(rec,0.5,10,color1);
        }
    }
    void move(){
        snake.pop_back();
        snake.push_front(Vector2Add(snake[0],dir));
    }


    bool collision(){
        if (snake[0].x==-1 || snake[0].y==-1 || snake[0].x==cnt || snake[0].y==cnt){
            snake[0]=Vector2Add(snake[0],Vector2Scale(dir,-1));
            return true;
        }
        for (int i=1;i<snake.size();i++)
            if (Vector2Equals(snake[0],snake[i]))
                return true;
        return false;
    }


};

double last=0;
bool updateNow(double t){
    double now= GetTime();
    if (now-last>=t){
        last=now;
        return true;
    }
    return false;
}

int main()
{
    int score=0;

    InitWindow(cell*cnt, cell*cnt, "HSSSSS");
    SetTargetFPS(60);
    Food food= Food();
    Snake s=Snake();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(color4);
        food.draw();
        s.draw();
        if (updateNow(0.2)){
        s.move();
        }
        if (IsKeyPressed(KEY_UP) && s.dir.y!=1)
            s.dir={0,-1};
        if (IsKeyPressed(KEY_DOWN)&& s.dir.y!=-1)
            s.dir={0,1};
        if (IsKeyPressed(KEY_RIGHT)&& s.dir.x!=-1)
            s.dir={1,0};
        if (IsKeyPressed(KEY_LEFT)&& s.dir.x!=1)
            s.dir={-1,0};
        if (Vector2Equals(s.snake[0],food.pos))
            {
                score++;
                food=Food();
                s.snake.push_back(Vector2Add(s.snake[0],s.dir));
            }
        DrawText(TextFormat("Score: %04i",score),cell*(cnt-10),0,40,color3);
        bool c=s.collision();
        if (c)
            {
                s.dir={0,0};
                DrawText("GG try again??",cell*4,cell*8,70,color3);
            }
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}