///////////////////////////////////////////////////
//	Players.cpp: implementation of the Players class.
//	By: Nissim Zohar ID:  066412149
///////////////////////////////////////////////////


#include "Players.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Players::~Players(){}
//////////////////////////////////////////////////////////////////////
Players::Players(string a, string b , string c, int win, int los , int rnk,int eq)
:user(a) , password(b) , email(c) , wins(win),loses(los),rank(rnk),equal(eq),status(NO),firstime(0){}
//////////////////////////////////////////////////////////////////////
//ofstream fo writing to file all of the class in one function
ofstream& operator<<(ofstream& o, const Players& B)
{
	   o << B.GetUser() << endl;
	   o << B.GetPassword() << endl;
	   o << B.GetEmail() << endl;
	   o << B.GetWins() << endl;
	   o << B.GetLoses() << endl;
	   o << B.GetEqul() << endl;
	   o << B.GetRank() << endl;	   
       return o;
}
//////////////////////////////////////////////////////////////////////
//updating if the resul is win
void Players::UpdateWins(int add)
{
	status=NO;
	firstime =0;
	wins+=add;
	if(add < 0)
		rank -= WinRank;
	if(add > 0)
		rank += WinRank;
}
//////////////////////////////////////////////////////////////////////
//updating if the resul is losse
void Players::UpdateLoss(int add)
{
	status=NO;
	firstime =0;
	loses+=add;
	if(add < 0)
		rank -= LossRank;
	if(add > 0)
		rank += LossRank;
}
//////////////////////////////////////////////////////////////////////
//updating if the resul is equal
void Players::UpdateEql(int add)
{
	if(firstime == 2)
	{
		status=NO;
		firstime =0;
	}
	else
	{
		firstime++;
		status=YES;
	}

	equal += add;
	if(add < 0)
		rank -= EqlRank;
	if(add > 0)
		rank += EqlRank;		
}
//////////////////////////////////////////////////////////////////////
void Players::UpdateStatus(Busy_e ste)
//updating if the status of the player
{
	status=ste;
}
//////////////////////////////////////////////////////////////////////
