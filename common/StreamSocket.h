///////////////////////////////////////////////////
//	StreamSocket.h
//	Header file for the StreamSocket class
//	a wrapper for stream sockets
//	By: Nissim Zohar
//	ID:  066412149
///////////////////////////////////////////////////

#ifndef __STREAMSOCKET_H__
#define __STREAMSOCKET_H__

#include "Socket.h"
#include <string>

// StreamSocket
class StreamSocket: public Socket {
public:
	StreamSocket();
	StreamSocket(SOCKET fd): Socket(fd) {}

	// listen: address, port - address and port to bind to, backlog - connections queue size
	virtual void listen(const char* address, int port, int backlog = SOMAXCONN);
	// accept: clientAddress - output parameter - will be filled with client's address
	// return value - client connection socket
	virtual StreamSocket* accept(std::string& clientAddress);
	// connect: address, port - address and port to connect to
	virtual void connect(const char* address, int port);	
private:
	StreamSocket(const StreamSocket&);
	void operator=(const StreamSocket&);
};


#endif //__STREAMSOCKET_H__
