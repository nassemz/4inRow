///////////////////////////////////////////////////
//	global.h
//	By: Nissim Zohar ID:  066412149
///////////////////////////////////////////////////
#ifndef _LIB_GLOB_
#define _LIB_GLOB_
#pragma warning(disable: 4786)
#include <string>
#include <iostream>
using namespace std;
//////////////////////////////////////////////////////////////////////////
//converting the string variable to int type
const int StringToInt(const string k);
const int WinRank = 20;
const int LossRank = 4;
const int EqlRank = 10;
//////////////////////////////////////////////////////////////////////////
struct Registration {
	char username[12];
	char password[12];
	char email[30];
};
//////////////////////////////////////////////////////////////////////////
struct Login{
	char username[12];
	char password[12];
};
//////////////////////////////////////////////////////////////////////////
struct Report{
	char username[12];
	char outcome ;   // outcome = 'w' - win ; outcome='l' - lose; outcome='d' - draw
	int rankChange; // �� ����� �����   -5 ���� �� ������ ������ �� ���. ������  
};
//////////////////////////////////////////////////////////////////////////
struct Query{
	char username[12];
};
//////////////////////////////////////////////////////////////////////////
enum Busy_e {YES=0, NO};
enum States_e { OK=0,FAIL, ALREADY_EXIST, DOESNT_EXIST, INVALID_PASSWORD};
/*
OK - ������ ������ �����.
FAIL - ������ ����� (�� ���� �����)
ALREADY_EXIST - ��� ������ ����� ����� ��� ��� �� �� ����� ����
DOESNT_EXIST - ��� ������ ������/����� ������ �� ����
INVALID_PASSWORD - ������ ���� ��� ������ ���� �����
*/
//////////////////////////////////////////////////////////////////////////
struct Reply{
	States_e status;
	int wins, loses ,rank,equal;
	Busy_e stonoff;
};
//////////////////////////////////////////////////////////////////////////
struct Update{
	int num;
	char username[12];
	char kindupdate[6];
};
//////////////////////////////////////////////////////////////////////////
#endif

