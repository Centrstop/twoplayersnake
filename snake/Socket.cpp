#include "Socket.h"

void Socket::WsaStartup(int version,WSADATA* wsaData)
{
    WSAStartup(version,wsaData);
}

Socket::Socket(int af=AF_INET,int type=SOCK_DGRAM,int proto=IPPROTO_UDP)
{
    mySocket=socket(af,type,proto);

}

int Socket::getStatus(){

return mySocket;

}
int Socket::Bind(){

return bind(mySocket,(SOCKADDR*)&socketaddr,sizeof(socketaddr));

}
void Socket::CloseSocket(){

closesocket(mySocket);

}
void Socket::SockAddrInit(short family,ULONG addr,u_short port)
{


    socketaddr.sin_family=family;
    socketaddr.sin_addr.s_addr=addr;
    socketaddr.sin_port=port;

    eventaddr=socketaddr;
    size=sizeof(eventaddr);
}

int Socket::RecvFrom(char* BUF,int SIZE)
{

    return recvfrom(mySocket,BUF,SIZE,0,(sockaddr*)&eventaddr,&size);
}

void Socket::SendTo(const char* BUF,int SIZE)
{

    sendto(mySocket,BUF,SIZE,0,(sockaddr*)&eventaddr,sizeof(eventaddr));
}

Socket::~Socket()
{


}
