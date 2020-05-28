////////////////////////////////////////////////////
//	StreamSocket.cpp
//	By: Nissim Zohar
//	ID:  066412149
///////////////////////////////////////////////////
#include "StreamSocket.h"

StreamSocket::StreamSocket(): Socket(SOCK_STREAM) {}

// bind and listen
void StreamSocket::listen(const char* address, int port, int backlog) {
	struct sockaddr_in m_addr;
	ZeroMemory(&m_addr, sizeof(m_addr));
	m_addr.sin_family = AF_INET;
	if (address)
		m_addr.sin_addr.s_addr = inet_addr(address);
	else
		m_addr.sin_addr.s_addr = INADDR_ANY;
	m_addr.sin_port = htons(port);

	if (bind(getFd(), (struct sockaddr*)&m_addr, sizeof(m_addr)) == SOCKET_ERROR )
		throw SocketException("Failed to bind socket");

	if (::listen(getFd(), backlog) == SOCKET_ERROR)
		throw SocketException("Failed to listen on socket");
}

StreamSocket* StreamSocket::accept(std::string& clientAddress) {
	SOCKET fd;
	struct sockaddr_in cli_addr;
	int cli_addrLen = sizeof(cli_addr);
	
	if ((fd = ::accept(getFd(), (sockaddr*)&cli_addr, &cli_addrLen)) == INVALID_SOCKET) {
		if (WSAGetLastError() != WSAEWOULDBLOCK)
			throw SocketException("Failed to accept");
		return NULL;
	}
	clientAddress = inet_ntoa(cli_addr.sin_addr);
	return new StreamSocket(fd);
}

void StreamSocket::connect(const char* address, int port) {
	struct sockaddr_in addr;

	ZeroMemory(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(address);
	addr.sin_port = htons(port);
	if (::connect(getFd(), (struct sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
		throw SocketException("Failed to connect");	
}
