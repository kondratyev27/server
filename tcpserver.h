#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "server.h"

class TcpServer: public Server{

    static void* makeDialog(void* sockD);
public:
    TcpServer();
    void* start() override;

    static bool sendMsg(std::string msg, int _sockD );
    static std::string recieveMsg(int _sockD);

    ~TcpServer();
};

#endif // TCPSERVER_H



