#include "stdafx.h"
#include "Game.h"
#include "Snake.h"
#include <locale>
#include <iostream>
#include <conio.h>
#include "winsock.h"
#include "Socket.h"

using namespace std;

const int WINSOCK_VERSION = 0x0101;
const int BUFSIZE=4;
//SOCKET Socket;
WSADATA wsaData;
//SOCKADDR_IN socketaddr,eventaddr;
char bufSEND[BUFSIZE],bufRECV[BUFSIZE];
//int size;
string mess;


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"

#define ANSI_COLOR_BRIGHT  "\x1b[1m"
#define ANSI_COLOR_RESET   "\x1b[0m"

char Game::KEY_READING='d';
int Game::delta_x=1;
int Game::delta_y=0;

Game& Game::Instance()
{
    static Game theSingleInstance;
    return theSingleInstance;
}
Game::Game()
{
    setlocale(0,"");
    system("color 0a");


}

bool Game::Initialise(int x,int y,int len)
{
    int choice;
    do
    {
        cout<<"Âûáåðèòå ïóíêò\n1-Ñîçäàòü èãðó\n2-Âîéòè â èãðó\n3-Âûéòè";
        cout<<"\n>>";
        cin>>choice;
    }
    while(choice!=1 && choice!=2 && choice!=3);

    if(choice==3) return false;

    if(choice ==1)
        SERVER=true;
    else
        SERVER=false;

    Server=new Snake(len);
    Client=new Snake(len);
    if(SERVER)
    {
        YOU=Server;
        HE=Client;
    }
    else
    {
        YOU=Client;
        HE=Server;
    }
//He=new Snake(1,1,30);

    for(int i=0; i<10; i++)
    {
        Server->newHead(x+i,y);
        Client->newHead(x+i,23-y);
    }

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    //delta_x=1;
    //delta_y=0;
//ÝÊÑÏÅÐÈÌÅÍÒÛ


    //WSAStartup(WINSOCK_VERSION, &wsaData);
    // Socket = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);

    Socket::WsaStartup(WINSOCK_VERSION,&wsaData);
    mySock=new Socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);

    if (mySock->getStatus()==INVALID_SOCKET)
    {
        printf("Error create socket :-(\n");
        return false;
    }


    //socketaddr.sin_family = AF_INET;
    if(SERVER)
    {
        mySock->SockAddrInit(AF_INET,INADDR_ANY,1666);
    }
    //socketaddr.sin_addr.s_addr  = INADDR_ANY;
    else
    {

        string ip;
        cout<<"\n--------------\n";
        cin>>ip;
        mySock->SockAddrInit(AF_INET,inet_addr(ip.data()),1666);
        //socketaddr.sin_addr.s_addr  =inet_addr(ip.data());

    }

    //socketaddr.sin_port = 1666;

    //eventaddr=socketaddr;
    // size=sizeof(eventaddr);
    mess="HUI";

    if(SERVER)
    {
        char chInfo[64];
        gethostname(chInfo,sizeof(chInfo));
        printf(chInfo);
        printf(" GetHostName OK !!!!!\n");
    }
    else
        cout<<"Waiting...";
    if(SERVER)
    {
        //if (bind(Socket,(SOCKADDR*)&socketaddr,sizeof(socketaddr)) == SOCKET_ERROR)
        if (mySock->Bind() == SOCKET_ERROR)
        {
            printf("Error bind socket");
            exit(1);
        }
        mySock->RecvFrom(bufRECV,BUFSIZE);
        //recvfrom(Socket,bufRECV,BUFSIZE,0,(sockaddr*)&eventaddr,&size);
//        sendto(Socket,mess.data(),mess.length()+1,0,(sockaddr*)&eventaddr,sizeof(eventaddr));

        mySock->SendTo(mess.data(),mess.length()+1);
    }
    else
    {
        mySock->SendTo(mess.data(),mess.length()+1);
        //sendto(Socket,mess.data(),mess.length()+1,0,(sockaddr*)&eventaddr,sizeof(eventaddr));
        while(mySock->RecvFrom(bufRECV,BUFSIZE)==-1);
    }
    thread = CreateThread(NULL,0,KeyEvent,NULL, 0, NULL);
    EDA_EPTA_NAHUI=generateEat();

}
DWORD WINAPI Game::KeyEvent(LPVOID t)
{
    while(1)
    {
        KEY_READING=getch();
        switch(KEY_READING)
        {
        case 'w':
            if(delta_y!=1)
            {
                delta_x=0;
                delta_y=-1;

            }
            //else KEY_READING='s';
            break;
        case 's':
            if(delta_y!=-1)
            {
                delta_x=0;
                delta_y=1;

            }
            //else KEY_READING='w';
            break;
        case 'a':
            if(delta_x!=1)
            {
                delta_x=-1;
                delta_y=0;

            }
            //else KEY_READING='d';
            break;
        case 'd':
            if(delta_x!=-1)
            {
                delta_x=1;
                delta_y=0;

            }
            //else KEY_READING='d';
            break;

        }
    }
    return 0;
}
//--------------
COORD Game::generateEat()
{

    COORD eda;
    bool flag=false;
    do
    {
        eda.X=rand()%75+2;
        eda.Y=rand()%20+2;
        COORD temp;
        for(int i=0; i<YOU->getLength(); i++)
        {
            temp=(*YOU)[i];
            if(temp.X==eda.X && temp.Y==eda.Y)
            {
                flag=true;
                break;
            }
        }

        for(int i=0; !flag && (i<HE->getLength()); i++)
        {
            temp=(*HE)[i];

            if(temp.X==eda.X && temp.Y==eda.Y)
            {
                flag=true;
                break;
            }
        }

    }
    while(flag);

    return eda;
}

bool Game::Gameover(bool flag_win){
	COORD Puttext;
	Puttext.X=35;
	Puttext.Y=10;
	SetConsoleCursorPosition(hConsole, Puttext);
	puts("GAME OVER");
	if(flag_win){ 
	Puttext.X=36;
	Puttext.Y=11;
	SetConsoleCursorPosition(hConsole, Puttext);
	puts("YOU WIN");
	}
	else {
    Puttext.X=36;
	Puttext.Y=11;
	SetConsoleCursorPosition(hConsole, Puttext);
	puts("YOU LOSE");
	}
	Puttext.X=31;
	Puttext.Y=12;
	SetConsoleCursorPosition(hConsole, Puttext);
	puts("PRESS \"E\" TO EXIT");
	while(KEY_READING!='e'){
	}
	return true;
}
void Game::Draw()
{
    //hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    //std::cout << ANSI_COLOR_RED <<"Hello World\n"<< ANSI_COLOR_RESET;
    /* position.X = EAT_X;
     position.Y = EAT_Y;
     SetConsoleCursorPosition(hConsole, position);
     puts("$");
     if((py->x[py->currlen]==EAT_X)&&(py->y[py->currlen]==EAT_Y))
     {
         py->currlen++;
         createEat();
     };*/
    int i=0;
    while(1)
    {
        Sleep(20);
        system("cls");
		YOU->moveHead(delta_x,delta_y);
		YOU->reset();
        checkBorder(YOU);
        bufSEND[0]=(char)delta_x;
        bufSEND[1]=(char)delta_y;
        if(SERVER)
        {
            bufSEND[2]=(char)EDA_EPTA_NAHUI.X;
            bufSEND[3]=(char)EDA_EPTA_NAHUI.Y;
            //sendto(Socket,bufSEND,2,0,(sockaddr*)&eventaddr,sizeof(eventaddr));
            //while(recvfrom(Socket,bufRECV,BUFSIZE,0,(sockaddr*)&eventaddr,&size)==-1);
            mySock->SendTo(bufSEND,4);
            while(mySock->RecvFrom(bufRECV,BUFSIZE)==-1);
        }
        else
        {
            //while(recvfrom(Socket,bufRECV,BUFSIZE,0,(sockaddr*)&eventaddr,&size)==-1);
            //sendto(Socket,bufSEND,2,0,(sockaddr*)&eventaddr,sizeof(eventaddr));
            while(mySock->RecvFrom(bufRECV,BUFSIZE)==-1);
            mySock->SendTo(bufSEND,2);
            EDA_EPTA_NAHUI.X=(int)bufRECV[2];
            EDA_EPTA_NAHUI.Y=(int)bufRECV[3];
        }


		HE->moveHead((int)bufRECV[0],(int)bufRECV[1]);
		if(HE->getLength()==15) {Gameover(false); return;};
		if(YOU->getLength()==15) {Gameover(true); return;}; 
		HE->reset();
        checkBorder(HE);

        COORD head=(*YOU)[YOU->getLength()-1];

        if(memcmp((char*)&head,(char*)&EDA_EPTA_NAHUI,sizeof(head))==0)
        {
            YOU->newHead(head.X+delta_x,head.Y+delta_y);
            if(SERVER)
            EDA_EPTA_NAHUI=generateEat();
        }
        head=(*HE)[HE->getLength()-1];

       if(memcmp((char*)&head,(char*)&EDA_EPTA_NAHUI,sizeof(head))==0)
        {
            HE->newHead(head.X+(int)bufRECV[0],head.Y+(int)bufRECV[1]);
            if(SERVER)
            EDA_EPTA_NAHUI=generateEat();
        }

        for(int i=0; i<YOU->getLength(); i++)
        {
            SetConsoleCursorPosition(hConsole, (*YOU)[i]);
            puts("®");

        }
        for(int i=0; i<HE->getLength(); i++)
        {
            SetConsoleCursorPosition(hConsole, (*HE)[i]);
            //cout<<<<"*"<<ANSI_COLOR_RESET;
            // puts(ANSI_COLOR_RED"*"ANSI_COLOR_RESET);
            puts("©");
        }
        SetConsoleCursorPosition(hConsole,EDA_EPTA_NAHUI);
        //cout<<<<"*"<<ANSI_COLOR_RESET;
        // puts(ANSI_COLOR_RED"*"ANSI_COLOR_RESET);
        puts("$");
    }

}
void Game::checkBorder(Snake* s)
{
    COORD head=(*s)[s->getLength()-1];
    if(head.X<0)
        s->moveHead(80-head.X,0);
    //Server->setHead(80,(*Server)[currlen-1].Y);

    if(head.X>80)
        s->moveHead(-head.X,0);
    // Server->setHead(0,(*Server)[currlen-1].Y);

    if(head.Y<0)
        s->moveHead(0,23-head.Y);
    //Server->setHead((*Server)[currlen-1].X,23);

    if(head.Y>23)
        s->moveHead(0,-head.Y);

    //return head;
}
//----------------


Game::~Game()
{

    delete Server;
    delete Client;
    //delete He;

}
