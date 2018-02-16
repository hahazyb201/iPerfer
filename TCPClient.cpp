#include "TCPClient.h"
#include <iostream>


TCPClient::TCPClient()
{
	sock = -1;
	port = 0;
	address = "";
	duration=0;
}

bool TCPClient::setup(string address , int port, long t)
{
  	if(sock == -1)
	{
		sock = socket(AF_INET , SOCK_STREAM , 0);
		if (sock == -1)
		{
      			cout << "Could not create socket" << endl;
    		}
        }
  	if(inet_addr(address.c_str()) == -1)
  	{
    		struct hostent *he;
    		struct in_addr **addr_list;
    		if ( (he = gethostbyname( address.c_str() ) ) == NULL)
    		{
		      herror("gethostbyname");
      		      cout<<"Failed to resolve hostname\n";
		      return false;
    		}
	   	addr_list = (struct in_addr **) he->h_addr_list;
    		for(int i = 0; addr_list[i] != NULL; i++)
    		{
      		      server.sin_addr = *addr_list[i];
		      break;
    		}
  	}
  	else
  	{
    		server.sin_addr.s_addr = inet_addr( address.c_str() );
  	}
  	server.sin_family = AF_INET;
  	server.sin_port = htons( port );
  	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
  	{
    		perror("connect failed. Error56");
    		return false;
  	}
	duration=t;
  	return true;
}

bool TCPClient::Send(char * str)
{
	if(sock != -1) 
	{
		int n=send(sock , str , 1000 , 0);
		if(n<1000)		
			cout<<"SendLen: "<<n<<endl;
		if( n< 0)
		{
			cout << "Send failed : " << string(str) << endl;
			return false;
		}
	}
	else
		return false;
	return true;
}

string TCPClient::receive(int size)
{
  	char buffer[size];
	memset(&buffer[0], 0, sizeof(buffer));

  	string reply;
	if( recv(sock , buffer , size, 0) < 0)
  	{
	    	cout << "receive failed!" << endl;
		return nullptr;
  	}
	buffer[size-1]='\0';
  	reply = buffer;
  	return reply;
}

string TCPClient::read()
{
  	char buffer[1] = {};
  	string reply;
  	while (buffer[0] != '\n') {
    		if( recv(sock , buffer , sizeof(buffer) , 0) < 0)
    		{
      			cout << "receive failed!" << endl;
			return nullptr;
    		}
		reply += buffer[0];
	}
	return reply;
}
void TCPClient::run(){
	time_t startTime=time(NULL);
	time_t currentTime=0;
	char data[1000];
	memset(data,'0',1000);
	char fin[1000]="Dataok";
	memset(fin+6,'0',994);
	long numKb=0;
	
	while(currentTime-startTime<duration){
		
		Send(data);
		numKb++;
		currentTime=time(NULL);
	}
	
	Send(fin);
	string rev=receive();
	currentTime=time(NULL);
	cout<<"ack: "<<rev<<endl;
	if(!rev.compare("Yes!")){
		exit();	
		printSummary(numKb,startTime,currentTime);
		
	}
	
	
}
void TCPClient::printSummary(long Kb,long start,long end){
	cout<<"sent = "<<Kb<<" KB  Rate = "<<((float)Kb)*8.0/1000/((float)(end-start))<<" Mbps"<<endl;
}
void TCPClient::exit()
{
    close( sock );
}
