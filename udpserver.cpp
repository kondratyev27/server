#include "udpserver.h"
#include <string.h>
#include <iostream>


using namespace std;

UdpServer::UdpServer(): Server("UDP")
{
    sockD = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockD == -1){
        setError(string("Error initializing "+ getProcolName() +" socet!"));
    }

    sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET ;
    servaddr.sin_port = htons(hostPort);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY) ;

    if( bind( sockD, (sockaddr*)&servaddr, sizeof(servaddr)) == -1 ){
        close(sockD);
        setError(string("Error binding to socket at " + getProcolName()));
    }
}


void* UdpServer::start()
{
    if(!errorFlag){
        cout << "Ready to work with " << getProcolName() <<" clients.\n\n";
        sockaddr_in clientAddr;
        socklen_t addrSize = sizeof(sockaddr_in);
        while(true){
            char buffer[bufSize];
            if(( recvfrom(sockD, buffer, bufSize, 0, ( sockaddr *) &clientAddr, &addrSize)) == -1){
                cout << "Error at receiving data!";
                continue;
            }
            cout << "Received message from client: " << buffer << endl;
            Server:: processingMsg(buffer);
            if(sendto(sockD, buffer, strlen(buffer), 0, ( sockaddr *) &clientAddr, addrSize) == -1){
                cout << "Error at sending data!";
            }
            sleep(1);
        }
    }
    return 0;
}

void * UdpServer::threadStarter(void * serv){
    return ((UdpServer*)serv)->start();
}

UdpServer:: ~UdpServer(){
    close(sockD);
}
