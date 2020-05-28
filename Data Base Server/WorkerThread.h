///////////////////////////////////////////////////
//	WorkerThread.h
//	Header file for the WorkerThread class
//	a thread that talks to a connected client
//	By: Nissim Zohar ID:  066412149
///////////////////////////////////////////////////
#ifndef __WORKERTHREAD_H__
#define __WORKERTHREAD_H__
#include "../common/Thread.h"
#include <exception>
#include <fstream>
#include <list>
#include "Players.h"
#include "global.h"
/////////////////////////////////////////////////////
class StreamSocket;

class WorkerThread: public Thread {
public:
	WorkerThread(StreamSocket *socket,list<Players *>* play);
	~WorkerThread();
	int Process();
	// finished: return value - true/false - thread finished
	bool finished() const { return m_finished; }
private:
	WorkerThread();
	WorkerThread(const WorkerThread&); //copy constractor
	void operator=(const WorkerThread&);
	StreamSocket *m_socket;
	bool m_finished;
	/////////////////////////////////////////////////////
	// *** ThreadException ***
public:
	class WorkerThreadException: public exception {
	public:
		WorkerThreadException(const char *msg): m_msg(msg) {}
		const char *what() const throw() { return m_msg.c_str(); }
	private:
		WorkerThreadException();
		std::string m_msg;
	};
	/////////////////////////////////////////////////////
private :
		std::list<Players *>* play_list; //svae the player after load from file
public:
	virtual bool CheckUser(string user);
	//update the statf of the player
	virtual void UpdateStatus(string user,Busy_e st);
	//Remove A User only by the game server
	virtual States_e RemoveUser(string user);
	//check if user and passwor is OK
	virtual int CheckFromFile(string user,string password);
	//rport about user
	virtual Reply CheckForReport(string user);
	//add user to list
	bool AddUser(string user ,string password,string name);
	//update user
	virtual bool UpdateUser(Update up);
};
/////////////////////////////////////////////////////
#endif //__WORKERTHREAD_H__