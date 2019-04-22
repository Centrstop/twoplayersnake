#include "stdafx.h"
#include "Snake.h"
#include <iostream>
using namespace std;
Snake::Snake(int length)
{
    mySnake=new COORD[length];
    lengthSnake=length;
    currLen=0;

}
 

void Snake::moveHead(int delta_x,int delta_y)
{



    for(int i=0; i<(currLen-1); i++)
        mySnake[i]=mySnake[i+1];

    mySnake[currLen-1].X+=delta_x;
    mySnake[currLen-1].Y+=delta_y;
	
    for(int i=currLen+1; i<lengthSnake; i++)
        mySnake[i]=mySnake[currLen-1];
}

void Snake::newHead(int x,int y)
{
    if(++currLen >= lengthSnake)
    {
        //do something
    }
    else
    {
        mySnake[currLen-1].X=x;
        mySnake[currLen-1].Y=y;
    }

}

void Snake::reset(){
	bool flag_eat=false;
	for(int i=0;i<currLen-2;i++){
		if((mySnake[currLen-1].X==mySnake[i].X)&&(mySnake[currLen-1].Y==mySnake[i].Y)) {flag_eat=true;cout<<i;};
		
	}
	if(flag_eat){
     for(int i=0;i<10;i++){
      mySnake[i].X=mySnake[currLen-10+i].X;
	  mySnake[i].Y=mySnake[currLen-10+i].Y;
	 }
	 currLen=10;
	}

}

void Snake::setHead(int x,int y){
mySnake[currLen-1].X=x;
mySnake[currLen-1].Y=y;

}
int Snake::getLength()
{

    return currLen;
}

const COORD& Snake::operator[](int n)
{

    return mySnake[n];
}



Snake::~Snake()
{
    delete[] mySnake;
    //dtor
}
