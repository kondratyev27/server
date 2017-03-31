#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "server.h"

class TcpServer: public Server{

    static void* makeDialog(void* sockD);
public:
    TcpServer();
    void* start() override;
    ~TcpServer();
};

#endif // TCPSERVER_H



