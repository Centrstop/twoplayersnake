#include "stdafx.h"
#include <iostream>
#include "Game.h"
#include "Snake.h"
#include "Socket.h"
#include <time.h>
using namespace std;

int main()
{
    srand(time(NULL));
    Game& game=Game::Instance();
	if(!(game.Initialise(1,1,30))) { cout<<"EXIT"; return 0;};

    game.Draw();




    return 0;
}
