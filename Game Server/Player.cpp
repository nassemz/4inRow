///////////////////////////////////////////////////
//	Player.cpp: implementation of the Player class.
//	By: Nissim Zohar ID:  066412149
///////////////////////////////////////////////////

#include "Player.h"
//////////////////////////////////////////////////////////////////////
Player::Player(string user,	StreamSocket* sock)
: socket_t(sock), username(user){}
//////////////////////////////////////////////////////////////////////
Player::Player(){}
//////////////////////////////////////////////////////////////////////
Player::~Player()
{
	delete socket_t;
}
//////////////////////////////////////////////////////////////////////
int Player::getMove()
{
	
	try{
		char buf[4];
		buf[0]=0;
		socket_t->recv(buf,4);
		return atoi(buf);
	}catch (Socket::SocketException e) {
		cout << e.what() << std::endl;
		return 0;
	}
}
//////////////////////////////////////////////////////////////////////
void Player::StartP()
{
	socket_t->send("go",4);
}
//////////////////////////////////////////////////////////////////////
void Player::sendMove(int mov)
{
	switch (mov)
	{
	case 1:
		socket_t->send("1",4);
		break;
	case 2:
		socket_t->send("2",4);
		break;
	case 3:
		socket_t->send("3",4);
		break;
	case 4:
		socket_t->send("4",4);
		break;
	case 5:
		socket_t->send("5",4);
		break;
	case 6:
		socket_t->send("6",4);
		break;
	case 7:
		socket_t->send("7",4);
		break;
	default:
		break;
	}
}
//////////////////////////////////////////////////////////////////////

bool Player::Set_Type(char a)
{
	bool flag=false;
	try{
		char buff[4];
		buff[0] = a;
		socket_t->send(buff,4);
		flag=true;
	}
	catch (Socket::SocketException e) {
		std::cout << e.what() << std::endl;
		flag=false;
	}
	return flag;
}
//////////////////////////////////////////////////////////////////////
void Player::SendWin(){
	try{
		socket_t->send("win",4);
		
	}catch (Socket::SocketException e) {
		
	}
}
//////////////////////////////////////////////////////////////////////
void Player::SendLoss(){
	try{
		socket_t->send("los",4);
		
	}catch (Socket::SocketException e) {
		
	}	
}
//////////////////////////////////////////////////////////////////////
void Player::SendEqul(){
	try{
		socket_t->send("eql",4);
		
	}catch (Socket::SocketException e) {
		
	}	
}
//////////////////////////////////////////////////////////////////////
bool Player::isDisconnected()
{
	try{
		socket_t->send("win",4);
		
	}catch (Socket::SocketException e) {
		return true;
	}
	
	return false;
}
//////////////////////////////////////////////////////////////////////