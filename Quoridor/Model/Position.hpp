//
// Created by Mark Dimitrov on 15/02/2022.
//

#pragma once 


class Position {
private:
    int x,y;
public:
    Position(int x, int y);
    void setX(int nX){
        x = nX;
    }
    void setY(int nY){
        y=nY;
    }
    int getX() const{
        return x;
    }
    int getY() const{
        return y;
    }
};
