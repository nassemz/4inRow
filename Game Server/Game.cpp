///////////////////////////////////////////////////
// Game.cpp: implementation of the Game class.
//	By: Nissim Zohar ID:  066412149
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
void Game::PrintGame()
//printing the game
{
	cout<<"\t\t\t\t";
	for(int i=0; i < ROW ; i++)
		cout<<"---";
	
	cout<<endl;

	for(i=0; i < ROW ; i++)
		for(int j=0; j < COL; j++)
		{
			if(j==0)
				cout<<"\t\t\t\t"<<"| ";
			
			cout<<" "<<arr[i][j];
			if(j == COL-1)
				cout<< " |"<<endl<<endl;
		}
	cout<<"\t\t\t\t";
	for(i=0; i < ROW ; i++)
		cout<<"---";
		
	cout<<endl;
	cout<<"\t\t\t\t";
	cout<<"   ";

	for(int j=0; j < COL; j++)
		cout<<j<<" ";
	cout<<endl;		
}
//////////////////////////////////////////////////////////////////////
void Game::initarr()
//initialization the array to '.'
{
	for(int i=0; i < ROW ; i++)
		for(int j=0; j < COL ; j++)
			arr[i][j]='.';
}
//////////////////////////////////////////////////////////////////////
void Game::Insert(int player , int character )
//inseret number to the array
{
	for(int i=ROW; i>0 ; i--)
	{
		if(arr[i-1][player-1] == '.')
		{
			if(character == 0)
			{
				arr[i-1][player-1]=XXX;
			}
			else
				arr[i-1][player-1]=OOO;
			if(CheckArray()==true)
			{
				cout<<"Game was finished "<<endl;
			}
		//	PrintGame();
			return;
		}
	}
		
}
//////////////////////////////////////////////////////////////////////
bool Game::CheckArray()
//check if there are winner
{
	for(int i=0; i < ROW ; i++)
		for(int j=0; j < COL ; j++)
		{
			if(j+3 <= COL)
			{
				if (arr[i][j] == arr[i][j+1] && arr[i][j] == arr[i][j+2] && arr[i][j] == arr[i][j+3] && arr[i][j] != '.')
					return true;
			}
			if(i+3 <= ROW)
			{
				if (arr[i][j] == arr[i+1][j] && arr[i][j] == arr[i+2][j] && arr[i][j] == arr[i+3][j] && arr[i][j] != '.')
					return true;
			}
			if((j-3 > 0) && (i+3 <= ROW) )	
			{
				if (arr[i][j] == arr[i+1][j-1] && arr[i][j] == arr[i+2][j-2] && arr[i][j] == arr[i+3][j-3] && arr[i][j] != '.')
					return true;
			}
			if((j+3 <= COL) && (i+3 <= ROW) )
			{
				if (arr[i][j] == arr[i+1][j+1] && arr[i][j] == arr[i+2][j+2] && arr[i][j] == arr[i+3][j+3] && arr[i][j] != '.')
					return true;
			}
		}
		return false;
}

//check if the array full
bool Game::CheckFullArray()
{
	for(int j=0; j < COL ; j++)
			if(arr[0][j] == '.')
				return false;
			return true;

}
//////////////////////////////////////////////////////////////////