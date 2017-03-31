#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>
#include <string>


class Server
{
    std::string procolName;
protected:
    const int hostPort = 4321;
    const int bufSize = 64*1024;
    int sockD;
    bool errorFlag;
    void setError(const std::string &errMesg);
    std::string getProcolName() const;
    static void processingMsg(const std::string& msg);
public:
    virtual void* start() = 0;
    Server(std::string _procolName);
};

#endif // SERVER_H


