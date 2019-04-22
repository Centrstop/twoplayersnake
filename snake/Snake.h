#ifndef SNAKE_H
#define SNAKE_H

#include <windows.h>

class Snake
{
public:
    Snake(int length);
    virtual ~Snake();
    void newHead(int x,int y);
    void moveHead(int delta_x,int delta_y);
    int getLength();
	void reset();
    const COORD& operator[](int n);
    void setHead(int x,int y);


private:
    COORD position;
    HANDLE hConsole;
    COORD *mySnake;
    int  lengthSnake;
    int  currLen,tmpx,tmpy;
};

#endif // SNAKE_H
