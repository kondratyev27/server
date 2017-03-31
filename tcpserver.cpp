#include <iostream>
#include "tcpserver.h"
#include <string.h>
#include <pthread.h>

using namespace std;

TcpServer::TcpServer(): Server("TCP")
{
    sockD = socket(AF_INET, SOCK_STREAM, 0);
    if(sockD == -1){
        setError(string("Error initializing "+ getProcolName() +" socet!"));
    }

    sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET ;
    servaddr.sin_port = htons(hostPort);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if( bind( sockD, (sockaddr*)&servaddr, sizeof(servaddr)) == -1 ){
        close(sockD);
        setError(string("Error binding to socket at " + getProcolName()));
    }

    if(listen( sockD, 10) == -1 ){
        close(sockD);
        setError("Error listening!");
    }
}


void* TcpServer::start()
{
    if(!errorFlag){
        cout << "Ready to work with " << getProcolName() <<" clients.\n\n";
        socklen_t addrSize = sizeof(sockaddr_in);
        while(true){
            sockaddr_in sadr;
            int *cSockD = new int;

            if((*cSockD = accept( sockD, (sockaddr*)&sadr, &addrSize)) != -1){ // TODO: Add threads counter.
                pthread_t threadId = 0;
                pthread_create( &threadId, 0, &makeDialog, (void*)cSockD );
                pthread_detach(threadId);
            }
            else{
                cout << "Can't accept new client!";
            }
        }
    }
    return 0;
}

void* TcpServer::makeDialog(void* sockD){
    int cSockD = *((int*)sockD);

    int lokalBufSize = 64 * 1024;
    char buffer[lokalBufSize];
    memset(buffer, 0, lokalBufSize);
    int bytecount;

    if((bytecount = recv(cSockD, buffer, lokalBufSize, 0)) == -1){
        cout << "Error at receiving data!";
        return 0;
    }
    cout << "Received message from client: " << buffer << endl;
    Server:: processingMsg(buffer);
    if((bytecount = send(cSockD, buffer, strlen(buffer), 0)) == -1){
        cout << "Error at sending data!";
    }
    printf("Sent bytes %d\n", bytecount);

    close(cSockD);
    delete (int*)sockD;
    return 0;
}

TcpServer:: ~TcpServer(){
    close(sockD);
}
