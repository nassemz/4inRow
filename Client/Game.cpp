///////////////////////////////////////////////////
// Game.cpp: implementation of the Game class.
//	By: Nissim Zohar
//	ID:  066412149
///////////////////////////////////////////////////
#include "Game.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Game::Game()
{
	initarr();
}
//////////////////////////////////////////////////////////////////////
Game::~Game()
{
	
}
//////////////////////////////////////////////////////////////////////
void Game::PrintGame()
//printing the game
{
	cout<<"\t\t\t\t";
	for(int i=0; i < Row ; i++)
		cout<<"---";
	
	cout<<endl;

	for(i=0; i < Row ; i++)
		for(int j=0; j < Col; j++)
		{
			if(j==0)
				cout<<"\t\t\t\t"<<"| ";
			
			cout<<" "<<arr[i][j];
			if(j == Col-1)
				cout<< " |"<<endl<<endl;
		}
	cout<<"\t\t\t\t";
	for(i=0; i < Row ; i++)
		cout<<"---";
		
	cout<<endl;
	cout<<"\t\t\t\t";
	cout<<"   ";

	for(int j=1; j < Col+1; j++)
		cout<<j<<" ";
	cout<<endl;		
}
//////////////////////////////////////////////////////////////////////
void Game::initarr()
//initialization the array to '.'
{
	for(int i=0; i < Row ; i++)
		for(int j=0; j < Col ; j++)
			arr[i][j]='.';
}
//////////////////////////////////////////////////////////////////////
bool Game::Insert(int y,int player)
//inseret number to the array
{
	for(int i=Row; i>0 ; i--)
	{
		if(arr[i-1][y-1] == '.')
		{
			if(player==1)
				arr[i-1][y-1]=Type;
			else
				arr[i-1][y-1]=Second_Type;
			break;
		}
		if(i == 1)
		{
			cout<<endl<< "This Colum Is Full..."<<endl;
			return false;
		}
	}
	PrintGame();
	return true;
}
//////////////////////////////////////////////////////////////////////
bool Game::CheckArray()
//check if there are winner
{
	for(int i=0; i < Row ; i++)
		for(int j=0; j < Col ; j++)
		{
			if(j+3 <= Col)
			{
				if (arr[i][j] == arr[i][j+1] && arr[i][j] == arr[i][j+2] && arr[i][j] == arr[i][j+3] && arr[i][j] != '.')
					return true;
			}
			if(i+3 <= Row)
			{
				if (arr[i][j] == arr[i+1][j] && arr[i][j] == arr[i+2][j] && arr[i][j] == arr[i+3][j] && arr[i][j] != '.')
					return true;
			}
			if((j-3 > 0) && (i+3 <= Row) )	
			{
				if (arr[i][j] == arr[i+1][j-1] && arr[i][j] == arr[i+2][j-2] && arr[i][j] == arr[i+3][j-3] && arr[i][j] != '.')
					return true;
			}
			if((j+3 <= Col) && (i+3 <= Row) )
			{
				if (arr[i][j] == arr[i+1][j+1] && arr[i][j] == arr[i+2][j+2] && arr[i][j] == arr[i+3][j+3] && arr[i][j] != '.')
					return true;
			}
		}
		return false;
}
//////////////////////////////////////////////////////////////////////
