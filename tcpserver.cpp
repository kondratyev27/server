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


bool TcpServer::sendMsg(string msg , int _sockD)
{
    if(msg.empty()){
        return 0;
    }
    int byteCount = 0;
    int msgSize = msg.size();
    string sizeOfSendData = to_string( msgSize) ;
    if( ( send(_sockD, sizeOfSendData.c_str(), sizeOfSendData.length(), 0))== -1){ //send size
        cout << "Error sending data! \n";
        return 0;
    }

    char flag[2];
    if(recv(_sockD, flag, sizeof(flag), 0)== -1){ // just to synchronize
        cout << "Error recieving flag! \n";
        return 0;
    }

    while (byteCount != msgSize){
        int tmpByteCount = 0;
        if( (tmpByteCount = send(_sockD, msg.c_str(), msg.length(), 0))== -1){
            cout << "Error sending data! \n";
            return 0;
        }else{
            byteCount += tmpByteCount;
            msg = msg.substr(tmpByteCount);
        }
    }
    //        cout << "Sending of  " << byteCount << " bytes succesfull! \n";

    return 1;
}

string TcpServer::recieveMsg(int _sockD){
    string recMsg;
    char buf[bufSize];
    int byteCount = 0;

    if(recv(_sockD, buf, bufSize, 0)== -1){ //try to recieve msg size
        cout << "Error recieving data! \n";
        return "";
    }else{

        char succesFlag[]  = "1";
        if( send(_sockD, succesFlag, sizeof(succesFlag) , 0) == -1){
            cout << "Error sending flag! \n";
            return 0;
        }

        int recievingSize =  atoi(buf);

        while (byteCount != recievingSize ){ // whait until all bytes would'n be recieved
            int tmpByteCount = 0;
            memset(buf, 0, bufSize);
            if(( tmpByteCount = recv(_sockD, buf, bufSize, 0)) == -1){
                cout << "Error recieving data! \n";
                return "";
            }else{
                byteCount += tmpByteCount;
                recMsg += string(buf);
            }
        }
    }
    return recMsg;
}

void* TcpServer::makeDialog(void* sockD){
    int cSockD = *((int*)sockD);

    string newMsg =  recieveMsg(cSockD);

    if(!newMsg.empty()){
        cout << "\nReceived message from client: " << newMsg << endl;
        Server:: processingMsg(newMsg);
        sendMsg(newMsg, cSockD);

        //    int lokalBufSize = 64 * 1024;
        //    char buffer[lokalBufSize];
        //    memset(buffer, 0, lokalBufSize);
        //    int bytecount;

        //    if((bytecount = recv(cSockD, buffer, lokalBufSize, 0)) == -1){
        //        cout << "Error at receiving data!";
        //        return 0;
        //    }
        //    if((bytecount = send(cSockD, buffer, strlen(buffer), 0)) == -1){
        //        cout << "Error at sending data!";
        //    }

    }

    close(cSockD);
    delete (int*)sockD;
    return 0;
}


TcpServer:: ~TcpServer(){
    close(sockD);
}
