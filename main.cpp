#include <iostream>
#include <pthread.h>
#include "tcpserver.h"
#include "udpserver.h"


//std::mutex coutLocker;               // TODO: make cout thread safety
//void print(const std::string &text)
//{
//    coutLocker.lock();
//    std :: cout << text;
//    coutLocker.unlock();
//}


int main()
{
       std :: cout << "text";
    TcpServer tServ;
    UdpServer uServ;

    pthread_t UdpServThrId=0;
    pthread_create( &UdpServThrId, 0 , &uServ.threadStarter, &uServ ); // start Udp in new thread
    tServ.start(); // start listening Tcp in main thread

    pthread_join(UdpServThrId, 0);
    return 0;
}

