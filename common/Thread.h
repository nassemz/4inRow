///////////////////////////////////////////////////
//	Thread.h
//	Header file for thread class
//	By: Nissim Zohar
//	ID:  066412149
///////////////////////////////////////////////////


#ifndef ___THREAD__H__
#define ___THREAD__H__

#include <windows.h>

class Thread{
public:
	Thread(): m_handle(NULL) {}
	HANDLE start();
	virtual int Process() =0;
	HANDLE getHandle() { return m_handle; }
	virtual ~Thread() { if (m_handle != NULL) CloseHandle(m_handle); }
private:
	Thread(const Thread&);
	void operator=(const Thread&);

	static int runProcess (void* pThis);
	HANDLE m_handle;
};

#endif