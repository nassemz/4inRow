///////////////////////////////////////////////////
//	TableManager.h: interface for the TableManager class.
//	By: Nissim Zohar ID:  066412149
///////////////////////////////////////////////////

#if !defined(AFX_TABLEMANAGER_H__4E33142C_A446_4313_A2CE_A12B6B100C98__INCLUDED_)
#define AFX_TABLEMANAGER_H__4E33142C_A446_4313_A2CE_A12B6B100C98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Player.h"
#include "Table.h"
#include <list>

class TableManager  
{
public:
	//constractor that takes 2 parameter the port and the ip of the data base server
	TableManager(int port,char* databip);
	//CheckTable return if there are table no full
	Table* CheckTable();
	//Adding player to table
	virtual void addPlayerToTable(Player* p);
	//clear empty table
	virtual void clearEmptyTables();
	virtual ~TableManager();
	int NumberOfGames()const{return Table_list.size();}
//////////////////////////////////////////////////
public:
/////////////////////////////////////
	const int GetDbPort()const{return DbPort;} //Data Base Port
	const char* GetDbIP()const{return DbIP;} //Data Base IP
/////////////////////////////////////
private:
	//creating a new table
	Table* createNewTable(Player* p);
	TableManager();
/////////////////////////////////////
	int DbPort; //Data Base Port
	char* DbIP; //Data Base IP
/////////////////////////////////////
//////////////////////////////////////////////////
	std::list<Table *> Table_list; //svae the Tables

};

#endif // !defined(AFX_TABLEMANAGER_H__4E33142C_A446_4313_A2CE_A12B6B100C98__INCLUDED_)
