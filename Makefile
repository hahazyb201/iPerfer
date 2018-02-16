all: 
	g++ -Wall -o iPerfer iPerfer.cpp -I./ ./TCPServer.cpp ./TCPClient.cpp -std=c++11 -lpthread
