///////////////////////////////////////////////////
//	main.cpp
//	Main program file for the server application
//	By: Nissim Zohar ID:  066412149
///////////////////////////////////////////////////
#include "..\common\StreamSocket.h"
#include "..\common\sockglob.h"
#include "WorkerThread.h"
#include <string.h>
#include <string>
#include <iostream>
#include <vector>
////////////////////////////////////////////////////////////////////////////////
// Check for finished threads and clear them from the system
void clearFinished(std::vector<WorkerThread*> &threads, bool forceClean = false) {
	std::vector<WorkerThread*>::iterator pos = threads.begin();
	while (!(pos == threads.end()))
		if (forceClean || (*pos)->finished()) {
			WaitForSingleObject((*pos)->getHandle(), INFINITE);
			delete *pos;
			threads.erase(pos);
		}
		else
			++pos;
}
////////////////////////////////////////////////////////////////////////////////
//function for load and save to file
void LoadFromFile(list<Players *>* players);
void SaveToFile(list<Players *> *players);
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]) 
{
	// save the threads the server created
	//those clinet that doing one of the three option 
	//register ... logon ... report
	std::vector<WorkerThread*> threads; 

	//svae the player after load from file
	std::list<Players *> players_list; 

	//load the file into the player list
	LoadFromFile(&players_list);
	try {
		// Listen for connections
		StreamSocket socket;
		cout<<"Welcome For Opening the Server at"<<endl<<"IP : ";
		cout<<socket.Get_IP()<<endl;
		cout<<"Port : ";
		cout<<DEFAULTSERVERPORT<<endl;

		socket.listen(NULL, DEFAULTSERVERPORT);
		while (1) {
			try {
				//save to file
				SaveToFile(&players_list);
				std::string cliAddress;
				StreamSocket *cli_socket = socket.accept(cliAddress);
				std::cout << cliAddress << std::endl;
				// create new worker thread
				WorkerThread *worker = new WorkerThread(cli_socket,&players_list);
				worker->start();
				// save a pointer to the thread
				threads.push_back(worker);
				// clear any finished threads
				clearFinished(threads);
				std::cout << "There are " << threads.size() << " client(s) connected.\n";
				std::cout << "There are " << players_list.size() << " Player(s) in our DataBase.\n";
			}
			catch (WorkerThread::WorkerThreadException e) {
				SaveToFile(&players_list);
				std::cout << e.what() << std::endl;
			}
		}
	}
	catch (Socket::SocketException e) {
		SaveToFile(&players_list);
		std::cout << e.what() << " - " << WSAGetLastError() << std::endl;
	}
	catch (...) {
		SaveToFile(&players_list);
	}
	clearFinished(threads, true);
	SaveToFile(&players_list);
	return 0;
}
////////////////////////////////////////////////////////////////////////////////
void LoadFromFile(list<Players *> *players)
{
	ios_base::openmode  mode = ios_base::in;
	ifstream PlayersFile("Players.db",mode);
	
	if (! PlayersFile.is_open())
		return; //file doesnt exist!
	
	char temp[50];
	string user,password,wins,equal;
	string email,loses,rank;
	
	Players* Temp_Player;
	
	while(!PlayersFile.eof())
	{
		PlayersFile.getline(temp,49,'\n');
		if(strcmp(temp,"EOF")==0)
			break;
		user=temp;
		PlayersFile.getline(temp,49,'\n');
		password=temp;
		PlayersFile.getline(temp,49,'\n');
		email=temp;
		PlayersFile.getline(temp,49,'\n');
		wins=temp;
		PlayersFile.getline(temp,49,'\n');
		loses=temp;
		PlayersFile.getline(temp,49,'\n');
		equal=temp;
		PlayersFile.getline(temp,49,'\n');
		rank=temp;
		
		Temp_Player = new Players(user,password,email,StringToInt(wins),StringToInt(loses),StringToInt(rank),StringToInt(equal));
		players->push_back(Temp_Player);		
	}
	
	PlayersFile.close();
}
////////////////////////////////////////////////////////////////////////////////
void SaveToFile(list<Players *> *players)
{
	list<Players*>::const_iterator iter;

	

	ios_base::openmode  mode = ios_base::out | ios_base::trunc;
	ofstream PlayersFile("Players.db",mode);
	
	PlayersFile.clear(0);
	
	for(iter=players->begin();iter!=players->end();iter++)
		PlayersFile<<*(*iter);
	
	PlayersFile<<"EOF";
	
	PlayersFile.close();
}
////////////////////////////////////////////////////////////////////////////////