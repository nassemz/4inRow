///////////////////////////////////////////////////
//  main.cpp
//	Main program file for the server application
//	By: Nissim Zohar ID:  066412149
///////////////////////////////////////////////////

#include "..\common\StreamSocket.h"
#include "..\common\sockglob.h"
#include "LoginThread.h"

#include "TableManager.h"
#include "ClieFunc.h"
#include <string.h>
#include <string>
#include <iostream>
#include <vector>


// Check for finished threads and clear them from the system
void clearFinished(std::vector<LoginThread*> &threads, bool forceClean = false) {
	std::vector<LoginThread*>::iterator pos = threads.begin();
	while (!(pos == threads.end()))
		if (forceClean || (*pos)->finished()) {
			WaitForSingleObject((*pos)->getHandle(), INFINITE);
			delete *pos;
			threads.erase(pos);
		}
		else
			++pos;
}



int main(int argc, char *argv[]) {
	
	int port;             //Port for listening.
	char *IPAdr;		  //IP addr' to connect to.
	
	IPAdr = new char[IPLEN];
	
	cout << "Game Server Interface"<<endl;
	cout << "~~~~~~~~~~~~~~~~"<<endl;
	
	get_arguments(port,IPAdr,argc,argv);    //Get the port, and the ip address.
	
	cout <<endl<< "Data Base Using Port Number : "<<port<<endl;
	cout << "Data Base IP Address : "<<IPAdr<<endl<<endl;
	
	
	
	std::vector<LoginThread*> threads; // save the threads the server created
	TableManager* manager=new TableManager(port,IPAdr);
	
	try {
		// Listen for connections
		StreamSocket socket;
		cout<<"Welcome To Game Server at"<<endl<<"IP : ";
		cout<<socket.Get_IP()<<endl;
		cout<<"Port : ";
		cout<<DEFAULTPORT<<endl;
		
		int a = 0;

		socket.listen(NULL, DEFAULTPORT);
		while (1) {
			try {
				std::string cliAddress;
				StreamSocket *cli_socket = socket.accept(cliAddress);
				std::cout << cliAddress << std::endl;
				// create new userlogin thread
				LoginThread *userlogin = new LoginThread(cli_socket,manager);
				userlogin->start();
				// save a pointer to the thread
				threads.push_back(userlogin);
				// clear any finished threads
				clearFinished(threads);
				manager->clearEmptyTables();
				std::cout << "There are " << manager->NumberOfGames() * 2 << " client(s) connected.\n";
				std::cout << "There are " << manager->NumberOfGames() << " Game(s) Right Now.\n";
				
			}
			catch (LoginThread::LoginThreadException e) {
				//SaveToFile(&players_list);
				std::cout << e.what() << std::endl;
			}
		}
		
	}
	catch (Socket::SocketException e) {
		//	SaveToFile(&players_list);
		std::cout << e.what() << " - " << WSAGetLastError() << std::endl;
	}
	//SaveToFile(&players_list);
	clearFinished(threads, true);
	return 0;
}
