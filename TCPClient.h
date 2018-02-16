#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netdb.h> 
#include <vector>
#include <time.h>

typedef char byte;
using namespace std;

class TCPClient
{
  private:
    int sock;
    std::string address;
    int port;
    long duration;
    struct sockaddr_in server;

  public:
    TCPClient();
    bool setup(string address, int port, long t);
    bool Send(char * str);
    string receive(int size = 4096);
    string read();
    void run();
    void exit();
    void printSummary(long Kb,long start,long end);
};

#endif
