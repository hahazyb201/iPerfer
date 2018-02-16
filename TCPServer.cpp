#include "TCPServer.h" 

string TCPServer::Message;
time_t TCPServer::startTime;
time_t TCPServer::currentTime;
long TCPServer::numKb;


void TCPServer::setup(int port)
{
	startTime=0;
	currentTime=0;
	numKb=0;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
 	memset(&serverAddress,0,sizeof(serverAddress));
	serverAddress.sin_family=AF_INET;
	serverAddress.sin_addr.s_addr=htonl(INADDR_ANY);
	serverAddress.sin_port=htons(port);
	bind(sockfd,(struct sockaddr *)&serverAddress, sizeof(serverAddress));
 	listen(sockfd,5);
}

string TCPServer::receive()
{
	string str;
	socklen_t sosize  = sizeof(clientAddress);
	newsockfd = accept(sockfd,(struct sockaddr*)&clientAddress,&sosize);
	startTime=time(NULL);
	str = inet_ntoa(clientAddress.sin_addr);	
	char msg[MAXPACKETSIZE];
	while(1)
	{
		n=recv(newsockfd,msg,MAXPACKETSIZE,MSG_WAITALL);
		
		
		/*if(n==0)
		{
		   close(newsockfd);
		   break;
		}*/
		
		msg[n]=0;
		//send(newsockfd,msg,n,0);
		Message = string(msg);
		
		numKb++;
		if(!Message.substr(0,6).compare("Dataok")){	
			numKb--;
			currentTime=time(NULL);
			cout<<"FIN: DataOk"<<endl;				
			Send("Yes!");
			printSummary();
			break;		
		}
		
        }
	return str;
}

string TCPServer::getMessage()
{
	return Message;
}

void TCPServer::Send(string msg)
{
	send(newsockfd,msg.c_str(),msg.length(),0);
}

void TCPServer::clean()
{
	Message = "";
	memset(msg, 0, MAXPACKETSIZE);
}

void TCPServer::run(){
	
	receive();
	detach();
}


void TCPServer::printSummary(){
	cout<<"received = "<<numKb<<" KB  Rate = "<<((float)numKb)*8.0/1000/((float)(currentTime-startTime))<<" Mbps"<<endl;
}
void TCPServer::detach()
{
	close(sockfd);
	close(newsockfd);
} 
