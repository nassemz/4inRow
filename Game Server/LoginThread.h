///////////////////////////////////////////////////
//	LoginThread.h
//	Header file for the LoginThread class
//	a thread that talks to a connected client
//	By: Nissim Zohar ID:  066412149
///////////////////////////////////////////////////
#ifndef __LOGINTHREAD_H__
#define __LOGINTHREAD_H__
#include "../common/Thread.h"
#include <exception>
#include "global.h"
#include "TableManager.h"
///////////////////////////////////////////////////////////////////
class StreamSocket;

class LoginThread: public Thread {
public:
	LoginThread(StreamSocket *socket,TableManager* manag);
	~LoginThread();
	int Process();
	// finished: return value - true/false - thread finished
	bool finished() const { return m_finished; }
private:
	LoginThread();
	LoginThread(const LoginThread&);
	void operator=(const LoginThread&);

	StreamSocket *m_socket;
	TableManager* mannager;

	bool m_finished;
///////////////////////////////////////////////////////////////////
// *** ThreadException ***
public:
	class LoginThreadException: public exception {
	public:
		LoginThreadException(const char *msg): m_msg(msg) {}
		const char *what() const throw() { return m_msg.c_str(); }
	private:
		LoginThreadException();
		std::string m_msg;
	};
///////////////////////////////////////////////////////////////////
};

#endif 