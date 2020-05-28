///////////////////////////////////////////////////
// global.cpp: implementation of the global class.
//	By: Nissim Zohar ID:  066412149
///////////////////////////////////////////////////

#include "global.h"
#include <fstream>
#include <conio.h>	  /* needed for getch() */
//////////////////////////////////////////////////////////////////////
const int StringToInt(string k)
{
	const char* temp=k.c_str();
	for(int indx=0;indx<k.length();indx++)
	{
		if(temp[indx]>'9' || temp[indx]<'0')
			return 0;
	}
	return atoi(k.c_str());
}
//////////////////////////////////////////////////////////////////////
int GetPassword()
{
	ios_base::openmode  mode = ios_base::in;
	ifstream AdminFile("Admin.db",mode);
	char temp[50];
	
	AdminFile.getline(temp,49,'\n');
	string passwo = temp;
	AdminFile.close();

	const char* RealPass = passwo.c_str();
	char input = '\0';
	int pass;
	int p = 0;
	int c = 0;	
	while( c == 0 )     /* keep trying until correct password is entered */
	{
		char Password[20] = { '\0' };
		cout<<"Password: ";
		for(p = 0;p < 19;p++)
		{
			input = getch();         /* get character entered */
			if( input != '\r' && input != '\b' )   
			{
				if( isprint( input ) != 0 )
					Password[p] = input;     /* store input in Password */    
				if( iscntrl( input ) == 0 )
					cout << "*";             /* print '*' instead of input */
			}
			else if( input == '\r' )	/* if input = 'return' then */
				break;					/* break out of for() statment */
			else if( input == '\b' )	/* if input = 'backspace' then */
			{
				if( p > 0 )		/* Make sure that the 'password' prompt is not deleted */
				{
					cout << '\b' << " " << '\b';	/* erase the last '*' */
					--p;
					Password[p] = '\0';		/* overwrite last character with '\0' */
				}
				--p;
			}
		}
		pass = strcmp( RealPass, Password );   /* compare strings */
		if( pass != 0 )
		{
			cout << "\a\n\n\tLogin Unsuccessful!\n" << endl;
			return 0;
		}
		else if( pass == 0 )
		{
			cout << "\n\n\tLogin Successful!\n" << endl;
			return 1;
			c++;
		}
		if( p == 19 )       /* indicates too many characters were entered */
			cout << "\a\n\nTo many characters entered!"
			<< "\nPlease try again." << endl;
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////