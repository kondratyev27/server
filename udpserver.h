#ifndef UDPSERVER_H
#define UDPSERVER_H

#include "server.h"

class UdpServer: public Server{

    static void* makeDialog(void* sockD);
public:
    UdpServer();
    static void* threadStarter(void *serv);
    void* start() override;
    ~UdpServer();
};


#endif // UDPSERVER_H
