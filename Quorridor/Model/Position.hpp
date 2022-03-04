#include <string>
#ifndef POSITION_HPP
#define POSITION_HPP

class Position {
private:
    int x, y;
public:
    Position(int x, int y);
    Position(std::string pos);

    void setX(int nX) {x = nX;}
    void setY(int nY) {y = nY;}

    int getX() const {return x;}
    int getY() const {return y;}

    bool operator==(const Position& other) const;
    Position operator*(int i);
    Position operator/(int i);
    Position operator-(Position& other) const;
    virtual Position operator=(const Position& other);
};

#endif