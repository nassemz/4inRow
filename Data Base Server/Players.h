///////////////////////////////////////////////////
//	Players.h: interface for the Players class.
//	By: Nissim Zohar ID:  066412149
///////////////////////////////////////////////////


#ifndef _PLAYERS_
#define _PLAYERS_
#pragma warning(disable: 4786)
#include <string>
#include<iostream>
using namespace std;
#include <fstream>
#include "global.h"
///////////////////////////////////////////////////////////////////
class Players  
{
public:
	//constractor with all of parameters
	Players(string a, string b, string c,int win = 0, int los=0, int rnk=1500,int eq=0);
	virtual ~Players();
///////////////////////////////////////	
	//functions for geting user password email...
	Busy_e GetStatus()const{return status;}
	const string GetUser()const{return user;}
	const string GetPassword()const{return password;}
	const string GetEmail()const{return email;}
	const int GetWins()const{return wins;}
	const int GetLoses()const{return loses;}
	const int GetRank()const{return rank;}
	const int GetEqul()const{return equal;}
///////////////////////////////////////
	//functions for Updating Wins Loss Eql...
	virtual void UpdateWins(const int add);
	virtual void UpdateLoss(const int add);
	virtual void UpdateEql(const int add);
	//update the status
	virtual void UpdateStatus(Busy_e ste);
///////////////////////////////////////
	//functions for ofstream
	friend ofstream& operator<<(ofstream& o, const Players& B);
///////////////////////////////////////////////////////////////////	
private:
	string user;
	string password;
	string email;
	int wins;
	int loses;
	int equal;
	int rank;
	Busy_e status;
	int firstime; // only for checking status
};
///////////////////////////////////////////////////////////////////
#endif

