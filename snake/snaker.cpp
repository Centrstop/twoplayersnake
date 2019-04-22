// snake.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include "Game.h"
#include "Snake.h"
#include "Socket.h"
#include <time.h>


using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
    srand(time(NULL));
    Game& game=Game::Instance();
    game.Initialise(1,1,30);

    game.Draw();




    return 0;
}
