///////////////////////////////////////////////////
// Table.cpp: implementation of the Table class.
//	By: Nissim Zohar ID:  066412149
///////////////////////////////////////////////////

#include "Table.h"
#include "..\common\sockglob.h"
#include "global.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Table::Table(Player* player_tbl){
	full = false;
	finish = false;
	players[0].SetUser(player_tbl->GetUser());
	players[0].SetSocket(player_tbl->GetSocket());
	
}
//////////////////////////////////////////////////////////////////////
void Table::SetDbIP(char* IP)
{
	this->DbIP = new char[IPLEN];
	strcpy(DbIP,IP);
}
//////////////////////////////////////////////////////////////////////
void Table::SetDbPort(int Port)
{
	this->DbPort = Port;
}
//////////////////////////////////////////////////////////////////////
const bool Table::user_connected()
{
	char x[1];
	char o[1];
	x[0]=XXX;
	o[0]=OOO;

	//Sets the coin chars
	if(!players[0].Set_Type(x[0]))
	{
		UpdateDBServer(0,"win",0);
		return false;
	}
	if(!players[0].Set_Type(o[0]))
	{
		UpdateDBServer(0,"win",0);
		return false;
	}

	
		
	return true;
}
//////////////////////////////////////////////////////////////////////
int Table::Process(){
	
	int winner=0,i=0;
	Game game;
	int move=0;
	try{
		//update the server that they eql cause if the data base server fall
		// then we canot update the server
		//therefore we will update it from the begin for equal 
		// and when any one will win wel will wel will update again the eql varible and the win varible!!
		UpdateDBServer(0,"eql");
		UpdateDBServer(1,"eql");
		//to tell the first player that you are starting
		players[i].StartP();	
		
		while (1)
		{			
			move=players[i].getMove();
			if(move==0)
				break;
			else
				game.Insert(move,i);
			if(game.CheckFullArray()== true )
			{
				players[(i+1) % 2].SendEqul();
				players[(i+1) % 2].sendMove(move);
				players[i].SendEqul();
				players[i].sendMove(move);
				break;
			/*	//those 4 row not for telling data base that his equal 
				//but to tell the data base that the player status is OFF now...
				UpdateDBServer(0,"eql",0);
				UpdateDBServer(1,"eql",0);
				UpdateDBServer(0,"eql",-1);
				UpdateDBServer(1,"eql",-1);*/
			}
			if(game.CheckArray())
			//checking if there some one win
			//if the game finished
			{
				players[(i+1) % 2].SendLoss();
				players[(i+1) % 2].sendMove(move);
				players[i].SendWin();
				UpdateDBServer(0,"eql",-1);
				UpdateDBServer(1,"eql",-1);
				UpdateDBServer(i,"win");
				UpdateDBServer((i+1) % 2,"loss");
				break;
			}
			players[(i+1) % 2].sendMove(move);
			i=getTurn(i);
		}
		if(move==0)
		{
			players[getTurn(i)].SendWin();
			UpdateDBServer(getTurn(i),"eql",-1);
			UpdateDBServer(i,"eql",-1);
			UpdateDBServer(getTurn(i),"win");
			UpdateDBServer(i,"loss");
			
		}

	} catch(Socket::SocketException e){// /PlayerExcption exp){ 
		finish=true; // the procces is finished and now we can delete the table

		int PlOneWinner=1,PlTwoWinner=1;
		
		// one of the clients disconnected 
		if (players[0].isDisconnected())
			PlOneWinner=0;
		if (players[1].isDisconnected())
			PlTwoWinner=0;
		// they diconneted together
		if(PlOneWinner == 0 && PlTwoWinner == 0)
		{
			UpdateDBServer(0,"eql",-1);
			UpdateDBServer(1,"eql",-1);
			UpdateDBServer(0,"loss");
			UpdateDBServer(1,"loss");			
		}
		// the second is diconneted
		if(PlOneWinner == 1 && PlTwoWinner == 0)
		{
			UpdateDBServer(1,"eql",-1);
			UpdateDBServer(0,"eql",-1);
			UpdateDBServer(0,"win");
			UpdateDBServer(1,"loss");

		}
		// the first is diconneted
		if(PlOneWinner == 0 && PlTwoWinner == 1)
		{
			UpdateDBServer(0,"eql",-1);
			UpdateDBServer(1,"eql",-1);
			UpdateDBServer(1,"win");
			UpdateDBServer(0,"loss");
		}
		
		return 1;
	}
	finish=true; // the procces is finished and now we can delete the table
	return 1;
}
//////////////////////////////////////////////////////////////////////
Table::~Table(){
//deletng the Data Base Server IP
	delete[] this->DbIP; 
}
//////////////////////////////////////////////////////////////////////
void Table::AddPlayer(Player *player_tbl)
{
	full=true; //the table is full
	players[1].SetUser(player_tbl->GetUser()); //set the name of the user that playing
	players[1].SetSocket(player_tbl->GetSocket()); // set his socket
	char x[1];
	char o[1];
	x[0]=XXX;
	o[0]=OOO;

	players[1].Set_Type(o[0]);
	players[1].Set_Type(x[0]);
		
	this->start();// calling process
}
//////////////////////////////////////////////////////////////////////
bool Table::UpdateDBServer(int win,string state,int i)
//Updating the server by sending 3 parameters
//int win = number of player (1 or 2)
//string state= status (win , loss , equal )
//int i how much to add to the winn counter or loss counter ...
{
	try {
		StreamSocket socket;	//connecting to Data Base Server
		socket.connect(this->GetDbIP(),this->GetDbPort());
		
		// talk with the DBServer
		Update UpDte;
		StinrToChar(UpDte.username,players[win].GetUser()); //have to convert sting to char* then sending it;
		UpDte.num=i;
		StinrToChar(UpDte.kindupdate,state);


		//Sending to Data Base Server the data
		socket.send("4",4); 
		// 1 is telling to rigistaration
		// 2 is telling to logon
		// 3 is telling to report
		// 4 is telling to update

		//sending the data
		socket.send( (char *)& UpDte, sizeof(Update));
	}
	//catching socket error exceptions
	catch (Socket::SocketException e) {
		std::cout << e.what() << std::endl;
		return false;
	}
	return true;
}
//////////////////////////////////////////////////////////////////////

int Table::getTurn(int turn){
	return ((turn+1) % 2);
}
//////////////////////////////////////////////////////////////////////