///////////////////////////////////////////////////
//	Socket.h
//	Header file for Socket class
//	By: Nissim Zohar
//	ID:  066412149
///////////////////////////////////////////////////
#ifndef __SOCKET_H__
#define __SOCKET_H__
#include <windows.h>
#include <exception>
#include <string>
#include <iostream>
using namespace std;

// This class takes care of the WSAStartup & WSACleanup calls automatically
class Win32Init {
public:
	class WSAInitException: public exception {};
	
	~Win32Init() { WSACleanup(); }
private:
	Win32Init(const Win32Init&);
	static Win32Init m_obj;
	Win32Init();
};
// Socket - a wrapper for socket functions
class Socket {
public:
	Socket(int type = SOCK_STREAM);
	Socket(SOCKET fd): m_fd(fd) {}
	virtual ~Socket() =0;
	// send: buf - the buffer to send, len - number of bytes to send
	virtual int send(const char *buf, int len);
	// recv: buf - buffer to read to, len - maximum number of bytes to read
	virtual int recv(char *buf, int len);
protected:
	SOCKET getFd() const { return m_fd; }
	SOCKET m_fd;
private:
	Socket(const Socket&);
	void operator=(const Socket&);
public:
	const string Get_IP();
// *** SocketExcpetion ***
public:
	class SocketException: public exception {
	public:
		SocketException(const char *msg): m_msg(msg) {}
		const char *what() const throw() { return m_msg.c_str(); }
	private:
		SocketException();
		std::string m_msg;
	};
};
#endif //__SOCKET_H__