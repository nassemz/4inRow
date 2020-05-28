///////////////////////////////////////////////////
//	WorkerThread.cpp
//	By: Nissim Zohar ID:  066412149
///////////////////////////////////////////////////

#include <string.h>
#include "WorkerThread.h"
#include "../common/StreamSocket.h"
/////////////////////////////////////////////////////////////////////////
WorkerThread::WorkerThread(StreamSocket *socket,list<Players *>* play): m_socket(socket), m_finished(false)
{
	play_list=play;
}
/////////////////////////////////////////////////////////////////////////
int WorkerThread::Process() {
	// talk to the client
	try {
		Reply Rp_DB;
		char what_to_do[5];
		char buf[256];
		buf[0]=0;
		int option;
		Update update_user;
		
		//receving the option what to do "logon regis..." 
		m_socket->recv(what_to_do, 4);

		option=atoi(what_to_do);
		Login log;
		int CheckLogin;
		list <Players *>::iterator IterPlalyers;
		string users;
		bool flag=true;

		switch(option)
		{
		case 1:
			////////////////////////////////////////////////////////
			//Registration
			////////////////////////////////////////////////////////
			m_socket->recv(buf,sizeof(Registration));
			Registration reg;
			reg = (struct Registration&) buf;
			//add user
			if(AddUser(reg.username,reg.password,reg.email) == false)
			{
				Rp_DB.status=ALREADY_EXIST;
				Rp_DB.loses=0;
				Rp_DB.rank=0;
				Rp_DB.wins=0;
			}
			else
			{
				Rp_DB.status=OK;
				Rp_DB.loses=0;
				Rp_DB.rank=1500;
				Rp_DB.wins=0;
			}
			break;
		case 2:
			////////////////////////////////////////////////////////
			//Login
			////////////////////////////////////////////////////////
			m_socket->recv(buf,sizeof(Login));
			log = (struct Login&) buf;
			//check user and password
			CheckLogin=CheckFromFile(log.username,log.password);
			//if yes then return a ok msg
			if(CheckLogin == 0)
			{
				Rp_DB.status=OK; //ok msg
				Rp_DB.stonoff=NO;
				UpdateStatus(log.username,YES); ///////////////
			}
			else
			{
				if(CheckLogin == 1)
				{
					Rp_DB.status=INVALID_PASSWORD; //msg INVALID_PASSWORD
				}
				if(CheckLogin == 2)
				{
					Rp_DB.status=DOESNT_EXIST;
				}
			}
			if(CheckLogin == 8)
			{//ok msg but his status is on logon right now
				Rp_DB.status=OK; 
				Rp_DB.stonoff=YES;
			}

			break;
		case 3: // for report
			////////////////////////////////////////////////////////
			//Report
			////////////////////////////////////////////////////////
			m_socket->recv(buf,sizeof(Login));
			log = (struct Login&) buf;
			//report
			CheckLogin=CheckFromFile(log.username,log.password);
			if(CheckLogin == 0 || CheckLogin == 8)
			{
				Rp_DB=CheckForReport(log.username);
			}
			else{
				if(CheckLogin == 1)
				{
					Rp_DB.status=INVALID_PASSWORD;
				}
				if(CheckLogin == 2)
				{
					Rp_DB.status=DOESNT_EXIST;
				}	
			}
			break;
		case 4:
			////////////////////////////////////////////////////////
			//Update
			////////////////////////////////////////////////////////
			m_socket->recv(buf,sizeof(Update));
			update_user= (struct Update&) buf;
			UpdateUser(update_user);
			break;
		case 5:
			////////////////////////////////////////////////////////
			//Remove 
			////////////////////////////////////////////////////////
			m_socket->recv(buf,sizeof(Login));
			log = (struct Login&) buf;
			Rp_DB.status = RemoveUser( log.username );

			break;
		case 6:
			////////////////////////////////////////////////////////
			//Report for the game server only 
			////////////////////////////////////////////////////////
			m_socket->recv(buf,sizeof(Login));
			log = (struct Login&) buf;
			if(CheckUser( log.username )==false)
				Rp_DB.status=DOESNT_EXIST;
			else
			{
				Rp_DB.status=OK;
				Rp_DB=CheckForReport(log.username);
			}

			break;
		
		case 7:
			////////////////////////////////////////////////////////
			//List Of users
			////////////////////////////////////////////////////////
			flag=false;
			
			for(IterPlalyers=play_list->begin();IterPlalyers!=play_list->end();IterPlalyers++)

			{
				
				m_socket->send((((*IterPlalyers)->GetUser()).c_str()),14);				
			}

			m_socket->send("EOF",14);				
			break;


		default : 
			break;
		}
	if(flag==true)
		m_socket->send((char *)& Rp_DB,sizeof(Reply));
		
	}
	catch (Socket::SocketException e) {
		printf("Socket exception in worker thread: %s \n",e.what());
	}
	// tell main this thread is finished
	m_finished = true;
	return 0;
}
/////////////////////////////////////////////////////////////////////////
void WorkerThread::UpdateStatus(string user,Busy_e st)
{
	list <Players *>::iterator IterPlalyers;
	
	for(IterPlalyers=play_list->begin();IterPlalyers!=play_list->end();IterPlalyers++)
	{
		if( ((*IterPlalyers)->GetUser()==user))
		{
			(*IterPlalyers)->UpdateStatus(YES);
		}
	}
}
/////////////////////////////////////////////////////////////////////////
WorkerThread::~WorkerThread() {
	if (m_socket)
		delete m_socket;
}
/////////////////////////////////////////////////////////////////////////
int WorkerThread::CheckFromFile(string user,string password)
{
	list <Players *>::iterator IterPlalyers;
	
	for(IterPlalyers=play_list->begin();IterPlalyers!=play_list->end();IterPlalyers++)
	{
		if( ((*IterPlalyers)->GetUser()==user))
		{
			
			if( ((*IterPlalyers)->GetPassword()==password) )
			{
				if((*IterPlalyers)->GetStatus()==NO )
					return 0; // it's OK
				else
					return 8;
			}
			else 
				return 1;//INVALID_PASSWORD
		}
	}
	return 2; // user DOESNT_EXIST
}

/////////////////////////////////////////////////////////////////////////
bool WorkerThread::CheckUser(string user)
{
	list <Players *>::iterator IterPlalyers;
	
	for(IterPlalyers=play_list->begin();IterPlalyers!=play_list->end();IterPlalyers++)
	{
		if( ((*IterPlalyers)->GetUser()==user))
		{
			return true; // it's OK
			
		}
	}
	return false; // user DOESNT_EXIST
}
/////////////////////////////////////////////////////////////////////////
Reply WorkerThread::CheckForReport(string user)
{
	list <Players *>::iterator IterPlalyers;
	Reply re;
	re.status=DOESNT_EXIST;

	for(IterPlalyers=play_list->begin();IterPlalyers!=play_list->end();IterPlalyers++)
	{
		if( ((*IterPlalyers)->GetUser()==user))
		{
			re.wins = (*IterPlalyers)->GetWins();
			re.loses = (*IterPlalyers)->GetLoses();
			re.equal = (*IterPlalyers)->GetEqul();
			re.rank = (*IterPlalyers)->GetRank();
			re.status = OK;
			return re;

		}
	}
	return re; // user DOESNT_EXIST
}
/////////////////////////////////////////////////////////////////////////

States_e WorkerThread::RemoveUser(string user)
{
	list <Players *>::iterator IterPlalyers;
	
	for(IterPlalyers=(*play_list).begin();IterPlalyers!=(*play_list).end();IterPlalyers++)
	{
		if( (*IterPlalyers)->GetUser() == user )
		{
			// if the player his status is playing so we cannot
			//delete him cause he had to update
			if((*IterPlalyers)->GetStatus() == YES) 
				return FAIL;
			else
			{
				delete (*IterPlalyers);
				(*play_list).erase(IterPlalyers);
				return OK;
			}
		}
	}
	return DOESNT_EXIST;
}

/////////////////////////////////////////////////////////////////////////
bool WorkerThread::AddUser(string user ,string password,string name)
{

	list <Players *>::iterator IterPlalyers;
	
	for(IterPlalyers=(*play_list).begin();IterPlalyers!=(*play_list).end();IterPlalyers++)
	{
		if( (*IterPlalyers)->GetUser() == user )
		{
			return false;
		}
	}
	
	Players* Temp_Player = new Players(user,password,name);
	(*play_list).push_back(Temp_Player);
	return true;
}
/////////////////////////////////////////////////////////////////////////
bool WorkerThread::UpdateUser(Update up)
{
	list <Players *>::iterator IterPlalyers;
	string cmp;
	cmp = up.username;
	for(IterPlalyers=(*play_list).begin();IterPlalyers!=(*play_list).end();IterPlalyers++)
	{
		if((*IterPlalyers)->GetUser() == cmp)
		{
			if(strcmp(up.kindupdate,"win")==0)
				(*IterPlalyers)->UpdateWins(up.num);
			if(strcmp(up.kindupdate,"loss")==0)
				(*IterPlalyers)->UpdateLoss(up.num);
			if(strcmp(up.kindupdate,"eql")==0)
				(*IterPlalyers)->UpdateEql(up.num);
			return true;
		}
	}
	return false;
}
/////////////////////////////////////////////////////////////////////////