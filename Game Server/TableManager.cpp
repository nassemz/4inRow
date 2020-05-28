///////////////////////////////////////////////////
// TableManager.cpp: implementation of the TableManager class.
//	By: Nissim Zohar ID:  066412149
///////////////////////////////////////////////////

#include "TableManager.h"
#include "..\common\sockglob.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TableManager::TableManager(int port,char* databip)
//Construction the Data Base server IP & Port for updating connection
{
	this->DbPort= port;
	DbIP = new char[IPLEN];
	strcpy(this->DbIP,databip);
}
/////////////////////////////////////////////////////////////////////////////
TableManager::~TableManager()
// Destruction the Data Base server Ip
{
	delete[] DbIP;
}
/////////////////////////////////////////////////////////////////////////////
Table* TableManager::createNewTable(Player* p)
//this fucntion create a new table it's take the first player as argument and 
//creating table and the player will be the first player in the player array 
//of the Table
{
		Table* Tbl=new Table(p);
		Tbl->SetSockectPZero(p->GetSocket());
		Table_list.push_back(Tbl);
		Tbl->SetDbIP(this->DbIP);
		Tbl->SetDbPort(this->DbPort);
		return Tbl;
}
/////////////////////////////////////////////////////////////////////////////
void TableManager::clearEmptyTables()
{
//this function to clear the empty table after the table is dead
//the int flag it's for evrey time we distroy a table return from the bigen 
//cause they are therds and maybe 1 or two finish in the same time

	list<Table*>::iterator Tbl_Iter;
	int flag= 1;
	
	do{
	flag = 0;

	for(Tbl_Iter=Table_list.begin();Tbl_Iter!=Table_list.end();Tbl_Iter++)
		if((*Tbl_Iter)->isFinish()==true)
		{
			delete[] *(Tbl_Iter);
			Table_list.erase(Tbl_Iter);
			flag = 1;
			break;
		}		

	}while(flag);
}
/////////////////////////////////////////////////////////////////////////////
void TableManager::addPlayerToTable(Player* p)
//this function uses before the CreateNewTable function it's called 
//to the all of the players there is a table that not full so we add a player to it
//else we call the CreateNewTable function
{
	Table* Tbl;

	Tbl=CheckTable(); // return pointer to table
	if(Tbl==0)
		Tbl=createNewTable(p);//else we call the CreateNewTable function
	else
		Tbl->AddPlayer(p);
}
/////////////////////////////////////////////////////////////////////////////
Table* TableManager::CheckTable()
//this function check if there is a table that not full 
//if yes return pointer to it
//else return 0
{
	if(Table_list.size()==0)
		return 0;
	
	list<Table*>::iterator Tbl_Iter;

	for(Tbl_Iter=Table_list.begin();Tbl_Iter!=Table_list.end();Tbl_Iter++)
		if((*Tbl_Iter)->isFull()==false)
		{
			if((*Tbl_Iter)->user_connected())
				return *(Tbl_Iter);
			else
			{
				//delete[] *(Tbl_Iter);
				Table_list.erase(Tbl_Iter);
				return CheckTable();
			}
		}

	return 0;
		
}
/////////////////////////////////////////////////////////////////////////////