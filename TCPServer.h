#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>

using namespace std;

#define MAXPACKETSIZE 1000

class TCPServer
{
	public:
	int sockfd, newsockfd, n, pid;
	struct sockaddr_in serverAddress;
	struct sockaddr_in clientAddress;
	pthread_t serverThread;
	char msg[ MAXPACKETSIZE ];
	static string Message;
	static time_t startTime;
	static time_t currentTime;
	static long numKb;

	void setup(int port);
	string receive();
	string getMessage();
	void Send(string msg);
	void detach();
	void clean();
	void printSummary();
	void run();
	
	
};

#endif
