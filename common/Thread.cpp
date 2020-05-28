///////////////////////////////////////////////////
//	Thread.cpp
//	By: Nissim Zohar
//	ID:  066412149
///////////////////////////////////////////////////
#include "Thread.h"

HANDLE Thread::start ()
{	
	return m_handle = 
		::CreateThread (NULL, 0, (unsigned long (__stdcall *)(void *))this->runProcess,(void *)this, 0, NULL);
}	

//static method
int Thread::runProcess (void* pThis)
{
	int retVal = ((Thread*)(pThis))->Process();
	return retVal;
}

//our working method, virtual, overridable
int Thread::Process ()
{
		return 1;
};
