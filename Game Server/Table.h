///////////////////////////////////////////////////
//	Table.h: interface for the Table class.
//	By: Nissim Zohar ID:  066412149
///////////////////////////////////////////////////
#if !defined(AFX_TABLE_H__5DF542DD_26D8_4DB8_84B0_446AFB83F957__INCLUDED_)
#define AFX_TABLE_H__5DF542DD_26D8_4DB8_84B0_446AFB83F957__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\COMMON\Thread.h"
#include "Player.h"
#include "Game.h"

class Table : public Thread  
{
public:
/////////////////////////////////////
	//constarctor that takes 1 parameter "player parameter"
	Table(Player* player_tbl);
	virtual ~Table();
	int Process();
/////////////////////////////////////	
	const bool isFinish()const {return finish;} //return if the game was finish
	const bool isFull()const{return full;}//return if the game is full
	virtual const bool user_connected();
/////////////////////////////////////
	bool UpdateDBServer(int win,string state,int i=1);//updating the server
	void AddPlayer(Player* player_tbl);//add player to the table
	void SetSockectPZero(StreamSocket* sock){players[0].SetSocket(sock);}//set the first player socket
/////////////////////////////////////
private:
	Table(); //defualt constractor as private
	int getTurn(int turn);//return the turn for players
public:
/////////////////////////////////////
	virtual void SetDbIP(char* IP); // sets the data base server ip
	virtual void SetDbPort(int Port);// sets the data base server port
	const int GetDbPort()const{return DbPort;} //get the Data Base Port
	const char* GetDbIP()const{return DbIP;} //Get the Data Base IP
/////////////////////////////////////
private:
/////////////////////////////////////
	int DbPort; //Data Base Port
	char* DbIP; //Data Base IP
/////////////////////////////////////
private:
	Player players[2];
	bool full;
	bool finish;
/////////////////////////////////////
};

#endif // !defined(AFX_TABLE_H__5DF542DD_26D8_4DB8_84B0_446AFB83F957__INCLUDED_)
