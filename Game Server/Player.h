///////////////////////////////////////////////////
//	Player.h: interface for the Player class.
//	By: Nissim Zohar ID:  066412149
///////////////////////////////////////////////////
#if !defined(AFX_PLAYER_H__4C1826C3_A5F9_4904_AA91_DD6A7E9E3949__INCLUDED_)
#define AFX_PLAYER_H__4C1826C3_A5F9_4904_AA91_DD6A7E9E3949__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "global.h"
#include "../common/StreamSocket.h"
///////////////////////////////////////////////////////////////////

class Player  
{
public:
	//Constractor that takes 2 parameters
	//string user is the user name
	//sock is a pointer to the player socket
	Player(string user,	StreamSocket* sock);
	//default constarcotr
	Player();
	//Distractor
	virtual ~Player();
	//function for telling the first player to start playing
	void StartP();
	//////////////////////////////////////////////////////	
	StreamSocket* GetSocket(){return socket_t;} //returns pointer to player sockect
	int getMove(); // get move is giting a legal number from the player to insert to the array
	virtual bool isDisconnected();//checking if the player disconnected
	const string GetUser()const {return username;}//get the user name
	//////////////////////////////////////////////////////
	virtual void sendMove(int mov);//sending the number that the other player give 
	virtual bool Set_Type(char a);//set the type like X or O
	virtual void SendEqul();//send that the result is Equal
	virtual void SetUser(string name){username= name;}//set the user name
	virtual void SetSocket(StreamSocket* soc){socket_t = soc;}//set the sockect
	virtual void SendWin();//sending you win
	virtual void SendLoss();//sending you loss
	//////////////////////////////////////////////////////	
private:
	StreamSocket* socket_t;// socket of the player
	string username; // username of the player
};
///////////////////////////////////////////////////////////////////
#endif // !defined(AFX_PLAYER_H__4C1826C3_A5F9_4904_AA91_DD6A7E9E3949__INCLUDED_)
///////////////////////////////////////////////////////////////////