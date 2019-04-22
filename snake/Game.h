#ifndef GAME_H
#define GAME_H
#include <windows.h>
class Snake;
class Socket;
class Game
{
public:
    static Game& Instance();
    bool Initialise(int,int,int);
    void Draw();
	bool Gameover(bool);
    virtual ~Game();

private:
    Game();
    Game(const Game& root);
    Game& operator=(const Game&);
    Snake* Server;
    Snake* Client;
    Snake *YOU,*HE;
    bool SERVER;
    static DWORD WINAPI KeyEvent(LPVOID t);
    void checkBorder(Snake* s);
    static char KEY_READING;
    HANDLE hConsole;
    HANDLE thread;
    static int delta_y,delta_x;
    Socket* mySock;
    COORD generateEat();
    COORD EDA_EPTA_NAHUI;

};

#endif // GAME_H
