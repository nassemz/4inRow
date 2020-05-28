///////////////////////////////////////////////////
//	Game.h: interface for the Game class.
//	By: Nissim Zohar ID:  066412149
///////////////////////////////////////////////////
#if !defined(AFX_GAME_H__816ED8AA_5572_4092_A0D6_0BE0A34D1C05__INCLUDED_)
#define AFX_GAME_H__816ED8AA_5572_4092_A0D6_0BE0A34D1C05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <iostream>
#include "global.h"
using namespace std;

class Game
{
public:
	//insert to the array an number
	void Insert(int character , int player);
	//printing the array 
	virtual void PrintGame();
	//Defualt Constractor
	Game();
	//Distractor
	virtual ~Game(){};
	//Check the Array if the game was finished
	virtual bool CheckArray();
	//Check the Array is Full
	virtual bool CheckFullArray();

private : 
	void initarr();
	char arr[ROW][COL];
};

#endif // !defined(AFX_GAME_H__816ED8AA_5572_4092_A0D6_0BE0A34D1C05__INCLUDED_)
