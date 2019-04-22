#ifndef SOCKET_H
#define SOCKET_H

#include <winsock.h>



class Socket
{
public:
    Socket(int,int,int);
    static void WsaStartup(int,WSADATA*);
    void SockAddrInit(short,unsigned long,u_short);
    int RecvFrom(char*,int);
    void SendTo(const char*,int);
    int Bind();
    void CloseSocket();

int getStatus();
    virtual ~Socket();

protected:

private:

    SOCKET mySocket;
    WSADATA wsaData;
    SOCKADDR_IN socketaddr,eventaddr;
//    char bufSEND[BUFSIZE],bufRECV[BUFSIZE];
    int size;

};

#endif // SOCKET_H
