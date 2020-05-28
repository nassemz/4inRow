///////////////////////////////////////////////////
// Game.h: interface for the Game class.
//	By: Nissim Zohar
//	ID:  066412149
///////////////////////////////////////////////////
#if !defined(AFX_GAME_H__816ED8AA_5572_4092_A0D6_0BE0A34D1C05__INCLUDED_)
#define AFX_GAME_H__816ED8AA_5572_4092_A0D6_0BE0A34D1C05__INCLUDED_
///////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <iostream>
#include "global.h"
//#include "Thread.h"
using namespace std;
///////////////////////////////////////////////////////////
class Game
{
public:
///////////////////////////////////////////////////////////
	//insert to the array an number
	bool Insert(int y,int player);
	//printing the array 
	virtual void PrintGame();
	//Defualt Constractor
	Game();
	//Distractor
	virtual ~Game();
	//set first player type
	virtual void SetFirst_Type(char a){Type = a;}
	//set second player type
	virtual void SetSecond_Type(char a){Second_Type = a;}
///////////////////////////////////////////////////////////
private : 
	bool CheckArray();
	void initarr();
	char arr[6][7];
	char Type;
	char Second_Type;
///////////////////////////////////////////////////////////
};
///////////////////////////////////////////////////////////
#endif // !defined(AFX_GAME_H__816ED8AA_5572_4092_A0D6_0BE0A34D1C05__INCLUDED_)
///////////////////////////////////////////////////////////