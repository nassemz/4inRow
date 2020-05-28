///////////////////////////////////////////////////
//	global.h
//	By: Nissim Zohar
//	ID:  066412149
///////////////////////////////////////////////////
#ifndef _LIB_GLOB_
#define _LIB_GLOB_
#pragma warning(disable: 4786)
#include <string>
#include <iostream>
using namespace std;
/////////////////////////////////////////////////////////////////////////
const int Row=6;
const int Col=7;
//converting the string variable to int type
const int StringToInt(const string k);
/////////////////////////////////////////////////////////////////////////
struct Registration {
	char username[12];
	char password[12];
	char email[30];
};
/////////////////////////////////////////////////////////////////////////
struct Login{
	char username[12];
	char password[12];
};
/////////////////////////////////////////////////////////////////////////
struct Report{
	char username[12];
	char outcome ;   // outcome = 'w' - win ; outcome='l' - lose; outcome='d' - draw
	int rankChange; // �� ����� �����   -5 ���� �� ������ ������ �� ���. ������  
};
/////////////////////////////////////////////////////////////////////////
struct Query{
	char username[12];
};
/////////////////////////////////////////////////////////////////////////
enum States_e { OK=0,FAIL, ALREADY_EXIST, DOESNT_EXIST, INVALID_PASSWORD};
/*
OK - ������ ������ �����.
FAIL - ������ ����� (�� ���� �����)
ALREADY_EXIST - ��� ������ ����� ����� ��� ��� �� �� ����� ����
DOESNT_EXIST - ��� ������ ������/����� ������ �� ����
INVALID_PASSWORD - ������ ���� ��� ������ ���� �����
*/
/////////////////////////////////////////////////////////////////////////
enum Busy_e {YES=0, NO};
struct Reply{
	States_e status;
	int wins, loses ,rank,equal;
	Busy_e stonoff;
};
/////////////////////////////////////////////////////////////////////////
#endif

