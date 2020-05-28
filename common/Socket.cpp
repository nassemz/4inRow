///////////////////////////////////////////////////
//	Socket.cpp
//	By: Nissim Zohar
//	ID:  066412149
///////////////////////////////////////////////////
#include "Socket.h"
#include "StreamSocket.h"

Win32Init Win32Init::m_obj;

Win32Init::Win32Init() {
	// init WSA
	WORD	wVersionRequested;
	WSADATA wsaData;
	
	wVersionRequested = MAKEWORD(2, 2);
	
	int err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) throw WSAInitException();
}

// Create the socket
Socket::Socket(int type): m_fd(0) {
	if ((m_fd = socket(PF_INET, type, 0)) == INVALID_SOCKET )
		throw SocketException("Failed to create socket");
}

Socket::~Socket() {
	closesocket(m_fd);
}

int Socket::send(const char* buf, int len) {
	int retVal = ::send(m_fd, buf, len, 0);
	if (retVal == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK)
		throw SocketException("Failed to send on socket");
	return retVal;
}

int Socket::recv(char *buf, int len) {
	int retVal = ::recv(m_fd, buf, len, 0);
	if (retVal == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK)
		throw SocketException("Failed to send on socket");
	return retVal;
}
const string Socket::Get_IP()
{
	SOCKADDR_IN SockAddr;
	
	char strHost[50];
	memset(strHost, 0 , 50);
	gethostname(strHost, 50);
	
	hostent* HostInfo = gethostbyname(strHost);
	memcpy(&(SockAddr.sin_addr),HostInfo->h_addr,HostInfo->h_length);
	
	char* pIP = inet_ntoa(SockAddr.sin_addr);
	
	string p(pIP);
	return p;
}
