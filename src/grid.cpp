
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include<cmath>
#include <vector> 
#include "grid.h"
#include <cstdlib> 

using namespace std;
    Color g={90,190,90,225};

Grid::Grid(int r,int c,int cell){
        rows=r;
        cols=c;
        cs=cell;
        for (int i=0;i<r+2;i++){
            vector<int> x(c+2);
            fill(x.begin(),x.end(),0);
            a.push_back(x);
        }
    }

void Grid:: Draw(){
        for (int i=1;i<rows+1;i++){
            for (int j=1;j<cols+1;j++){
                if (a[i][j]==1){
                    DrawRectangle((i-1)*cs,(j-1)*cs,cs,cs, (i+j)%2?GREEN:g);
                }
            }
        }
    }


void Grid:: update(){
        vector<vector<int > > b;
        vector<int> v(cols+2);
        fill(v.begin(),v.end(),0);
        b.push_back(v);
        for (int i=1;i<rows;i++){
            vector<int> x(cols+2);
            fill(x.begin(),x.end(),0);
            for (int j=1;j<cols;j++){
                int c=0;
                if (a[i-1][j-1]==1)
                    c++;
                if (a[i-1][j-0]==1)
                    c++;
                if (a[i-1][j+1]==1)
                    c++;
                if (a[i][j+1]==1)
                    c++;
                if (a[i][j-1]==1)
                    c++;
                if (a[i+1][j]==1)
                    c++;
                if (a[i+1][j-1]==1)
                    c++;
                if (a[i+1][j+1]==1)
                    c++;
                if (a[i][j]==1 && c>=2 && c<4)
                    x[j]=1;
                else if (a[i][j]==0 && c==3)
                    x[j]=1;
            }
            b.push_back(x);
        }
        b.push_back(v);
        a=b;
    }

void Grid::randomFill(int n ){
    while (n-->0){
        int i=rand()%rows+1;
        int j=rand()%cols+1;
        a[i][j]=1;
    }
}

int Grid::getPop(){
    int p=0;
    for (int i=1;i<=rows;i++){
        for (int j=1;j<cols;j++)
            p+=a[i][j];
    }
    return p;
}