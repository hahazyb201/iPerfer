#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdexcept>
#include <signal.h>
#include "TCPClient.h"
#include "TCPServer.h"

using namespace std;
TCPClient tClient;
TCPServer tServer;


int main(int argc, char** argv){
	
	bool client=false;
	bool server=false;
	string host="";
	int port=0;
	long duration=0;
	if(argc<=3){
		cout<<"Error: missing or additional arguments1"<<endl;
		exit(EXIT_FAILURE);	
	}else{
		
		if(string(argv[1])=="-s"){
			cout<<"test "<<argv[1]<<endl;
			if(argc!=4){
				cout<<"Error: missing or additional arguments2"<<endl;
				exit(EXIT_FAILURE);			
			}
			server=true;
			client=false;		
		}	
		if(string(argv[1])=="-c"){
			if(argc!=8){
				cout<<"Error: missing or additional arguments3"<<endl;
				exit(EXIT_FAILURE);			
			}
			client=true;
			server=false;		
		}
		if((server||client)!=true){
			cout<<"Error: missing or additional arguments4"<<endl;
			exit(EXIT_FAILURE);		
		}
	}
	
	int i=1;
	while(i<argc&&argv[i][0]=='-'){
		string arg=argv[i++];
		if(arg.length()!=2){
			cout<<"Error: missing or additional arguments5"<<endl;
			exit(EXIT_FAILURE);		
		}
		if(arg[1]=='c'||arg[1]=='s')
			continue;
		switch(arg[1]){
			case 't':
				if(client){
					try{
						duration=stol(argv[i++]);
					
					}catch(const invalid_argument& ia){
						cout<<"Error: time must be an integer"<<endl;
						exit(EXIT_FAILURE);				
	
					}
								
				}else{
					cout<<"Error: missing or additional arguments6"<<endl;
					exit(EXIT_FAILURE);	
			
				}
				break;
			case 'p':
				try{
					port=stoi(argv[i++]);				
				}catch(const invalid_argument& ia){
					cout<<"Error: port number must be in the range 1024 to 65535"<<endl;
					exit(EXIT_FAILURE);				
	
				}
				if(port<=1024||port>=65535){
					cout<<"Error: port number must be in the range 1024 to 65535"<<endl;
					exit(EXIT_FAILURE);
				}
				break;
			case 'h':
				if(client){
					host=argv[i++];				
				}else{
					cout<<"Error: missing or additional arguments7"<<endl;
					exit(EXIT_FAILURE);				
				}
				break;
			default:
				cout<<"Error: missing or additional arguments8"<<endl;
				exit(EXIT_FAILURE);
			
		}
	}
  	if(client){
		
		cout<<host<<" "<<port<<" "<<duration<<endl;	
		//signal(SIGINT, sig_exit);
		tClient.setup(host,port,duration);
		tClient.run();
		
		
	}else if(server){
		cout<<port<<endl;
		tServer.setup(port);
		tServer.run();
	}

	
	
}
