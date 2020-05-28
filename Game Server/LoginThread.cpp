///////////////////////////////////////////////////
//  LoginThread.cpp
//	By: Nissim Zohar ID:  066412149
///////////////////////////////////////////////////
#include "LoginThread.h"
#include "../common/StreamSocket.h"

LoginThread::LoginThread(StreamSocket *socket,TableManager* manag): m_socket(socket), mannager(manag) ,m_finished(false) {}

int LoginThread::Process() {
	
	Reply reply_answer;
	int option;
	bool flag=false;
	Login l;
	
	try {
		char buf[256];
		//option 
		//1) Registration
		//2) Login
		//3) Report
		m_socket->recv(buf,sizeof(int));
		option=StringToInt(buf);
		
		// connect to data base server
		StreamSocket socket;
		socket.connect(mannager->GetDbIP(),mannager->GetDbPort());
		flag=true;
		
		switch (option)
		{
		case 1:
			/////////////////////////////////////////////
			//Registration
			/////////////////////////////////////////////
			Registration r;
			
			m_socket->recv(buf,sizeof(Registration));
			r = (struct Registration&) buf;
			// talk with the server Registration
			buf[0] = 0;
			itoa(option,buf,10);
			socket.send(buf,4);
			socket.send( (char *)& r, sizeof(Registration));
			socket.recv(buf,sizeof(Reply));
			break;
		case 2:
			/////////////////////////////////////////////
			//Login
			/////////////////////////////////////////////
			m_socket->recv(buf,sizeof(Login));
			l = (struct Login&) buf;
			// talk with the server Login
			buf[0] = 0;
			itoa(option,buf,10);
			socket.send(buf,4);
			socket.send( (char *)& l, sizeof(Login));
			socket.recv(buf,sizeof(Reply));
			break;
		case 3:
			/////////////////////////////////////////////
			//Report
			/////////////////////////////////////////////
			m_socket->recv(buf,sizeof(Login));
			l = (struct Login&) buf;
			// talk with the server Login
			buf[0] = 0;
			itoa(option,buf,10);
			socket.send(buf,4);
			socket.send( (char *)& l, sizeof(Login));
			socket.recv(buf,sizeof(Reply));
			break;

		default:
			break;
		}
		//returnig to the client with the reply msg
		reply_answer= (struct Reply&) buf;
		m_socket->send( (char *)& reply_answer, sizeof(Reply));
		
		//add the player to the mannager only if loged on as OK
		if((option == 2) && (reply_answer.status == OK) && (reply_answer.stonoff == NO ))
		{
			Player* player_login = new Player(l.username,m_socket);
			mannager->addPlayerToTable(player_login);
		}
		
	}
	catch (Socket::SocketException e) {
		std::cout << e.what() << std::endl;
		try
		{
			if(flag==false)
			{
				reply_answer.status = FAIL;
				m_socket->send( (char *)& reply_answer, sizeof(Reply));
			}
			
		}catch (Socket::SocketException e) {
		}
		
	}
	
	// tell main this thread is finished
	m_finished = true;
	return 0;
}

LoginThread::~LoginThread() {
	
}
